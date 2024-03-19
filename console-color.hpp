#ifndef CONSOLE_COLOR_HPP
#define CONSOLE_COLOR_HPP

#if defined(__linux__) && !defined(CONSOLE_COLOR_USE_ANSI)
#define CONSOLE_COLOR_USE_ANSI
#endif

#if defined(_WIN32) && !defined(CONSOLE_COLOR_USE_ANSI)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

#include <iostream>

namespace console
{
#ifndef CONSOLE_COLOR_USE_ANSI
    enum shade
    {
        black,
        blue,
        green,
        cyan,
        red,
        purple,
        yellow,
        white,
        grey,
        bright_blue,
        bright_green,
        bright_cyan,
        bright_red,
        bright_purple,
        bright_yellow,
        bright_white,
        invalid
    };
#else
    enum shade
    {
        black = 30,
        red = 31,
        green = 32,
        yellow = 33,
        blue = 34,
        purple = 35,
        cyan = 36,
        white = 37,
        grey = 90,
        bright_red = 91,
        bright_green = 92,
        bright_yellow = 93,
        bright_blue = 94,
        bright_purple = 95,
        bright_cyan = 96,
        bright_white = 97,
        invalid
    };
#endif

    class color
    {
    public:
        color(shade text);
        color(shade text, shade background);

        shade text;
        shade background;
    };

    inline color get()
    {
#ifndef CONSOLE_COLOR_USE_ANSI
        CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo;
        if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &screenBufferInfo))
            return color(shade::white, shade::black);

        shade text = shade(screenBufferInfo.wAttributes % 16);
        shade background = shade(screenBufferInfo.wAttributes / 16);

        return color(text, background);
#else
        return color(shade(0), shade(0));
#endif
    }

    inline color default_color = get();

    inline color::color(shade text) : text(text), background(default_color.background) {}
    inline color::color(shade text, shade background) : text(text), background(background) {}

    inline void set(shade text, shade background)
    {
#ifndef CONSOLE_COLOR_USE_ANSI

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), background * 16 + text);
#else
        if (background != 0)
            background = shade(background + 10);

        printf("\033[%d;%dm", background, text);
#endif
    }

    inline void invert()
    {
#ifndef CONSOLE_COLOR_USE_ANSI
        color color = get();
        set(color.background, color.text);
#else
        printf("\033[7m");
#endif
    }

    inline void reset() { set(default_color.text, default_color.background); }

    inline std::ostream& invert(std::ostream& os) { invert(); return os; }
    inline std::wostream& invert(std::wostream& os) { invert(); return os; }

    inline std::ostream& reset(std::ostream& os) { reset(); return os; }
    inline std::wostream& reset(std::wostream& os) { reset(); return os; }

    inline std::ostream& operator<<(std::ostream& os, const color& color) { set(color.text, color.background); return os; }
    inline std::wostream& operator<<(std::wostream& os, const color& color) { set(color.text, color.background); return os; }

    template<typename T>
    class color_scoped
    {
    public:
        T thing;
        shade text;
        shade background;
        bool inverted = false;

        inline color_scoped(T t) : thing(std::move(t)), text(default_color.text), background(default_color.background) {}
        inline color_scoped(T t, shade text) : thing(std::move(t)), text(text), background(default_color.background) {}
        inline color_scoped(T t, shade text, shade background) : thing(std::move(t)), text(text), background(background) {}

        inline color_scoped<T>& invert()
        {
            inverted = !inverted;
            return *this;
        }
    };

    template<typename T>
    inline std::ostream & operator<<(std::ostream& os, const color_scoped<T> & it)
    {
        set(it.text, it.background);

        if (it.inverted)
            invert();

        os << it.thing;
        reset();

        return os;
    }

    template<typename T>
    inline std::wostream& operator<<(std::wostream& os, const color_scoped<T>& it)
    {
        set(it.text, it.background);
        os << it.thing;
        reset();

        return os;
    }
}

#endif

# Console Color

This is a simple, lightweight, header only library c++ library that allows to colorize the console text/background.

If you want to use the ANSI under Windows 10, define this macro `COLOR_USE_ANSI`.  
By default this macro is only defined for Linux.

## CMake support

You can add this library with a CMake help by using `add_subdirectory` + `target_link_libraries` calls on `console_color` target.
```cmake
# ...
add_subdirectory(console_color)
target_link_libraries(your_target_name PRIVATE console_color)
# ...
```

## Motivation

The main inspiration behind creating this project was [Color Console](https://github.com/aafulei/color-console) project (big credits for author for creating it).  
The library was created mainly to have an abstract way of dealing with colorization of colors in console applications under various platforms.  
I've made my own library, because the original one didn't support Linux + it was way too complex to introduce such support.

On older version of Windows than 10, [ANSI escape code](https://en.wikipedia.org/wiki/ANSI_escape_code) isn't supported, so the only way to colorize the console output  
that will work on older windows versions is to use syscall [SetConsoleTextAttribute](https://learn.microsoft.com/en-us/windows/console/setconsoletextattribute).

Linux supports [ANSI escape code](https://en.wikipedia.org/wiki/ANSI_escape_code) out of the box, so the text colorization is somewhat standardized over various distros.

## Examples

### Colors

This example demonstrates the usage of colors, you have to remember to manually place `console::reset`, to restore the default console color.

```cpp
std::cout << "Roses are " << console::color(console::shade::red) << "red" << console::reset << " and violets are " << console::color(console::shade::blue) << "blue" << console::reset << ".\n";
```

### Scoped colors

This example demonstrates the usage of scoped colors, they are more convienient in places when you want to colorize a specific part of text and reset the current console color automatically to default one.

```cpp
std::cout << "A " << console::color_scoped("red", console::shade::red) << " car races past a " << console::color_scoped("yellow", console::yellow) << " taxi near " << console::color_scoped("green", console::green) << " park.\n";
```

### colorized text & background

This example demonstrates the usage of colorization of backgrounds using scoped colors, it's also possible to use this feature on non scoped colors.

```cpp
std::cout << console::color_scoped("red", console::shade::black, console::shade::red) << " " << console::color_scoped("green", console::shade::black, console::shade::green) << " " << console::color_scoped("blue", console::shade::black, console::shade::blue) << "\n";
```

### inverting the current color

This example demonstrates the usage of invert current color feature.

```cpp
std::cout << console::color(console::shade::black, console::shade::white) << "Yin" << console::invert << "Yang" << console::reset << "\n";
```

### 
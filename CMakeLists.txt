add_library("console_color" INTERFACE)

target_sources("console_color" INTERFACE "console_color.hpp")
target_include_directories("console_color" INTERFACE "./")
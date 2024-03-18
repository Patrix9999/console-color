add_library("console-color" INTERFACE)

target_sources("console-color" INTERFACE "console-color.hpp")
target_include_directories("console-color" INTERFACE "./")
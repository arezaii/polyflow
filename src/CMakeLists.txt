add_library(pfutil STATIC pfutil.cpp pfutil.hpp)

add_executable(polyflow main.cpp polyflow.hpp)

target_link_libraries(polyflow pfutil)
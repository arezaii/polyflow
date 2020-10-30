add_library(pfutil STATIC pfutil.cpp pfutil.hpp)

add_executable(polyflow main.cpp)

target_link_libraries(polyflow pfutil)
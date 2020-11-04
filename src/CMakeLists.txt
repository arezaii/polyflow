add_library(pfutil STATIC pfutil.cpp pfutil.hpp)

add_executable(polyflow main.cpp)

target_link_libraries(polyflow pfutil)

add_custom_target(polyflow_build 
				  COMMAND iscc < ${CMAKE_CURRENT_SOURCE_DIR}/simpleOpenReadCloseGen.iscc.txt > ${CMAKE_CURRENT_SOURCE_DIR}/simpleOpenReadCloseGen.cpp)
				  
add_dependencies(polyflow polyflow_build)
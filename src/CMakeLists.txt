add_library(pfutil STATIC pfutil.cpp pfutil.hpp)

add_executable(polyflow main.cpp)

target_link_libraries(polyflow pfutil)

add_custom_target(polyflow_build 
				  COMMAND iscc < ${CMAKE_CURRENT_SOURCE_DIR}/simpleOpenReadCloseGen.iscc.txt > ${CMAKE_CURRENT_SOURCE_DIR}/simpleOpenReadCloseGen.cpp)
				  
add_dependencies(polyflow polyflow_build)

add_custom_target(polyflow_write
		COMMAND iscc < ${CMAKE_CURRENT_SOURCE_DIR}/simpleWriteFileGen.iscc.txt > ${CMAKE_CURRENT_SOURCE_DIR}/simpleWriteFileGen.cpp)

add_dependencies(polyflow polyflow_write)

add_custom_target(polyflow_cws
		COMMAND iscc < ${CMAKE_CURRENT_SOURCE_DIR}/addToGridGen.iscc.txt > 	${CMAKE_CURRENT_SOURCE_DIR}/addToGridGen.cpp)

add_dependencies(polyflow polyflow_cws)
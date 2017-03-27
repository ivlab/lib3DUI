project (GLEW C)

if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  # Linux specific code
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC") 
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC") 
endif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")

set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/plugins/${project_dirname}/deps/lib)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/plugins/${project_dirname}/deps/lib)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/plugins/${project_dirname}/deps/bin)
foreach (CONF ${CMAKE_CONFIGURATION_TYPES})
	string (TOUPPER ${CONF} CONF)
	set (CMAKE_RUNTIME_OUTPUT_DIRECTORY_${CONF} ${CMAKE_BINARY_DIR}/plugins/${project_dirname}/deps/bin)
	set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${CONF} ${CMAKE_BINARY_DIR}/plugins/${project_dirname}/deps/lib)
	set (CMAKE_LIBRARY_OUTPUT_DIRECTORY_${CONF} ${CMAKE_BINARY_DIR}/plugins/${project_dirname}/deps/lib)
endforeach(CONF CMAKE_CONFIGURATION_TYPES)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_library(glew STATIC glew.c include/GL/glew.h)

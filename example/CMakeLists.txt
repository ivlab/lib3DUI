
project(3DUIExample)

#---------------------- Files ----------------------

set(source_files
  main.cpp
  UIExample.cpp
)

set(header_files
  UIExample.h
)


set(extra_files
  desktop.minvr
)


set_source_files_properties(${extra_files} PROPERTIES HEADER_FILE_ONLY TRUE)


#---------------------- Dependencies ----------------------

find_package(MinVR REQUIRED)

include_directories(
	${OPENGL_INCLUDE_DIR}
	${MinVR_INCLUDE_DIR}
  ${glm_INCLUDE_DIR}
  ../lib3DUI
  ${CMAKE_SOURCE_DIR}/lib/glew/include
)

add_definitions(-DGLEW_STATIC)
if(MSVC)
	set(ALL_LIBS ${ALL_LIBS} optimized glew.lib debug glew_d.lib)
else()
	set(ALL_LIBS ${ALL_LIBS} optimized libglew.a debug libglew_d.a)
endif()

link_directories(${CMAKE_BINARY_DIR}/plugins/deps/lib)

#---------------------- OS Specific Flags ----------------------

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  # Apple-specific code
  set(CMAKE_CXX_FLAGS "-DOSX")
endif (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	find_package(Threads)
	find_package(X11)
	set(ALL_LIBS ${ALL_LIBS} ${CMAKE_THREAD_LIBS_INIT} rt Xrandr Xxf86vm Xi m dl ${X11_LIBRARIES})
endif()

#---------------------- Create Executable ----------------------

add_executable(${PROJECT_NAME} ${source_files} ${header_files} ${extra_files})
target_link_libraries(${PROJECT_NAME} 3DUI ${MinVR_LIBRARIES} ${OPENGL_gl_LIBRARY} ${ALL_LIBS})

# if not found on the system, add dependency to the glm external project
if (NOT ${glm_FOUND})
  add_dependencies(${PROJECT_NAME} glm)
endif (NOT ${glm_FOUND})


project(3DUI)

#---------------------- Files ----------------------

set(source_files
  BentoBoxWidget.cpp
  QuickShapes.cpp
  UIManager.cpp
  UIStates.cpp
)

set(header_files
  3DUIPluginAbstractions.h
  BentoBoxWidget.h
  QuickShapes.h
  UIManager.h
  UIStates.h
)

set(extra_files
  ../CMakeLists-ExternalProj-GLM.txt
  ../README.md
)


set_source_files_properties(${extra_files} PROPERTIES HEADER_FILE_ONLY TRUE)


#---------------------- Dependencies ----------------------

include_directories(
	${OPENGL_INCLUDE_DIR}
  ${glm_INCLUDE_DIR}
  ${GLM_INCLUDE_DIRS}
  ${CMAKE_SOURCE_DIR}/lib/glew/include
)

#---------------------- Create Lib ----------------------
add_definitions(-DGLEW_STATIC)
if(MSVC)
	set(ALL_LIBS ${ALL_LIBS} optimized glew.lib debug glew_d.lib)
else()
	set(ALL_LIBS ${ALL_LIBS} optimized libglew.a debug libglew_d.a)
endif()

link_directories(${CMAKE_BINARY_DIR}/plugins/deps/lib)

add_library(${PROJECT_NAME} ${source_files} ${header_files} ${extra_files})

# if not found on the system, add dependency to the glm external project
if (NOT ${glm_FOUND})
  add_dependencies(${PROJECT_NAME} glm)
endif (NOT ${glm_FOUND})

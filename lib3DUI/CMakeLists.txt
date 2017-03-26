
project(3DUI)

#---------------------- Files ----------------------

set(source_files
  BentoBoxWidget.cpp
  QuickShapes.cpp
  UIManager.cpp
  UIOverviewState.cpp
  UIInsideVolState.cpp
)

set(header_files
  3DUIPluginAbstractions.h
  BentoBoxWidget.h
  QuickShapes.h
  UIManager.h
  UIOverviewState.h
  UIInsideVolState.h
  UIState.h
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
)

#---------------------- Create Lib ----------------------

add_library(${PROJECT_NAME} ${source_files} ${header_files} ${extra_files})

# if not found on the system, add dependency to the glm external project
if (NOT ${glm_FOUND})
  add_dependencies(${PROJECT_NAME} glm)
endif (NOT ${glm_FOUND})


project(3DUI)

#---------------------- Files ----------------------

set(source_files
  BentoBoxWidget.cpp
#  GrabbingState.cpp
#  InkingState.cpp
  QuickShapes.cpp
#  StartState.cpp
)

set(header_files
#  3DUI.h
#  3DUIState.h
  BentoBoxWidget.h
#  GrabbingState.h
#  InkingState.h
  QuickShapes.h
#  StartState.h
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
)

#---------------------- Create Lib ----------------------

add_library(${PROJECT_NAME} ${source_files} ${header_files} ${extra_files})

# if not found on the system, add dependency to the glm external project
if (NOT ${glm_FOUND})
  add_dependencies(${PROJECT_NAME} glm)
endif (NOT ${glm_FOUND})
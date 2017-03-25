
# For headers and libs:
# 1. ideally: these are already installed on the system at a location
#    specified by the envvar 3DUI_ROOT.
# 2. if not, guess that 3DUI might be compiled locally in ../3DUI,
#    check there for the install directory in ../3DUI/build/install

find_path(3DUI_INCLUDE_DIR 3DUI.h
          HINTS ${CMAKE_SOURCE_DIR}/lib3DUI/)

find_library(3DUI_OPT_LIBRARIES NAMES lib3DUI.a 3DUI.lib 3DUI
             HINTS ${CMAKE_SOURCE_DIR}/build/lib)
          
find_library(3DUI_DEBUG_LIBRARIES NAMES lib3DUId.a 3DUId.lib 3DUId
             HINTS ${CMAKE_SOURCE_DIR}/build/lib)

if(3DUI_OPT_LIBRARIES AND 3DUI_DEBUG_LIBRARIES)
	set(3DUI_OPT_LIBRARIES optimized ${3DUI_OPT_LIBRARIES} )
	set(3DUI_DEBUG_LIBRARIES debug ${3DUI_DEBUG_LIBRARIES} )
#if only opt is found, use it for both
elseif(3DUI_OPT_LIBRARIES AND NOT 3DUI_DEBUG_LIBRARIES)
	set(3DUI_DEBUG_LIBRARIES debug ${3DUI_OPT_LIBRARIES} )
	set(3DUI_OPT_LIBRARIES optimized ${3DUI_OPT_LIBRARIES} )
#if only debug is found, use it for both
elseif(NOT 3DUI_OPT_LIBRARIES AND 3DUI_DEBUG_LIBRARIES)
	set(3DUI_OPT_LIBRARIES optimized ${3DUI_DEBUG_LIBRARIES} )
	set(3DUI_DEBUG_LIBRARIES debug ${3DUI_DEBUG_LIBRARIES} )
endif()

set(3DUI_LIBRARIES ${3DUI_OPT_LIBRARIES} ${3DUI_DEBUG_LIBRARIES})

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(3DUI  DEFAULT_MSG
                                  3DUI_INCLUDE_DIR 3DUI_OPT_LIBRARIES 3DUI_DEBUG_LIBRARIES 3DUI_LIBRARIES)

mark_as_advanced(3DUI_INCLUDE_DIR 3DUI_OPT_LIBRARIES 3DUI_DEBUG_LIBRARIES 3DUI_LIBRARIES)

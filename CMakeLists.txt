cmake_minimum_required(VERSION 2.8)
# --------------------------------------------------------------
#  lmidi
# --------------------------------------------------------------
set(MODULE_NAME lmidi)
set(target ${MODULE_NAME})

# Where to install files
set(INSTALL_PATH "${CMAKE_BINARY_DIR}/lib" CACHE STRING "Install directory path")
# -------- PLAT

set(LINK_LIBS stdc++)

if(UNIX)
  if(APPLE)
    set(PLAT "macosx")
    add_definitions(-D__MACOSX_CORE__)
    set(LINK_FLAGS "-bundle -undefined dynamic_lookup -all_load")
    set(LINK_LIBS "stdc++ -framework CoreMIDI -framework CoreAudio objc")
  else(APPLE)
    set(PLAT "linux")
    add_definitions(-D__LINUX_ALSA__)
    set(LINK_FLAGS "-shared")
    set(LINK_LIBS "stdc++ rt")
  endif(APPLE)
else(UNIX)
  if(WIN32)
    set(PLAT "win32")
    add_definitions(-D__WINDOWS_MM__)
  else(WIN32)
    set(PLAT "unsupported")
  endif(WIN32)
endif(UNIX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -fPIC -O2")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall -fPIC -O2")
if (RELEASE)
  add_definitions(-O2 -DNDEBUG)
endif(RELEASE)

# --------------------------------------------------------------
#  module
# --------------------------------------------------------------
add_custom_target(${MODULE_NAME} true)

# --------------------------------------------------------------
#  lmidi.core
# --------------------------------------------------------------
set(core "${MODULE_NAME}_core")

include_directories(include src/bind src)

file(GLOB CORE_SOURCES src/*.c src/bind/dub/*.cpp src/bind/*.cpp src/*.cpp
  src/${PLAT}/*.cpp src/${PLAT}/*.mm)

add_library(${core} MODULE ${CORE_SOURCES})
if(LINK_LIBS)
  target_link_libraries(${core} ${LINK_LIBS})
endif(LINK_LIBS)
set_target_properties(${core}
  PROPERTIES OUTPUT_NAME core
  LINK_FLAGS ${LINK_FLAGS}
  PREFIX ""
  SUFFIX ".so"
)  

add_dependencies(${MODULE_NAME} ${core})

# --------------------------------------------------------------
#  install                                     
# --------------------------------------------------------------
install(TARGETS ${core}
  DESTINATION ${INSTALL_PATH}/${MODULE_NAME}
)

# --------------------------------------------------------------
#  install                                     
# --------------------------------------------------------------
install(DIRECTORY ${MODULE_NAME}
  DESTINATION ${INSTALL_PATH}
)

#!/usr/bin/env lua
local lub = require 'lub'

local lib = require 'lmidi'

local def = {
  description = {
    summary = "Lubyk GUI module.",
    detailed = [[
      A pure OpenGL based GUI.
    ]],
    homepage = "http://doc.lubyk.org/"..lib.type..".html",
    author   = "Gaspard Bucher",
    license  = "MIT",
  },

  includes  = {'include', 'src/bind', 'src'},
  libraries = {'stdc++'},

  platlibs = {
    linux   = {'stdc++', 'rt'},
    macosx  = {
      'stdc++',
      '-framework CoreMIDI',
      '-framework CoreAudio',
      'objc',
    },
  },

  platdefs = {
    linux  = {'__LINUX_ALSA__'},
    macosx = {'__MACOSX_CORE__'},
    win32  = {'__WINDOWS_MM__'},
  }
  -- not needed on Mac OS X
  -- cmake_extra = [[
  -- add_subdirectory(src/glew)
  -- target_link_libraries(${core} ${CMAKE_BINARY_DIR}/glew/libGLEW.a)
  -- ]]
}

-- Platform specific sources or link libraries
def.platspec = def.platspec or lub.keys(def.platlibs)

--- End configuration

local tmp = lub.Template(lub.content(lub.path '|rockspec.in'))
lub.writeall(lib.type..'-'..lib.VERSION..'-1.rockspec', tmp:run {lib = lib, def = def, lub = lub})

tmp = lub.Template(lub.content(lub.path '|dist.info.in'))
lub.writeall('dist.info', tmp:run {lib = lib, def = def, lub = lub})

tmp = lub.Template(lub.content(lub.path '|CMakeLists.txt.in'))
lub.writeall('CMakeLists.txt', tmp:run {lib = lib, def = def, lub = lub})



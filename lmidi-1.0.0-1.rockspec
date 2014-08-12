package = "lmidi"
version = "1.0.0-1"
source = {
  url = 'https://github.com/lubyk/lmidi/archive/REL-1.0.0.tar.gz',
  dir = 'lmidi-REL-1.0.0',
}
description = {
  summary = "Lubyk GUI module.",
  detailed = [[
      A pure OpenGL based GUI.
    ]],
  homepage = "http://doc.lubyk.org/lmidi.html",
  license = "MIT"
}

dependencies = {
  "lua >= 5.1, < 5.3",
  "lub >= 1.0.3, < 2.0",
}
build = {
  type = 'builtin',
  modules = {
    -- Plain Lua files
    ['lmidi'          ] = 'lmidi/init.lua',
    ['lmidi.In'       ] = 'lmidi/In.lua',
    ['lmidi.Message'  ] = 'lmidi/Message.lua',
    ['lmidi.Note'     ] = 'lmidi/Note.lua',
    ['lmidi.Out'      ] = 'lmidi/Out.lua',
    -- C module
    ['lmidi.core'     ] = {
      sources = {
        'src/bind/dub/dub.cpp',
        'src/bind/lmidi_core.cpp',
        'src/bind/lmidi_In.cpp',
        'src/bind/lmidi_Out.cpp',
      },
      incdirs   = {'include', 'src/bind', 'src', 'src/rtmidi'},
      libraries = {'stdc++'},
    },
  },
  platforms = {
    linux = {
      modules = {
        ['lmidi.core'] = {
          libraries = {'stdc++', 'rt'},
        },
      },
    },
    macosx = {
      modules = {
        ['lmidi.core'] = {
          libraries = {'stdc++', '-framework CoreMIDI', '-framework CoreAudio', 'objc'},
        },
      },
    },
  },
}


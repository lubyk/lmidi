--[[----------------
  # Real time midi

  This module is part of [lubyk](http://lubyk.org) project.  
  Install with [luarocks](http://luarocks.org)

    $ luarocks install rtmidi
  
--]]--------------------
local lub = require 'lub'
local lib = lub.Autoload 'lmidi'

-- Current version of 'lmidi' respecting [semantic versioning](http://semver.org).
lib.VERSION = '1.0.0'

lib.DEPENDS = { -- doc
  -- Compatible with Lua 5.1, 5.2 and LuaJIT
  "lua >= 5.1, < 5.3",
  -- Uses [Lubyk base library](http://doc.lubyk.org/lub.html)
  'lub >= 1.0.3, < 2.0',
  -- Uses [lubyk networking and scheduling](http://doc.lubyk.org/lens.html)
  'lens ~> 1.0',
}


return lib

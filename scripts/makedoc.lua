local lut = require 'lut'
lut.Doc.make {
  sources = {
    'lui',
    {'doc', prepend = 'example/lui'},
  },
  copy = { 'doc', prepend = 'example/lui'},
  target = 'html',
  format = 'html',
  header = [[<h1><a href='http://lubyk.org'>Lubyk</a> documentation</h1> ]],
  index  = [=[
--[[--
  # Lubyk documentation

  ## List of available modules
--]]--
]=]
}


--[[------------------------------------------------------

  midi test
  ---------

  ...

--]]------------------------------------------------------
require 'lubyk'

local should = test.Suite('midi')

function should.autoLoad()
  assertTrue(midi)
end

test.all()

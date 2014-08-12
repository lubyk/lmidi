--[[------------------------------------------------------

  lmidi.In test
  ------------

  ...

--]]------------------------------------------------------
local lmidi  = require 'lmidi'
local lut    = require 'lut'
local In     = lmidi.In
local should = lut.Test 'lmidi.In'

local withUser = should:testWithUser()

function should.autoLoad()
  assertTrue(lmidi.In)
end

function should.raiseErrorOnBadPort()
  assertError("Invalid port number 88.", function()
    In(88)
  end)
end

function withUser.should.openPort(t)
  local mi = In(3)
  assertTrue(mi)
  t.continue = false
  local i= 0
  function mi:receive(msg)
    print(yaml.dump(msg))
    i = i + 1
    if i > 4 then
      t.continue = true
    end
  end
  t:timeout(function()
    return t.continue
  end)
  assertTrue(i > 4)
end

function withUser.should.createVirtualPort(t)
  local mi = In('foo')
  assertTrue(mi)
  print('Created virtual port', mi:portName(), 'please produce midi events...')
  t.continue = false
  local i= 0
  function mi.receive(a, b, c)
    print(a, b, c)
    i = i + 1
    if i > 4 then
      t.continue = true
    end
  end
  t:timeout(function()
    return t.continue
  end)
  assertTrue(i > 4)
end

function should.listInputPorts()
  local inputs = In.ports()
  assertType('table', inputs)
  assertType('string', inputs[1])
end

should:test()

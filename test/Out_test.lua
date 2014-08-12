--[[------------------------------------------------------

  midi.Out test
  -------------

  ...

--]]------------------------------------------------------
require 'lubyk'

local should = test.Suite('midi.Out')
local withUser = should:testWithUser()

function should.autoLoad()
  assertTrue(midi.Out)
end

function should.raiseErrorOnBadPort()
  assertError("the 'portNumber' argument .88. is invalid", function()
    midi.Out(88)
  end)
end

function withUser.should.openPort(t)
  local mo = midi.Out()
  mo:virtualPort('lubyk')
  local p_count = 6
  local base = {24, 12, 65, 24, 67, 72}
  local chan = {3,   2,  1, 4,  1,  2}
  local vol  = {60, 10, 50, 20, 40, 40}
  sleep(300) -- let DAW host find us
  local mi = midi.In('lubyk')
  local notes = {}
  assertTrue(mo)
  io.flush()
  t.players = {}
  t.players[p_count+1] = lk.Timer(125, function()
    local n = 37
    local off = {127+chan[1], n, 0}
    notes[n] = off
    mo:send(143+chan[1], n, 60)
    sleep(60)
    notes[n] = false
    mo:send(unpack(off))
  end)

  for i=1,p_count do
    t.players[i] = lk.Timer(250, function()
      local n = base[i] + 24*math.random()
      local off = {127+chan[i], n, 0}
      mo:send(143+chan[i], n, vol[i] * (1 + math.random()))
      notes[n] = off
      sleep(100 + 50*math.random())
      notes[n] = false
      mo:send(unpack(off))
      return 200 + 130*math.random()
    end)
    t.players[i]:start()
  end

  sleep(5000)
  for i=1,p_count+1 do
    t.players[i]:stop()
  end

  for n, s in pairs(notes) do
    if s then
      mo:send(unpack(s))
    end
  end
  assertTrue(true)
end

function withUser.should.sendChords(t)
  local mo = midi.Out()
  mo:virtualPort('lubyk')
  sleep(2000)
  t.timer = lk.Timer(500, function()
    mo:send {
      {143+1, 60, 80},
      {143+1, 63, 70},
      {143+1, 67, 90},
    }
    sleep(250)
    mo:send {
      -- NoteOff
      {127+1, 60, 0},
      {127+1, 63, 0},
      {127+1, 67, 0},
    }
  end)
  t.timer:start()
  sleep(4400)
  t.timer:stop()
  assertTrue(true)
end

function should.ignoreNil()
  local out = midi.Out()
  out:virtualPort('lubyk')
  assertPass(function()
    out:send(nil)
  end)
end

--function should.createVirtualPort()
--  local mi = midi.In('foo')
--  assertTrue(mi)
--  print(mi:port())
--  io.flush()
--  local continue = false
--  local i= 0
--  function mi.receive(a, b, c)
--    print(a, b, c)
--    io.flush()
--    i = i + 1
--    if i > 4 then
--      continue = true
--    end
--  end
--  local start = elapsed()
--  while not continue and elapsed() < start + 2000 do
--    sleep(10)
--  end
--  assertTrue(continue)
--end
--
test.all()

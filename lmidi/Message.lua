--[[------------------------------------------------------

  midi.Message
  ------------

  MIDI message abstraction.

--]]------------------------------------------------------
local lub    = require 'lub'
local lib    = lub.class 'midi.Message'

local private = {}

local CLOCK_NB_TO_OP = {
  [0xFA] = 'Start',
  [0xFC] = 'Stop',
  [0xF8] = 'Tick',
  [0xFB] = 'Continue',
}
local CLOCK_OP_TO_NB = {}
for k,v in pairs(CLOCK_NB_TO_OP) do
  CLOCK_OP_TO_NB[v] = k
end

setmetatable(lib, {
  __call = function(lib, ...)
    return lib.new(...)
  end
})

function lib.new(a, b, c)
  if a >= 0xF0 then
    if a == 0xF2 then
      return {
        type = 'Clock',
        op   = 'Song',
        -- Transform 1 position step = 6 midi clocks
        position = c * 128 + b,
      }
    else
      return {
        type = 'Clock',
        op   = CLOCK_NB_TO_OP[a],
      }
    end
  elseif a >= 0xB0 then
    return {
      type    = 'Ctrl',
      channel = a - 0xB0 + 1,
      ctrl    = b,
      value   = c
    }
  elseif a >= 0x90 then
    return {
      type     = c == 0 and 'NoteOff' or 'NoteOn',
      channel  = a - 0x90 + 1,
      note     = b,
      velocity = c
    }
  elseif a >= 0x80 then
    return {
      type     = 'NoteOff',
      channel  = a - 0x80 + 1,
      note     = b,
      velocity = c
    }
  else
    return {
      type = 'Raw',
      a    = a,
      b    = b,
      c    = c,
    }
  end
end

function lib.decode(msg)
  local type = msg.type
  if type == 'Clock' then
    return CLOCK_OP_TO_NB[msg.op]
  elseif type == 'Ctrl' then
    return msg.channel - 1 + 0xB0, msg.ctrl, msg.value
  elseif type == 'NoteOn' then
    return msg.channel - 1 + 0x90, msg.note, msg.velocity
  elseif type == 'NoteOff' then
    return msg.channel - 1 + 0x80, msg.note, msg.velocity
  else
    return msg.a, msg.b, msg.c
  end
end

return lib

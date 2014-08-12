--[[------------------------------------------------------

  lmidi.Out
  --------

  Create/open a midi port.

--]]------------------------------------------------------
local core  = require 'lmidi.core'
local lmidi = require 'lmidi'
local lib   = core.Out

local private = {}

local new = lib.new
function lib.new(port_or_name)
  local self = new()
  if port_or_name then
    self:openPort(port_or_name)
  end
  return self
end

function lib:sendAt(time, msg)
  local prev = self
  local at_top
  -- Get current top event
  if prev.at_next then
    at_top = prev.at_next.at
  else
    at_top = 0
  end
  msg.at = time
  -- sorted insert (next event first)
  while true do
    local ne = prev.at_next
    if not ne then
      prev.at_next = msg
      msg.at_next = nil
      break
    elseif at < ne.at then
      prev.at_next = msg
      msg.at_next  = ne
      break
    else
      prev = ne
    end
  end
  if time < at_top then
    -- reschedule sender thread
    -- FIXME: code not finished
    assert(false)
    sched:scheduleAt(time, self.thread)
  end
end

local send = lib.send
local decode = lmidi.Message.decode
function lib:send(msg, ...)
  if type(msg) == 'table' then
    if msg[1] then
      -- table is a list = chord
      for _, m in ipairs(msg) do
        if m[1] then
          send(self, unpack(m))
        else
          -- lmidi.Message
          send(self, decode(m))
        end
      end
    else
      -- lmidi.Message
      send(self, decode(msg))
    end
  elseif msg then
    send(self, msg, ...)
  end
end

-- Length must be in seconds.
function lib:sendNote(chan, note, velo, length)
  send(self, chan -1 + 0x90, note, velo)
  if length then
    -- FIXME: should optimize to avoid creating one thread per note !
    lk.Thread(function()
      send(self, chan -1 + 0x80, note, 0)
    end, now() + length)
  end
end
lib.sendNoteOn = lib.sendNote

function lib:sendNoteOff(chan, note, velo)
  send(self, chan -1 + 0x80, note, velo or 0)
end

function lib:sendCtrl(chan, ctrl, value)
  send(self, chan -1 + 0xB0, ctrl, value)
end

return lib

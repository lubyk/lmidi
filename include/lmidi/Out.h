/*
  ==============================================================================

   This file is part of the LUBYK project (http://lubyk.org)
   Copyright (c) 2007-2011 by Gaspard Bucher (http://teti.ch).

  ------------------------------------------------------------------------------

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
   THE SOFTWARE.

  ==============================================================================
*/
#ifndef LUBYK_INCLUDE_LMIDI_OUT_H_
#define LUBYK_INCLUDE_LMIDI_OUT_H_

#include "RtMidi.h"

namespace lmidi {
/** This class lets you send midi events through virtual ports (where possible)
 * or connect to midi receivers.
 *
 * @dub push: dub_pushobject
 *      string_format:'%%s (%%f)'
 *      string_args:'self->portName(), self->port()'
 */
class Out : public dub::Thread {
public:
  Out()
     : port_id_(-1)
     , port_name_("lubyk")
     , midi_out_(NULL)
     , buffer_(3, 0) {
    midi_out_ = new RtMidiOut;
  }

  ~Out() {
    if (midi_out_) {
      midi_out_->closePort();
      delete midi_out_;
    }
  }

  int port() const {
    return port_id_;
  }

  const char *portName() const {
    return port_name_.c_str();
  }

  void openPort(int port, lua_State *L) {
    if (midi_out_ == NULL) {
      lua_pushstring(L, "RtMidiOut not initialized: cannot open port.");
      lua_error(L);
    }
    midi_out_->closePort();

    if (port == -1) {
      // create a virtual port
      midi_out_->openVirtualPort(port_name_);
    } else {
      // try to connect to the given port
      // zero based index
      midi_out_->openPort(port - 1);
      port_name_ = midi_out_->getPortName(port - 1);
    }
    port_id_ = port;
  }

  void openPort(const char *port_name, lua_State *L) {
    // 1. find port from given name
    int port_count = midi_out_->getPortCount();
    std::string name;

    for (int i = 0; i < port_count; ++i) {
      name = midi_out_->getPortName(i);
      if (name == port_name) {
        return openPort(i + 1, L);
      }
    }
    lua_pushfstring(L, "Port '%s' not found.", port_name);
    lua_error(L);
  }

  void virtualPort(const char *port_name, lua_State *L) {
    port_name_ = port_name;
    return openPort(-1, L);
  }

  void send(int a, int b, int c) {
    if (!midi_out_) return;
    buffer_[0] = a;
    buffer_[1] = b;
    buffer_[2] = c;
    midi_out_->sendMessage(&buffer_);
  }

  /** List of midi output ports.
   */
  static LuaStackSize ports(lua_State * L) {
    RtMidiOut midi_out;
    int count = midi_out.getPortCount();
    lua_newtable(L);
    int tp = lua_gettop(L);
    for(int i = 0; i < count; ++i) {
      std::string name = midi_out.getPortName(i);
      lua_pushlstring(L, name.c_str(), name.length());
      lua_rawseti(L, tp, i + 1);
    }
    return 1;
  }
private:

  /** Midi port id to which the element is connected.
   *  If the value is -1 this means it has opened its own virtual port.
   */
  int port_id_;

  /** The connected port name.
   */
  std::string port_name_;

  /** Pointer to our RtMidiOut instance (lmidi::Out is just a wrapper around
   *  RtMidiOut).
   */
  RtMidiOut *midi_out_;

  /** Message sending buffer.
   * TODO: modify RtMidiOut so we do not need this.
   */
  std::vector<unsigned char> buffer_;
};

} // lmidi

#endif // LUBYK_INCLUDE_LMIDI_OUT_H_

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
#ifndef LUBYK_INCLUDE_LMIDI_IN_H_
#define LUBYK_INCLUDE_LMIDI_IN_H_

#include "RtMidi.h"
#include "lk/Fifo.h"
#include <iostream>

namespace lmidi {
  typedef std::vector<unsigned char> MsgVector;

/** This class lets you receive midi events through virtual ports (where possible)
 * or connect to midi senders and receive midi data from them.
 *
 * @dub push: dub_pushobject
 *      string_format:'%%s'
 *      string_args:'self->portName()'
 *      super: lk.FifoMethods
 */
class In : public lk::Fifo<MsgVector>, public dub::Thread {

  /** Midi port id to which the element is connected.
   *  If the value is -1 this means it has opened its own virtual port.
   */
  int port_id_;

  /** The connected port name.
   */
  std::string port_name_;

  /** Pointer to our RtMidiIn instance (lmidi::In is just a wrapper around
   *  RtMidiIn).
   */
  RtMidiIn *midi_in_;

public:
  In()
      : port_id_(-1),
        port_name_("lubyk"),
        midi_in_(NULL) {

    midi_in_ = new RtMidiIn;

    // set callback
    midi_in_->setCallback(In::sCallback, (void*)this);
  }

  ~In() {
    if (midi_in_) {
      midi_in_->closePort();
      delete midi_in_;
    }
  }

  int port() const {
    return port_id_ >= 0 ? port_id_ + 1 : port_id_;
  }

  const char *portName() const {
    return port_name_.c_str();
  }

  void openPort(int port) {
    // 1-based indexing API
    if (port > 0) port = port - 1;
    if (midi_in_ == NULL) {
      throw dub::Exception("RtMidiIn not initialized: cannot open port.");
    }
    midi_in_->closePort();

    if (port == -1) {
      // create a virtual port
      midi_in_->openVirtualPort(port_name_);
    } else {
      // try to connect to the given port
      try {
        midi_in_->openPort(port);
      } catch (RtMidiError &e) {
        if (e.getType() == RtMidiError::INVALID_PARAMETER) {
          throw dub::Exception("Invalid port number %i.", port >= 0 ? port + 1 : port);
        } else {
          throw;
        }
      }
      port_name_ = midi_in_->getPortName(port);
    }
    port_id_ = port;
  }

  void openPort(const char *port_name) {
    // 1. find port from given name
    int port_count = midi_in_->getPortCount();
    std::string name;

    for (int i = 0; i < port_count; ++i) {
      name = midi_in_->getPortName(i);
      if (name == port_name) {
        return openPort(i + 1);
      }
    }
    throw dub::Exception("Port '%s' not found.", port_name);
  }

  void virtualPort(const char *port_name) {
    port_name_ = port_name;
    return openPort(-1);
  }

  /** Change types to ignore. By default all special types are ignored.
   */
  void ignoreTypes( bool midiSysex = true, bool midiTime = true, bool midiSense = true ) {
    midi_in_->ignoreTypes(midiSysex, midiTime, midiSense);
  }

  /** List of midi input ports.
   */
  static LuaStackSize ports(lua_State * L) {
    RtMidiIn midi_in;
    int count = midi_in.getPortCount();
    lua_newtable(L);
    int tp = lua_gettop(L);
    for(int i = 0; i < count; ++i) {
      std::string name = midi_in.getPortName(i);
      lua_pushlstring(L, name.c_str(), name.length());
      lua_rawseti(L, tp, i + 1);
    }
    return 1;
  }

protected:

  virtual LuaStackSize unpack(lua_State *L, MsgVector *message) {
    size_t sz = message->size();
    for(size_t i=0; i < sz; ++i) {
      lua_pushnumber(L, message->at(i));
    }
    return sz;
  }

private:

  /** Static callback to trigger when new messages arrive.
   */
  static void sCallback(double timestamp, MsgVector *message, void *data) {
    ((In*)data)->receive(timestamp, message);
  }

  inline void receive(double timestamp, MsgVector *message) {
    // push a copy
    if (!push(new MsgVector(*message))) {
      // data deleted by Fifo.
      fprintf(stderr, "Midi message buffer full !\n");
    }
  }


  // static bool input_list(std::ostream * pOutput, std::vector<std::string>& ports)
  // {
  //   RtMidiIn *midiout = 0;
  //   unsigned int i,nPorts;
  //   std::string portName;
  //
  //   try {
  //     midiout = new RtMidiIn();
  //   }
  //   catch (RtMidiError &error) {
  //     *pOutput << error.getMessageString() << std::endl;
  //     return false;
  //   }
  //
  //   ports.clear();
  //
  //   nPorts = midiout->getPortCount();
  //
  //   for ( i=0; i<nPorts; i++ ) {
  //     try {
  //       portName = midiout->getPortName(i);
  //       ports.push_back(portName);
  //     } catch (RtMidiError &error) {
  //       *pOutput << error.getMessageString() << std::endl;
  //       return false;
  //     }
  //   }
  //   return true;
  // }
};

} // midi
#endif // LUBYK_INCLUDE_LMIDI_IN_H_

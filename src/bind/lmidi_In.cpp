/**
 *
 * MACHINE GENERATED FILE. DO NOT EDIT.
 *
 * Bindings for class In
 *
 * This file has been generated by dub 2.2.0.
 */
#include "dub/dub.h"
#include "lmidi/In.h"

using namespace lmidi;

/** lmidi::In::In()
 * include/lmidi/In.h:64
 */
static int In_In(lua_State *L) {
  try {
    In *retval__ = new In();
    retval__->dub_pushobject(L, retval__, "lmidi.In", true);
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "new: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "new: Unknown exception");
  }
  return dub::error(L);
}

/** lmidi::In::~In()
 * include/lmidi/In.h:75
 */
static int In__In(lua_State *L) {
  try {
    DubUserdata *userdata = ((DubUserdata*)dub::checksdata_d(L, 1, "lmidi.In"));
    if (userdata->gc) {
      In *self = (In *)userdata->ptr;
      delete self;
    }
    userdata->gc = false;
    return 0;
  } catch (std::exception &e) {
    lua_pushfstring(L, "__gc: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "__gc: Unknown exception");
  }
  return dub::error(L);
}

/** int lmidi::In::port() const
 * include/lmidi/In.h:82
 */
static int In_port(lua_State *L) {
  try {
    In *self = *((In **)dub::checksdata(L, 1, "lmidi.In"));
    lua_pushnumber(L, self->port());
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "port: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "port: Unknown exception");
  }
  return dub::error(L);
}

/** const char* lmidi::In::portName() const
 * include/lmidi/In.h:86
 */
static int In_portName(lua_State *L) {
  try {
    In *self = *((In **)dub::checksdata(L, 1, "lmidi.In"));
    lua_pushstring(L, self->portName());
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "portName: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "portName: Unknown exception");
  }
  return dub::error(L);
}

/** void lmidi::In::openPort(int port)
 * include/lmidi/In.h:90
 */
static int In_openPort(lua_State *L) {
  try {
    In *self = *((In **)dub::checksdata(L, 1, "lmidi.In"));
    int type__ = lua_type(L, 2);
    if (type__ == LUA_TNUMBER) {
      int port = dub::checkint(L, 2);
      self->openPort(port);
      return 0;
    } else {
      const char *port_name = dub::checkstring(L, 2);
      self->openPort(port_name);
      return 0;
    }
  } catch (std::exception &e) {
    lua_pushfstring(L, "openPort: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "openPort: Unknown exception");
  }
  return dub::error(L);
}

/** void lmidi::In::virtualPort(const char *port_name)
 * include/lmidi/In.h:131
 */
static int In_virtualPort(lua_State *L) {
  try {
    In *self = *((In **)dub::checksdata(L, 1, "lmidi.In"));
    const char *port_name = dub::checkstring(L, 2);
    self->virtualPort(port_name);
    return 0;
  } catch (std::exception &e) {
    lua_pushfstring(L, "virtualPort: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "virtualPort: Unknown exception");
  }
  return dub::error(L);
}

/** void lmidi::In::ignoreTypes(bool midiSysex=true, bool midiTime=true, bool midiSense=true)
 * include/lmidi/In.h:138
 */
static int In_ignoreTypes(lua_State *L) {
  try {
    In *self = *((In **)dub::checksdata(L, 1, "lmidi.In"));
    int top__ = lua_gettop(L);
    if (top__ >= 4) {
      bool midiSysex = dub::checkboolean(L, 2);
      bool midiTime = dub::checkboolean(L, 3);
      bool midiSense = dub::checkboolean(L, 4);
      self->ignoreTypes(midiSysex, midiTime, midiSense);
      return 0;
    } else if (top__ >= 3) {
      bool midiSysex = dub::checkboolean(L, 2);
      bool midiTime = dub::checkboolean(L, 3);
      self->ignoreTypes(midiSysex, midiTime);
      return 0;
    } else if (top__ >= 2) {
      bool midiSysex = dub::checkboolean(L, 2);
      self->ignoreTypes(midiSysex);
      return 0;
    } else {
      self->ignoreTypes();
      return 0;
    }
  } catch (std::exception &e) {
    lua_pushfstring(L, "ignoreTypes: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "ignoreTypes: Unknown exception");
  }
  return dub::error(L);
}

/** static LuaStackSize lmidi::In::ports(lua_State *L)
 * include/lmidi/In.h:144
 */
static int In_ports(lua_State *L) {
  try {
    return In::ports(L);
  } catch (std::exception &e) {
    lua_pushfstring(L, "ports: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "ports: Unknown exception");
  }
  return dub::error(L);
}

/** int lk::FifoMethods::fd()
 * src/bind_headers/Fifo.h:10
 */
static int In_fd(lua_State *L) {
  try {
    In *self = *((In **)dub::checksdata(L, 1, "lmidi.In"));
    lua_pushnumber(L, self->fd());
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "fd: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "fd: Unknown exception");
  }
  return dub::error(L);
}

/** LuaStackSize lk::FifoMethods::pop(lua_State *L)
 * src/bind_headers/Fifo.h:11
 */
static int In_pop(lua_State *L) {
  try {
    In *self = *((In **)dub::checksdata(L, 1, "lmidi.In"));
    return self->pop(L);
  } catch (std::exception &e) {
    lua_pushfstring(L, "pop: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "pop: Unknown exception");
  }
  return dub::error(L);
}

/** bool lk::FifoMethods::hasMessage()
 * src/bind_headers/Fifo.h:12
 */
static int In_hasMessage(lua_State *L) {
  try {
    In *self = *((In **)dub::checksdata(L, 1, "lmidi.In"));
    lua_pushboolean(L, self->hasMessage());
    return 1;
  } catch (std::exception &e) {
    lua_pushfstring(L, "hasMessage: %s", e.what());
  } catch (...) {
    lua_pushfstring(L, "hasMessage: Unknown exception");
  }
  return dub::error(L);
}



// --=============================================== __tostring
static int In___tostring(lua_State *L) {
  In *self = *((In **)dub::checksdata_n(L, 1, "lmidi.In"));
  lua_pushfstring(L, "lmidi.In: %p (%s)", self, self-> portName() );
  
  return 1;
}

// --=============================================== METHODS

static const struct luaL_Reg In_member_methods[] = {
  { "new"          , In_In                },
  { "__gc"         , In__In               },
  { "port"         , In_port              },
  { "portName"     , In_portName          },
  { "openPort"     , In_openPort          },
  { "virtualPort"  , In_virtualPort       },
  { "ignoreTypes"  , In_ignoreTypes       },
  { "ports"        , In_ports             },
  { "fd"           , In_fd                },
  { "pop"          , In_pop               },
  { "hasMessage"   , In_hasMessage        },
  { "__tostring"   , In___tostring        },
  { "deleted"      , dub::isDeleted       },
  { NULL, NULL},
};


extern "C" int luaopen_lmidi_In(lua_State *L)
{
  // Create the metatable which will contain all the member methods
  luaL_newmetatable(L, "lmidi.In");
  // <mt>

  // register member methods
  dub::fregister(L, In_member_methods);
  // setup meta-table
  dub::setup(L, "lmidi.In");
  // <mt>
  return 1;
}
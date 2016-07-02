#pragma once


#ifdef _WIN32
  #ifndef WIN32_LEAN_AND_MEAN
    #define WIN32_LEAN_AND_MEAN
    #define SINGLESPEED_USE_WIN32_LEAN_AND_MEAN
  #endif
  #include <windows.h>
  #include <GL/gl.h>
  #ifdef SINGLESPEED_USE_WIN32_LEAN_AND_MEAN
    #undef WIN32_LEAN_AND_MEAN
  #endif
#else
  #include <OpenGL/gl.h>
#endif


#include "linmath.h"

#include "event.hpp"
#include "core_events.hpp"
#include "app.hpp"
#include "shader.hpp"
#include "gl_wrap.hpp"
#include "texture2d.hpp"
#include "renderer2d.hpp"
#include "vbo.hpp"
#include "ibo.hpp"
#include "fbo.hpp"
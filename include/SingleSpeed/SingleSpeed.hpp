#pragma once

#ifndef SINGLE_SPEED_BUILDINDG
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
#endif

#include <string>
#include <vector>

#include "linmath.h"

#include "event.hpp"
#include "core_events.hpp"
#include "window_settings.hpp"
#include "app.hpp"
#include "shader.hpp"
#include "gl_wrap.hpp"
#include "gl_info.hpp"
#include "texture2d.hpp"
#include "renderer2d.hpp"
#include "vbo.hpp"
#include "ibo.hpp"
#include "fbo.hpp"

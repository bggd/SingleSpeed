#pragma once

#ifndef SINGLE_SPEED_BUILDINDG
  #ifdef __APPLE__
    #include <OpenGL/gl.h> 
  #else
    #ifdef _WIN32
      #define WIN32_LEAN_AND_MEAN
      #include <windows.h>
    #endif
    #include <gl/gl.h>
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

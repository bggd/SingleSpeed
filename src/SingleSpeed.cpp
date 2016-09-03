#ifdef _WIN32
  #include <SDL.h>
#else
  #include <SDL2/SDL.h>
#endif

#include <iostream>
#include <string>

#define SINGLE_SPEED_BUILDING
#include "../dependencies/glad/include/glad/glad.h"
#include "../include/SingleSpeed/SingleSpeed.hpp"

#include "event.cpp"
#include "core_events.cpp"
#include "shader.cpp"
#include "gl_wrap.cpp"
#include "gl_info.cpp"
#include "renderer2d.cpp"
#include "renderer2d_glsl.cpp"
#include "vbo.cpp"
#include "ibo.cpp"
#include "fbo.cpp"
#include "texture2d.cpp"
#include "app.cpp"

#include "../dependencies/glad/src/glad.c"

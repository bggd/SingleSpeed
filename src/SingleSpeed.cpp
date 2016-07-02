#ifdef _WIN32
  #include <SDL.h>
#else
  #include <SDL2/SDL.h>
#endif

#include <iostream>
#include <string>

#include "../include/SingleSpeed/SingleSpeed.hpp"

#include "../dependencies/glad/include/glad/glad.h"

#include "event.cpp"
#include "core_events.cpp"
#include "shader.cpp"
#include "gl_wrap.cpp"
#include "renderer2d.cpp"
#include "vbo.cpp"
#include "ibo.cpp"
#include "fbo.cpp"
#include "texture2d.cpp"
#include "app.cpp"

#include "../dependencies/glad/src/glad.c"

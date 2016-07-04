App* AppStack::current = nullptr;
std::vector<App*> AppStack::stack;

static void gl_debug_cb(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* msg, const void* data)
{
  std::cerr << "gl_debug_cb" << msg << std::endl;
}

void process_event(SDL_Event& ev)
{
  if (ev.type == SDL_MOUSEMOTION) {
    MouseEventArgs arg;
    arg.type = MouseEventArgs::Type::Moved;
    arg.x = ev.motion.x;
    arg.y = ev.motion.y;
    CoreEvents::events.mouse_moved.notify(arg);
  }
  else if (ev.type == SDL_MOUSEBUTTONDOWN) {
    MouseEventArgs arg;
    arg.type = MouseEventArgs::Type::Pressed;
    arg.x = ev.button.x;
    arg.y = ev.button.y;
    CoreEvents::events.mouse_pressed.notify(arg);
  }
  else if (ev.type == SDL_MOUSEBUTTONUP) {
    MouseEventArgs arg;
    arg.type = MouseEventArgs::Type::Released;
    arg.x = ev.button.x;
    arg.y = ev.button.y;
    CoreEvents::events.mouse_released.notify(arg);
  }
}

void AppStack::run(const WindowSettings& settings)
{
  SDL_LogSetAllPriority(SDL_LOG_PRIORITY_VERBOSE);

  SDL_Init(SDL_INIT_EVERYTHING);

  SDL_Window* window;
  SDL_GLContext glcontext;

  //SDL_GL_UnloadLibrary();
  //SDL_GL_LoadLibrary(NULL);

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
  //SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  //SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

  window = SDL_CreateWindow(settings.title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, settings.width, settings.height, SDL_WINDOW_OPENGL);
  if (window == NULL) goto game_over;
  glcontext = SDL_GL_CreateContext(window);
  if (glcontext == NULL) goto game_over;

  SDL_GL_MakeCurrent(window, glcontext);

  int profile;
  SDL_GL_GetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, &profile);
  GLInfo::is_gles2 = (profile == SDL_GL_CONTEXT_PROFILE_ES);
  std::cout <<  GLInfo::is_gles2 << '\n';
  SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &GLInfo::major);
  SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &GLInfo::minor);

  if (GLInfo::is_gles2) {
    if (!gladLoadGLES2Loader((GLADloadproc)SDL_GL_GetProcAddress)) goto game_over;
  }
  else {
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) goto game_over;
  }

  if (!SDL_GL_SetSwapInterval(-1)) SDL_GL_SetSwapInterval(1);

  std::cout << GLInfo::major << "." << GLInfo::minor << std::endl;
  std::cout << GLVersion.major << "." << GLVersion.minor << std::endl;

  glDebugMessageCallback(gl_debug_cb, NULL);
  glEnable(GL_DEBUG_OUTPUT);

  GLuint VAO;

  if (!GLInfo::is_gles2) {
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
  }

  for (;;) {
    if (AppStack::current == nullptr) break;
    AppStack::current->enter_frame();

    SDL_Event ev;
    while (SDL_PollEvent(&ev)) {
      if (ev.type == SDL_QUIT) goto game_over; 
      process_event(ev);
    }

    if (AppStack::current == nullptr) break;
    AppStack::current->update();
    if (AppStack::current == nullptr) break;
    AppStack::current->draw();

    SDL_GL_SwapWindow(window);

    if (AppStack::current == nullptr) break;
    AppStack::current->exit_frame();
  }

game_over:

  if (!GLInfo::is_gles2) {
    glDeleteVertexArrays(1, &VAO);
  }

  SDL_Quit();
}

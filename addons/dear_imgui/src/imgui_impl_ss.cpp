#include "../libs/imgui/imgui.h"
#include "../libs/imgui/imgui.cpp"
#include "../libs/imgui/imgui_draw.cpp"
#include "../libs/imgui/imgui_demo.cpp"

#include "../include/imgui_impl_ss.hpp"

#include <SingleSpeed/SingleSpeed.hpp>

#ifdef _WIN32
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

#include <cstddef> // ofsetof
#include <iostream>


using namespace ss;

static VBO* g_VboHandle = NULL;
static IBO* g_ElementsHandle = NULL;
static Texture2D* g_FontTexture = NULL;

static std::unique_ptr<EventListener> g_MousePressed;
static std::unique_ptr<EventListener> g_MouseMoved;
static std::unique_ptr<EventListener> g_MouseReleased;
static std::unique_ptr<EventListener> g_MouseScrolled;


static void ImGui_ImplSS_RenderDrawLists(ImDrawData* draw_data)
{
  ImGuiIO& io = ImGui::GetIO();
  int fb_width = (int)(io.DisplaySize.x * io.DisplayFramebufferScale.x);
  int fb_height = (int)(io.DisplaySize.y * io.DisplayFramebufferScale.y);
  if (fb_width == 0 || fb_height == 0) return;
  draw_data->ScaleClipRects(io.DisplayFramebufferScale);

  gl::viewport(0, 0, fb_width, fb_height);
  for (int n = 0; n < draw_data->CmdListsCount; n++) {
    const ImDrawList* cmd_list = draw_data->CmdLists[n];
    const ImDrawIdx* idx_buffer_offset = 0;

    g_VboHandle->bind();

    g_VboHandle->vertex_attrib_pointer(Renderer2D::POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(ImDrawVert), (const GLvoid*)offsetof(ImDrawVert, pos));
    g_VboHandle->vertex_attrib_pointer(Renderer2D::UV, 2, GL_FLOAT, GL_FALSE, sizeof(ImDrawVert), (const GLvoid*)offsetof(ImDrawVert, uv));
    g_VboHandle->vertex_attrib_pointer(Renderer2D::COLOR, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(ImDrawVert), (const GLvoid*)offsetof(ImDrawVert, col));

    g_VboHandle->buffer_data(cmd_list->VtxBuffer.size()*sizeof(ImDrawVert), &cmd_list->VtxBuffer.front(), VBO::STREAM_DRAW);

    g_ElementsHandle->bind();
    g_ElementsHandle->buffer_data(cmd_list->IdxBuffer.size()*sizeof(ImDrawIdx), &cmd_list->IdxBuffer.front(), VBO::STREAM_DRAW);

    for (const ImDrawCmd* pcmd = cmd_list->CmdBuffer.begin(); pcmd != cmd_list->CmdBuffer.end(); pcmd++) {
      if (pcmd->UserCallback) {
        pcmd->UserCallback(cmd_list, pcmd);
      }
      else {
        static Texture2D* tex = (Texture2D*)malloc(sizeof(Texture2D));
        tex->id = (GLuint)(intptr_t)pcmd->TextureId;
        tex->bind();
        gl::scissor((GLint)pcmd->ClipRect.x, (GLint)(fb_height - pcmd->ClipRect.w), (GLsizei)(pcmd->ClipRect.z-pcmd->ClipRect.x), (GLsizei)(pcmd->ClipRect.w - pcmd->ClipRect.y));
        g_ElementsHandle->draw_elements(GL_TRIANGLES, pcmd->ElemCount, sizeof(ImDrawIdx) == 2 ? GL_UNSIGNED_SHORT : GL_UNSIGNED_INT, idx_buffer_offset);
      }
      idx_buffer_offset += pcmd->ElemCount;
    }
  }

  g_VboHandle->unbind();
  g_ElementsHandle->unbind();
  gl::scissor(0, 0, fb_width, fb_height);
}

bool ImGui_ImplSS_Init()
{
  ImGuiIO& io = ImGui::GetIO();

  io.RenderDrawListsFn = ImGui_ImplSS_RenderDrawLists;

  return true;
}

void ImGui_ImplSS_Shutdown()
{
  ImGui_ImplSS_InvalidateDeviceObjects();
  ImGui::Shutdown();
}

void ImGui_ImplSS_NewFrame()
{
  if (!g_FontTexture) ImGui_ImplSS_CreateDeviceObjects();

  ImGuiIO& io = ImGui::GetIO();

  int w, h;
  int display_w, display_h;
  SDL_Window* window = SDL_GL_GetCurrentWindow();
  SDL_GetWindowSize(window, &w, &h);
  SDL_GL_GetDrawableSize(window, &display_w, &display_h);
  io.DisplaySize = ImVec2((float)w, (float)h);
  io.DisplayFramebufferScale = ImVec2((float)display_w/w, (float)display_h/h);
  ImGui::NewFrame();
}

bool ImGui_ImplSS_CreateDeviceObjects()
{
  ImGuiIO& io = ImGui::GetIO();
  unsigned char* pixels;
  int width, height;
  io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);

  g_FontTexture = new Texture2D;
  g_FontTexture->bind();
  g_FontTexture->tex_parameteri(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  g_FontTexture->tex_parameteri(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  g_FontTexture->upload_rgba8(width, height, pixels);
  g_FontTexture->unbind();

  io.Fonts->TexID = (void*)(intptr_t)g_FontTexture->id;

  g_VboHandle = new VBO;
  g_ElementsHandle = new IBO;

  g_MousePressed = CoreEvents::mouse_pressed.make_listener(
      [](MouseEventArgs& arg)
      {
        ImGui::GetIO().MousePos = ImVec2((float)arg.x, (float)arg.y);
        ImGui::GetIO().MouseDown[0] = true;
      }
      );

  g_MouseMoved = CoreEvents::mouse_moved.make_listener(
      [](MouseEventArgs& arg)
      {
        ImGui::GetIO().MousePos = ImVec2((float)arg.x, (float)arg.y);
      }
      );

  g_MouseReleased = CoreEvents::mouse_released.make_listener(
      [](MouseEventArgs& arg)
      {
        ImGui::GetIO().MousePos = ImVec2((float)arg.x, (float)arg.y);
        ImGui::GetIO().MouseDown[0] = false;
      }
      );

  g_MouseScrolled = CoreEvents::mouse_scrolled.make_listener(
      [](MouseEventArgs& arg)
      {
        ImGui::GetIO().MouseWheel = (float)arg.scroll_y;
      }
      );

  return true;
}

void ImGui_ImplSS_InvalidateDeviceObjects()
{
  if (g_VboHandle) {
    delete g_VboHandle;
    g_VboHandle = NULL;
  }
  if (g_ElementsHandle) {
    delete g_ElementsHandle;
    g_ElementsHandle = NULL;
  }
  if (g_FontTexture) {
    delete g_FontTexture;
    ImGui::GetIO().Fonts->TexID = 0;
    g_FontTexture = NULL;
  }

  g_MousePressed.reset();
  g_MouseMoved.reset();
  g_MouseReleased.reset();
  g_MouseScrolled.reset();
}

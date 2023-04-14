#include "window.hpp"

#include "raylib.h"

namespace Window
{
  int width{1280};
  int height{720};
  std::string title{"tetris"};
}

void Window::Tick()
{
  if (IsKeyDown(KEY_LEFT_ALT) && IsKeyPressed(KEY_ENTER)) {
    ToggleFullscreen();
  }

  if (IsWindowResized()) {
    Window::width = GetScreenWidth();
    Window::height = GetScreenHeight();
  }

  if (Window::width != GetScreenWidth()) {
    SetWindowSize(Window::width, Window::height);
  }
}
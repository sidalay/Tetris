#include "window.hpp"

void Window::Tick()
{
  if (IsKeyDown(KEY_LEFT_ALT) && IsKeyPressed(KEY_ENTER)) {
    ToggleFullscreen();
  }

  if (width != GetScreenWidth()) {
    SetWindowSize(width, height);
  }
}
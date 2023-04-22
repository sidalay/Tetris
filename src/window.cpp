#include "window.hpp"

#include "raylib.h"

namespace Window
{
  int width{1280};
  int height{720};
  std::string title{"tetris"};
  const float cell_size_percentage{1.f/26.f};            // 100% / # of cells 
  const float well_width{10.f * cell_size_percentage};   // # of cells wide
  const float well_height{20.f * cell_size_percentage};  // # of cells high
  const float h_margin{cell_size_percentage * 3.f};      // height margin = # of cells
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
#include "matrix.hpp"

const float cell_size{.045f}; // 4.5% of height 
const float well_width{10.f * cell_size}; // 10 cells wide
const float w_margin{(1.f - well_width) * .5f}; // 22.5% margin
const float h_margin{.05f}; // 5% from top/bottom of screen
const float well_height{1 - (h_margin * 2.f)}; // 90% of height
const float frame_spacing{cell_size};  

Playfield::Playfield()
  : border{
      Window::width * ((1.f - ((Window::height * well_width)/Window::width)) * .5f),
      Window::height * h_margin,
      Window::height * well_width,
      Window::height * well_height
    }
{
  InitializeMatrix();
}

void Playfield::Tick()
{
  UpdateFrames();
  UpdateMatrix();
}

void Playfield::Draw()
{
  DrawMatrix();
  DrawBorder();
}

void Playfield::DrawBorder()
{
  DrawRectangleLinesEx(border.area, 1.f, Color{ 78, 78, 78, 100 });
}

void Playfield::DrawMatrix()
{
  for (auto& row : matrix) {
    for (auto& col : row) {
      DrawRectangle(
        col.area.x, 
        col.area.y, 
        col.area.width, 
        col.area.height, 
        col.color);
      DrawRectangleLinesEx(col.area, 2.f, Color{ 48, 48, 48, 100 });
    }
  }
}

void Playfield::DrawHold()
{
  DrawRectangleLinesEx(hold.area, 1.f, Color{ 78, 78, 78, 100 });
}

void Playfield::DrawNext()
{

}

void Playfield::DrawPreview()
{
  
}

void Playfield::InitializeMatrix()
{
  for (int y{}; y < matrix.size() - 4; ++y) {
    for (int x{0}; x < matrix[y].size(); ++x) {
      if (y % 2 == 0) {
        matrix[y][x].area.x = border.area.x + ((Window::height * cell_size) * x);
        matrix[y][x].area.y = border.area.y + ((Window::height * cell_size) * y);
        matrix[y][x].area.width = Window::height * cell_size;
        matrix[y][x].area.height = Window::height * cell_size;
        matrix[y][x].color = x % 2 == 0 ? Color{ 15, 14, 14, 255 } : Color{ 20, 19, 19, 255 };
      } else {
        matrix[y][x].area.x = border.area.x + ((Window::height * cell_size) * x);
        matrix[y][x].area.y = border.area.y + ((Window::height * cell_size) * y);
        matrix[y][x].area.width = Window::height * cell_size;
        matrix[y][x].area.height = Window::height * cell_size;
        matrix[y][x].color = x % 2 != 0 ? Color{ 15, 14, 14, 255 } : Color{ 20, 19, 19, 255 };
      }
    }
  }
}

void Playfield::UpdateFrames()
{
  if (IsWindowResized()) {
    border.area.x = Window::width * ((1.f - ((Window::height * well_width)/Window::width)) * .5f);
    border.area.y = Window::height * h_margin;
    border.area.width = Window::height * well_width;
    border.area.height = Window::height * well_height;
  }
}

void Playfield::UpdateMatrix()
{
  if (IsWindowResized()) {
    for (int y{}; y < matrix.size() - 4; ++y) {
      for (int x{0}; x < matrix[y].size(); ++x) {
        if (y % 2 == 0) {
          matrix[y][x].area.x = border.area.x + ((Window::height * cell_size) * x);
          matrix[y][x].area.y = border.area.y + ((Window::height * cell_size) * y);
          matrix[y][x].area.width = Window::height * cell_size;
          matrix[y][x].area.height = Window::height * cell_size;
        } else {
          matrix[y][x].area.x = border.area.x + ((Window::height * cell_size) * x);
          matrix[y][x].area.y = border.area.y + ((Window::height * cell_size) * y);
          matrix[y][x].area.width = Window::height * cell_size;
          matrix[y][x].area.height = Window::height * cell_size;
        }
      }
    }
  }
}

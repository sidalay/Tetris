#include "matrix.hpp"

const float cell_size{1.f/22.f};            // 100% / 22 cells 
const float well_width{10.f * cell_size};   // 10 cells wide
const float well_height{20.f * cell_size};  // 20 cells high
const float h_margin{cell_size};            // height margin = 1 cell
const float frame_spacing{cell_size};
const Color frame_color{78, 78, 78, 100};
const Color cell_color_one{15, 14, 14, 255};
const Color cell_color_two{20, 19, 19, 255};
const Color cell_color_lines{48, 48, 48, 100};

Playfield::Playfield()
{
  InitializeFrames();
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
  DrawFrames();
}

void Playfield::DrawFrames()
{
  DrawRectangleLinesEx(frames.at(0).area, 1.f, frame_color);
  DrawRectangleLinesEx(frames.at(1).area, 1.f, frame_color);
  DrawRectangleLinesEx(frames.at(2).area, 1.f, frame_color);
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
      DrawRectangleLinesEx(col.area, 2.f, cell_color_lines);
    }
  }
}

void Playfield::DrawSideMatrix()
{

}

void Playfield::InitializeFrames()
{
  frames.at(0).area.x = (Window::width - (well_width * Window::height)) * .5f,
  frames.at(0).area.y = Window::height * h_margin;
  frames.at(0).area.width = Window::height * well_width;
  frames.at(0).area.height = Window::height * well_height;

  frames.at(1).area.x = frames.at(0).area.x - (Window::height * cell_size) * 6.f;
  frames.at(1).area.y = frames.at(0).area.y;
  frames.at(1).area.width = Window::height * cell_size * 5.f;
  frames.at(1).area.height = Window::height * cell_size * 5.f;

  frames.at(2).area.x = frames.at(0).area.x + (Window::height * cell_size) * 11.f;
  frames.at(2).area.y = frames.at(0).area.y;
  frames.at(2).area.width = Window::height * cell_size * 5.f;
  frames.at(2).area.height = Window::height * cell_size * 5.f;
}

void Playfield::InitializeMatrix()
{
  for (int y{}; y < matrix.size() - 4; ++y) { // draw 20 cells instead of 24
    for (int x{}; x < matrix[y].size(); ++x) {
      if (y % 2 == 0) {
        matrix[y][x].area.x = frames.at(0).area.x + ((Window::height * cell_size) * x);
        matrix[y][x].area.y = frames.at(0).area.y + ((Window::height * cell_size) * y);
        matrix[y][x].area.width = Window::height * cell_size;
        matrix[y][x].area.height = Window::height * cell_size;
        matrix[y][x].color = x % 2 == 0 ? cell_color_one : cell_color_two;
      } else {
        matrix[y][x].area.x = frames.at(0).area.x + ((Window::height * cell_size) * x);
        matrix[y][x].area.y = frames.at(0).area.y + ((Window::height * cell_size) * y);
        matrix[y][x].area.width = Window::height * cell_size;
        matrix[y][x].area.height = Window::height * cell_size;
        matrix[y][x].color = x % 2 != 0 ? cell_color_one : cell_color_two;
      }
    }
  }
}

void Playfield::UpdateFrames()
{
  if (IsWindowResized()) {
    frames.at(0).area.x = Window::width * ((1.f - ((Window::height * well_width)/Window::width)) * .5f);
    frames.at(0).area.y = Window::height * h_margin;
    frames.at(0).area.width = Window::height * well_width;
    frames.at(0).area.height = Window::height * well_height;

    frames.at(1).area.x = frames.at(0).area.x - (Window::height * cell_size) * 6.f;
    frames.at(1).area.y = frames.at(0).area.y;
    frames.at(1).area.width = Window::height * cell_size * 5.f;
    frames.at(1).area.height = Window::height * cell_size * 5.f;

    frames.at(2).area.x = frames.at(0).area.x + (Window::height * cell_size) * 11.f;
    frames.at(2).area.y = frames.at(0).area.y;
    frames.at(2).area.width = Window::height * cell_size * 5.f;
    frames.at(2).area.height = Window::height * cell_size * 5.f;
  }
}

void Playfield::UpdateMatrix()
{
  if (IsWindowResized()) {
    for (int y{}; y < matrix.size() - 4; ++y) {
      for (int x{}; x < matrix[y].size(); ++x) {
        if (y % 2 == 0) {
          matrix[y][x].area.x = frames.at(0).area.x + ((Window::height * cell_size) * x);
          matrix[y][x].area.y = frames.at(0).area.y + ((Window::height * cell_size) * y);
          matrix[y][x].area.width = Window::height * cell_size;
          matrix[y][x].area.height = Window::height * cell_size;
        } else {
          matrix[y][x].area.x = frames.at(0).area.x + ((Window::height * cell_size) * x);
          matrix[y][x].area.y = frames.at(0).area.y + ((Window::height * cell_size) * y);
          matrix[y][x].area.width = Window::height * cell_size;
          matrix[y][x].area.height = Window::height * cell_size;
        }
      }
    }
  }
}

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
  InitializeMatrices();
}

void Playfield::Tick() 
{
  UpdateFrames();
  UpdateMatrices();
}

void Playfield::Draw()
{
  DrawMatrices();
  DrawFrames();
}

void Playfield::DrawFrames()
{
  DrawRectangleLinesEx(frames.at(0).area, 1.f, frame_color);
  DrawRectangleLinesEx(frames.at(1).area, 1.f, frame_color);
  DrawRectangleLinesEx(frames.at(2).area, 1.f, frame_color);
}

void Playfield::DrawMatrices()
{
  for (auto& frame : frames) {
    for (auto& row : frame.matrix) {
      for (auto& cell : row) {
        DrawRectangle(
          cell.area.x, 
          cell.area.y, 
          cell.area.width, 
          cell.area.height, 
          cell.color);
        DrawRectangleLinesEx(cell.area, 2.f, cell_color_lines);
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

void Playfield::UpdateMatrices()
{
  if (IsWindowResized()) {
    for (auto& frame : frames) {
      for (int y{}; y < frame.grid.y; ++y) {
        for (int x{}; x < frame.grid.x; ++x) {
          if (y % 2 == 0) {
            frame.matrix[y][x].area.x = frame.area.x + ((Window::height * cell_size) * x);
            frame.matrix[y][x].area.y = frame.area.y + ((Window::height * cell_size) * y);
            frame.matrix[y][x].area.width = Window::height * cell_size;
            frame.matrix[y][x].area.height = Window::height * cell_size;
          } else {
            frame.matrix[y][x].area.x = frame.area.x + ((Window::height * cell_size) * x);
            frame.matrix[y][x].area.y = frame.area.y + ((Window::height * cell_size) * y);
            frame.matrix[y][x].area.width = Window::height * cell_size;
            frame.matrix[y][x].area.height = Window::height * cell_size;
          }
        }
      }
    }
  }
}

void Playfield::InitializeFrames()
{
  frames.emplace_back(
    Frame{
      Rectangle{(Window::width - (well_width * Window::height)) * .5f,
        Window::height * h_margin,
        Window::height * well_width,
        Window::height * well_height},
      Vector2{10,20}
  });

  frames.emplace_back(
    Frame{
      Rectangle{frames.at(0).area.x - (Window::height * cell_size) * 6.f,
        frames.at(0).area.y,
        Window::height * cell_size * 5.f,
        Window::height * cell_size * 5.f},
      Vector2{5,5}
  });

  frames.emplace_back(
    Frame{
      Rectangle{frames.at(0).area.x + (Window::height * cell_size) * 11.f,
        frames.at(0).area.y,
        Window::height * cell_size * 5.f,
        Window::height * cell_size * 5.f},
      Vector2{5,5}
  });

  for (auto& row : frames) {
    row.matrix.resize(row.grid.y);
    for (auto& col : row.matrix) {
      col.resize(row.grid.x);
    }
  }
}

void Playfield::InitializeMatrices()
{
  for (auto& frame : frames) {
    for (int y{}; y < frame.grid.y; ++y) {
      for (int x{}; x < frame.grid.x; ++x) {
        if (y % 2 == 0) {
          frame.matrix[y][x].area.x = frame.area.x + ((Window::height * cell_size) * x);
          frame.matrix[y][x].area.y = frame.area.y + ((Window::height * cell_size) * y);
          frame.matrix[y][x].area.width = Window::height * cell_size;
          frame.matrix[y][x].area.height = Window::height * cell_size;
          frame.matrix[y][x].color = x % 2 == 0 ? cell_color_one : cell_color_two;
        } else {
          frame.matrix[y][x].area.x = frame.area.x + ((Window::height * cell_size) * x);
          frame.matrix[y][x].area.y = frame.area.y + ((Window::height * cell_size) * y);
          frame.matrix[y][x].area.width = Window::height * cell_size;
          frame.matrix[y][x].area.height = Window::height * cell_size;
          frame.matrix[y][x].color = x % 2 != 0 ? cell_color_one : cell_color_two;
        }
      }
    }
  }
}
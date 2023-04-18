#include "matrix.hpp"

#include "window.hpp"

const Color frame_color{78, 78, 78, 100};
const Color cell_color_one{15, 14, 14, 255};
const Color cell_color_two{20, 19, 19, 255};
const Color cell_color_lines{48, 48, 48, 100};
const Color cell_color_clear{0, 0, 0, 0};

bool operator==(const Color& lhs, const Color& rhs) 
{
  bool r{lhs.r == rhs.r};
  bool g{lhs.g == rhs.g};
  bool b{lhs.b == rhs.b};
  bool a{lhs.a == rhs.a};

  if (r && g && b && a) {
    return true;
  }
  return false;
} 

Playfield::Playfield()
{
  InitializeFrames();
  InitializeMatrices();
  InitMap();
}

void Playfield::Tick() 
{
  if (IsWindowResized()) {
    UpdateFrames();
    UpdateMatrices();
  }
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
        if (cell.color != cell_color_clear) {
          DrawRectangleLinesEx(cell.area, 2.f, cell_color_lines); 
        }
      }
    }
  }
}

void Playfield::UpdateFrames()
{
  float cell_size{Window::height * Window::cell_size_percentage};

  frames.at(0).area.x = Window::width * ((1.f - ((Window::height * Window::well_width)/Window::width)) * .5f);
  frames.at(0).area.y = Window::height * Window::h_margin;
  frames.at(0).area.width = Window::height * Window::well_width;
  frames.at(0).area.height = Window::height * Window::well_height;

  frames.at(1).area.x = frames.at(0).area.x - cell_size * 6.f;
  frames.at(1).area.y = frames.at(0).area.y;
  frames.at(1).area.width = cell_size * 5.f;
  frames.at(1).area.height = cell_size * 5.f;

  frames.at(2).area.x = frames.at(0).area.x + cell_size * 11.f;
  frames.at(2).area.y = frames.at(0).area.y;
  frames.at(2).area.width = cell_size * 5.f;
  frames.at(2).area.height = cell_size * 5.f;
}

void Playfield::UpdateMatrices()
{
  float cell_size{Window::height * Window::cell_size_percentage};

  for (auto& frame : frames) {
    for (int y{}; y < frame.grid.y; ++y) {
      for (int x{}; x < frame.grid.x; ++x) {
        UpdateCells(frame, y, x);
      }
    }
  }
}

void Playfield::InitializeFrames()
{
  float cell_size{Window::height * Window::cell_size_percentage};
  frames.emplace_back(
    Frame{
      Rectangle{
        (Window::width - (Window::well_width * Window::height)) * .5f,
        Window::height * Window::h_margin,
        Window::height * Window::well_width,
        Window::height * Window::well_height},
        Vector2{12,24}
  });

  frames.emplace_back(
    Frame{
      Rectangle{
        frames.at(0).area.x - cell_size * 6.f,
        frames.at(0).area.y,
        cell_size * 5.f,
        cell_size * 5.f},
        Vector2{7,8} // (first,last) column and top three rows are invisible
  });

  frames.emplace_back(
    Frame{
      Rectangle{
        frames.at(0).area.x + cell_size * 11.f,
        frames.at(0).area.y,
        cell_size * 5.f,
        cell_size * 5.f},
        Vector2{7,8} // (first,last) column and top three rows are invisible
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
  for (int i{}; i < frames.size(); ++i) {
    for (int y{}; y < frames[i].grid.y; ++y) {
      for (int x{}; x < frames[i].grid.x; ++x) {
        if (y >= 0 && y <= 2) { // rows 1-3
          if (x == 0 || x == frames[i].matrix[y].size() - 1) {
            frames[i].matrix[y][x].occupied = true;
          }
          frames[i].matrix[y][x].color = cell_color_clear;
        } else if (x == 0 || x == frames[i].matrix[y].size() - 1) {
          frames[i].matrix[y][x].color = cell_color_clear;
          frames[i].matrix[y][x].occupied = true;
        } else if (i == 0 && y == frames[i].matrix.size() - 1) { // last row
          frames[i].matrix[y][x].color = cell_color_clear;
          frames[i].matrix[y][x].occupied = true;
        } else if (y % 2 == 0) {
          frames[i].matrix[y][x].color = x % 2 == 0 ? cell_color_one : cell_color_two;
        } else {
          frames[i].matrix[y][x].color = x % 2 != 0 ? cell_color_one : cell_color_two;
        }
        InitCells(frames[i], y, x);
      }
    }
  }
}

void Playfield::InitCells(Frame& frame, int row, int col)
{
  float cell_size{Window::height * Window::cell_size_percentage};
  frame.matrix[row][col].area.x = (frame.area.x - cell_size * 1.f) + (cell_size * col);
  frame.matrix[row][col].area.y = (frame.area.y - cell_size * 3.f) + (cell_size * row);
  frame.matrix[row][col].area.width = cell_size;
  frame.matrix[row][col].area.height = cell_size;
}

void Playfield::InitMap()
{
  const std::vector<std::vector<Cell>>& border{frames.at(0).matrix};
  for (int row{}; row < border.size(); ++row) {
    for (int col{}; col < border.at(row).size(); ++col) {
      matrix_map.emplace(std::make_pair(row,col), border[row][col].occupied);
    }
  }
}

void Playfield::UpdateCells(Frame& frame, int row, int col)
{
  InitCells(frame, row, col);
}

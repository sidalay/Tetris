#include "matrix.hpp"
#include "enforcer.hpp"
#include "window.hpp"

#include <algorithm>

const Color frame_color{78, 78, 78, 100};
const Color cell_color_one{15, 14, 14, 255};
const Color cell_color_two{20, 19, 19, 255};
const Color cell_color_lines{48, 48, 48, 100};
const Color cell_color_clear{0, 0, 0, 0};

Playfield::Playfield()
  : tetromino{bag.Pull()}
{
  InitializeFrames();
  InitializeMatrices();
  InitMap();
  handler.UpdateArea(frames[1].area);
}

void Playfield::Tick() 
{
  if (IsWindowResized()) {
    UpdateFrames();
    UpdateMatrices();
    UpdateBlocks();
  }
  CheckLevelUp();
  UpdateHandler();
  tetromino.Tick();
  bag.Tick();

  DrawText(TextFormat("Level: %i", level+1), 20, 20, 20, RAYWHITE);
  DrawText(TextFormat("Lines cleared: %i", lines), 20, 50, 20, RAYWHITE);
  DrawText(TextFormat("Lines needed to clear: %i", (linesToClear[level] + previouslines) - lines), 20, 80, 20, RAYWHITE);
}

void Playfield::Draw()
{
  DrawMatrices();
  DrawFrames();
  DrawHandler();
  DrawBlocks();
  tetromino.Draw();
  bag.Draw();
}

void Playfield::DrawFrames()
{
  float offset{7.f};
  for (auto& frame : frames) {
    Rectangle area{
      frame.area.x - offset, 
      frame.area.y - offset, 
      frame.area.width + (offset + 5.f), 
      frame.area.height + (offset + 5.f)
    };
    // DrawRectangleLinesEx(area, 3.f, RAYWHITE);

    // Left line
    DrawRectangleGradientV(
      area.x, 
      area.y, 
      3, 
      area.height, 
      BLACK, RAYWHITE
    );
    // Right line
    DrawRectangleGradientV(
      area.x + area.width - 2.f, 
      area.y, 
      3, 
      area.height, 
      BLACK, RAYWHITE
    );
    // Bottom line
    DrawLineEx(
      {frame.area.x - offset, frame.area.y + frame.area.height + (offset * 0.5f)}, 
      {frame.area.x + frame.area.width + offset - 2.f, frame.area.y + frame.area.height + (offset * 0.5f)}, 
      3.f, RAYWHITE
    );
  }
  // // Top line
  // DrawLineEx(
  //   {frames[0].area.x - offset + 3.f, frames[0].area.y - offset + 1.f}, 
  //   {frames[0].area.x + frames[0].area.width + offset - 5.f, frames[0].area.y - offset + 1.f}, 
  //   3.f, BLACK
  // );
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
          float offset{2.f};
          Rectangle area{cell.area.x, cell.area.y, cell.area.width - offset, cell.area.height - offset};
          DrawRectangleLinesEx(area, 2.f, cell.outline); 
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
  frames.at(2).area.height = cell_size * 16.f;
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
        Vector2{14,26}
  });

  frames.emplace_back(
    Frame{
      Rectangle{
        frames.at(0).area.x - cell_size * 6.f,
        frames.at(0).area.y,
        cell_size * 5.f,
        cell_size * 5.f},
        Vector2{9,8} // (first,last) column and top three rows are invisible
  });

  frames.emplace_back(
    Frame{
      Rectangle{
        frames.at(0).area.x + cell_size * 11.f,
        frames.at(0).area.y,
        cell_size * 5.f,
        cell_size * 16.f},
        Vector2{9,19} // (first,last) column and top three rows are invisible
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
    float alpha{1.f/frames[i].grid.y};
    Color color_one{15,14,14,static_cast<unsigned char>(255.f*alpha)};
    Color color_two{20,19,19,static_cast<unsigned char>(255.f*alpha)};
    for (int y{}; y < frames[i].grid.y; ++y) {
      for (int x{}; x < frames[i].grid.x; ++x) {
        if (y >= 0 && y <= 2) { // rows 1-3
          if (x == 0 || x > frames[i].matrix[y].size() - 4) {
            frames[i].matrix[y][x].occupied = true;
          }
          frames[i].matrix[y][x].color = cell_color_clear;
        } else if (x == 0 || x > frames[i].matrix[y].size() - 4) {
          frames[i].matrix[y][x].color = cell_color_clear;
          frames[i].matrix[y][x].occupied = true;
        } else if (i == 0 && y > frames[i].matrix.size() - 4) { // last row
          frames[i].matrix[y][x].color = cell_color_clear;
          frames[i].matrix[y][x].occupied = true;
        } else if (y % 2 == 0) {
          frames[i].matrix[y][x].color = x % 2 == 0 ? color_one : color_two;
        } else {
          frames[i].matrix[y][x].color = x % 2 != 0 ? color_one : color_two;
        }
        frames[i].matrix[y][x].outline = Color{48, 48, 48, static_cast<unsigned char>(30.f*alpha)};
        InitCells(frames[i], y, x);
      }
      alpha += 1.f/(frames[i].grid.y - 2.f);
      if (alpha > 1.f) {
        alpha = 1.f;
      }
      color_one.a = static_cast<unsigned char>(255.f*alpha);
      color_two.a = static_cast<unsigned char>(255.f*alpha);
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
      matrix.emplace(std::make_pair(row,col), border[row][col].occupied);
    }
  }
}

void Playfield::UpdateCells(Frame& frame, int row, int col)
{
  InitCells(frame, row, col);
}

void Playfield::UpdateCellState()
{
  for (auto& [key,block] : blocks) {
    matrix.at(key) = true;
  }
}

void Playfield::DrawBlocks()
{
  if (!blocks.empty()) {
    for (auto& [key,block] : blocks) {
      block.Draw();
    }
  }
}

void Playfield::UpdateBlocks()
{
  for (auto& [key,block] : blocks) {
    block.Tick();
  }
}

void Playfield::DrawHandler()
{
  handler.DrawGhost();
  handler.DrawHold();
}

void Playfield::UpdateHandler()
{
  if (IsWindowResized()) {
    handler.UpdateArea(frames[1].area);
  }
  if (handler.UpdateLock()) {
    CaptureBlocks();
    PullTetromino();
  }
  handler.Tick();
}

void Playfield::CaptureBlocks()
{
  auto tetro{tetromino.GetBlocks()};
  std::sort(tetro.begin(), tetro.end());

  for (auto& block : tetro) {
    // store current tetromino blocks in blocks map
    blocks.emplace(std::make_pair(block.screen_row, block.screen_col + 1), block);
    OccupyMatrix(block);
  }
  for (auto& block : tetro) {
    CheckLine(block.screen_row);
  }
}

void Playfield::OccupyMatrix(const Tetro::Block& block)
{
  std::pair key{block.screen_row, block.screen_col + 1};
  // Set the block's cell to occupied
  matrix.at(key) = true;
}

void Playfield::CheckLine(int row)
{
  // check if all cells in the row are occupied
  for (int col{1}; col < 11; ++col) {
    if (matrix.at({row,col}) == false) {
      return;
    }
  }
  ClearLine(row);
}

void Playfield::ClearLine(int row)
{
  for (int col{1}; col < 11; ++col) {
    // remove blocks in this row
    blocks.erase({row,col});
    // switch all cells in this row to unoccupied
    matrix.at({row,col}) = false;
  }
  ++lines;
  DropLine(row);
}

void Playfield::DropLine(int clearedline)
{
  float cell_size{Window::height * Window::cell_size_percentage};
  std::vector<Tetro::Block> newBlocks{};
  
  for (auto iter{blocks.rbegin()}; iter != blocks.rend(); ++iter) {
    Tetro::Block& block{iter->second};
    int row{iter->first.first};
    int col{iter->first.second};
    std::pair key{row, col};
    std::pair nextRow{row + 1, col};

    if (row < clearedline) {
      // check if the cell in the row below is occupied
      if (!matrix.at(nextRow)) {
        // if its not move block down
        block.area.y += cell_size;
        block.screen_row += 1;
        // set previous cell location to unoccupied
        matrix.at(key) = false;
      }
    }
    // store block into vector
    newBlocks.emplace_back(block);
  }

  // clear matrix map
  for (int row{}; row < 23; ++row) {
    for (int col{1}; col < 11; ++col) {
      matrix.at({row,col}) = false;
    }
  }

  // clear blocks map
  blocks.clear();
  
  // fill blocks map with newBlocks
  for (auto& newBlock : newBlocks) {
    blocks.emplace(std::make_pair(newBlock.screen_row, newBlock.screen_col + 1), newBlock);
  }

  // loop through blocks and set their cells to occupied
  UpdateCellState();
}

void Playfield::PullTetromino()
{
  tetromino = bag.Pull();

  if (!Enforcer::MovementIsSafe(tetromino, matrix, Tetro::Movement::DOWN)) {
    GameOver();
  }
}

void Playfield::GameOver()
{
  // clear blocks map
  blocks.clear();

  // clear matrix map
  for (int row{}; row < 23; ++row) {
    for (int col{1}; col < 11; ++col) {
      matrix.at({row,col}) = false;
    }
  }

  // reset handler level
  handler.Reset();
  // reset lines cleared count
  lines = 0;
  previouslines = 0;

  // clear bag and pull new piece
  bag.Reset();
  PullTetromino();
}

void Playfield::CheckLevelUp()
{
  if (level < 20) {
    if (lines >= previouslines + linesToClear[level]) {
      ++level;
      previouslines = lines;
      handler.LevelUp();
    }
  }
}


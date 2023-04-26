#include "matrix.hpp"
#include "enforcer.hpp"
#include "window.hpp"

#include <algorithm>

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
  : tetromino{bag.Pull()}
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
    UpdateBlocks();
  }
  UpdateBag();
  UpdateHold();
  UpdateTetromino();
  Gravity();
  UpdateLock();
}

void Playfield::Draw()
{
  DrawMatrices();
  DrawFrames();
  DrawBag();
  DrawGhost();
  DrawTetromino();
  DrawBlocks();
  DrawHold();
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
      matrix_map.emplace(std::make_pair(row,col), border[row][col].occupied);
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
    matrix_map.at(key) = true;
  }
}

void Playfield::Gravity()
{
  if (!IsKeyDown(KEY_DOWN)) {
    gravitytime += GetFrameTime();
    if (gravitytime >= 1.f) {
      if (Enforcer::MovementIsSafe(tetromino, *this, Tetro::Movement::DOWN)) {
        tetromino.Fall();
        ResetLock();
      }
      gravitytime = 0.f;
    }
  }
}

void Playfield::DrawTetromino()
{
  tetromino.Draw();
}

void Playfield::UpdateTetromino()
{
  tetromino.Tick();
}

void Playfield::DrawHold()
{
  if (hold.GetColor() == Color{0,0,0,0}) {
    return;
  }
  if (lock.hold) {
    hold.Draw(GRAY);
  } else {
    hold.Draw();
  }
}

void Playfield::BagPull()
{
  tetromino = bag.Pull();
}

void Playfield::DrawBag()
{
  float cell_size{Window::height * Window::cell_size_percentage};
  Vector2 area{cell_size * 9.f, cell_size * 4.f};
  const auto& next{bag.View()};
  for (int i{}; i < 3; ++i) {
    if (next[i].GetType() == Tetro::Shape::I) {
      next[i].Draw(Vector2{area.x - (cell_size * 0.5f), area.y - cell_size * 0.5f});
    } else if (next[i].GetType() == Tetro::Shape::O) {
      next[i].Draw(Vector2{area.x - (cell_size * 0.5f), area.y});
    } else {
      next[i].Draw(area);
    }
    area.y += cell_size * 5.f;
  }
}

void Playfield::Hold()
{
  if (lock.hold) {
    return;
  }

  if (hold.GetColor() == Color{0, 0, 0, 0}) {
    hold = tetromino;
    BagPull();
  } else {
    Tetromino temp{hold};
    hold = tetromino;
    tetromino = Tetromino{temp.GetType()};
  }
  hold.SetHoldState({frames[1].area.x, frames[1].area.y});
  lock.hold = true;
}

void Playfield::UpdateHold()
{
  hold.Tick();
  if (IsWindowResized()) {
    hold.SetHoldState({frames[1].area.x, frames[1].area.y});
  }
}

void Playfield::UpdateBag()
{
  bag.Tick();
}

void Playfield::ResetLock()
{
  lock.time = 0.f;
  lock.active = false;
}

void Playfield::UpdateLock()
{
  if (!IsWindowResized()) {
    if (!Enforcer::MovementIsSafe(tetromino, *this, Tetro::Movement::DOWN)) {
      lock.time += GetFrameTime();
      if (lock.time >= lock.delay) {
        lock.active = true;
      }
    } else {
      ResetLock();
    }
  }
  CheckLock();
}

void Playfield::CheckLock()
{
  if (lock.active) {
    CaptureBlocks();
    BagPull();
    ResetLock();
    lock.hold = false;
  }
}

void Playfield::DrawBlocks()
{
  if (!blocks.empty()) {
    float offset{1.f};
    for (auto& [key,block] : blocks) {
      DrawRectangleRec(block.area, block.color);
      Rectangle area{block.area.x - offset, block.area.y - offset, block.area.width + offset, block.area.height + offset};
      DrawRectangleLinesEx(area, 2.f, BLACK);
    }
  }
}

void Playfield::DrawGhost()
{
  if (!IsWindowResized()) {
    float offset{};
    auto  tetro{tetromino.GetBlocks()};
    float cell_size{Window::height * Window::cell_size_percentage};
    Tetromino temp{tetromino};

    while (Enforcer::MovementIsSafe(temp, *this, Tetro::Movement::DOWN)) {
      temp.Move(Tetro::Movement::DOWN);
      ++offset;
    }
    for (auto& block : tetro) {
      Rectangle area{block.area.x, block.area.y + (cell_size * offset), block.area.width, block.area.height};
      if (block.area.y > 25) {
        block.area.y = 25;
      }
      DrawRectangleLinesEx(area, 2.f, Color{ 245, 245, 245, 200 });
    }
  }
}

void Playfield::UpdateBlocks()
{
  float cell_size{Window::height * Window::cell_size_percentage};
  float borderX{(Window::width - (Window::well_width * Window::height)) * .5f};
  for (auto& [key,block] : blocks) {
    block.area.y = cell_size * block.screen_row;
    block.area.x = borderX + (cell_size * block.screen_col); 
    block.area.width = cell_size;
    block.area.height = cell_size;
  }
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
  matrix_map.at(key) = true;
}

void Playfield::CheckLine(int row)
{
  // check if all cells in the row are occupied
  for (int col{1}; col < 11; ++col) {
    if (matrix_map.at({row,col}) == false) {
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
    matrix_map.at({row,col}) = false;
  }
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
      if (!matrix_map.at(nextRow)) {
        // if its not move block down
        block.area.y += cell_size;
        block.screen_row += 1;
        // set previous cell location to unoccupied
        matrix_map.at(key) = false;
      }
    }
    // store block into vector
    newBlocks.emplace_back(block);
  }

  // clear the map
  for (int row{}; row < 23; ++row) {
    for (int col{1}; col < 11; ++col) {
      matrix_map.at({row,col}) = false;
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

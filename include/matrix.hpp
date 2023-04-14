#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "raylib.h"
#include "tetromino.hpp"
#include "window.hpp"

#include <vector>

struct Cell
{
  Rectangle area{};
  Color     color{};
  bool      occupied{};
};

struct Frame
{
  Rectangle area{};
  Vector2   grid{};
  std::vector<std::vector<Cell>> matrix{};
  // Todo: Texture member
};

struct Playfield
{ 
  std::vector<Frame> frames{}; // border, hold, next, preview
  // std::array<std::array<Cell,10>,24> matrix{};

  Playfield();
  void Tick();
  void Draw();
  void DrawFrames();
  void DrawMatrix();
  void DrawSideMatrix(Frame&, int, int);
  void InitializeFrames();
  void InitializeMatrix();
  void UpdateFrames();
  void UpdateMatrix();
};

#endif // MATRIX_HPP
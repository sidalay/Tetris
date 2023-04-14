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
  std::vector<Frame> frames{};

  Playfield();
  void Tick();
  void Draw();
  void DrawFrames();
  void DrawMatrices();
  void UpdateFrames();
  void UpdateMatrices();
  void InitializeFrames();
  void InitializeMatrices();
};

#endif // MATRIX_HPP
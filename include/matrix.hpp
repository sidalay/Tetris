#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "raylib.h"
#include "tetromino.hpp"
#include "window.hpp"

#include <array>

struct Cell
{
  Rectangle area{};
  Color     color{};
  bool      occupied{};
};

struct Frame
{
  Rectangle area{};
  // Todo: Texture member
};

struct Playfield
{
  std::array<Frame,4>                frames{}; // border, hold, next, preview
  std::array<std::array<Cell,10>,24> matrix{};

  Playfield();
  void Tick();
  void Draw();
  void DrawFrames();
  void DrawMatrix();
  void DrawSideMatrix();
  void InitializeFrames();
  void InitializeMatrix();
  void UpdateFrames();
  void UpdateMatrix();
};

#endif // MATRIX_HPP
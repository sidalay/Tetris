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
  Frame border{};
  std::array<std::array<Cell,10>,24> matrix{};

  Playfield();
  void Tick();
  void Draw();
  void DrawBorder();
  void DrawMatrix();
  void DrawSideFrames();
  void DrawPreview();
  void InitializeMatrix();
  void UpdateFrames();
  void UpdateMatrix();
};

#endif // MATRIX_HPP
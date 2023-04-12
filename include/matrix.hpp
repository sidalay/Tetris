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
  // Todo: Texture member
};

struct Playfield
{
  Frame              border{};
  Frame              hold{120, 120};
  Frame              preview{120, 240};
  int                spacing{30};
  Vector2            grid{10, 24};
  std::vector<Cell>  matrix{};

  Playfield();
  void Tick();
  void Draw();
  void DrawBorder();
  void DrawMatrix();
  void DrawHold();
  void DrawPreview();
  void InitializeMatrix();
  void UpdateFrames();
  void UpdateMatrix();
};

// assume for 1280x720 screen 1 Tetromino Square is 30px x 30px 
// grid is 10 wide x 24 high
// 720 / 24 = 30. 30 x 10 = 300. 1280 - 300 = 980. 980 / 2 = 490.
// hold, next should be 5 tetromino square x 5 tetromino square
// preview should be 5 tetromino square x 15 tetromino square (preview 3 pieces)

#endif // MATRIX_HPP
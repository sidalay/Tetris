#ifndef TETROMINO_HPP
#define TETROMINO_HPP

#include "raylib.h"

#include <array>

namespace Tetro 
{
  
enum class Shape 
{
  I, J, L, O, S, T, Z
};

struct Block
{
  Rectangle area{};
  Color color{};
};
  
}

struct Tetromino
{
  Tetromino(Tetro::Shape);

  std::array<Tetro::Block,4> Shape{};

  void Rotate();
};

#endif // TETROMINO_HPP

/*
Cyan I
Blue J
Orange L
Yellow O
Green S
Purple T
Red Z
*/
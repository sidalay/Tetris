#ifndef TETROMINO_HPP
#define TETROMINO_HPP

#include "raylib.h"
#include "window.hpp"

#include <array>
#include <utility>

namespace Tetro 
{
  
enum class Shape 
{
  I, J, L, O, S, T, Z
};

enum class Orientation
{
  UP, DOWN, LEFT, RIGHT
};

struct Block
{
  Rectangle area{};
};
  
}

struct Tetromino
{
public:
  Tetromino(Tetro::Shape);

  void Tick();
  void Draw();
  void Rotate();

public:
  std::array<Tetro::Block,4> blocks{};
  Tetro::Shape               type{};
  Tetro::Orientation         facing{Tetro::Orientation::UP};
  Color                      color{};

private:
  void Drop();
  void InitBlocks();
  void SetSize();
  void SetColor();
  void SetOrigin();
  void SetShape(std::pair<int,int>, std::pair<int,int>, std::pair<int,int>); // std::pair<y,x>
  void SetFollowers();
  void UpdateBlockPos();
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
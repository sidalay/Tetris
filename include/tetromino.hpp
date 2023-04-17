#ifndef TETROMINO_HPP
#define TETROMINO_HPP

#include "raylib.h"

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
  Color     color{};
};
  
}

struct Tetromino
{
public:
  Tetromino(Tetro::Shape);

  void Tick();
  void Draw();
  void Move(Tetro::Orientation);
  void RotateCW();
  void RotateCCW();

private:
  std::array<Tetro::Block,4> blocks{};
  Tetro::Shape               type{};
  Tetro::Orientation         facing{Tetro::Orientation::UP};
  Color                      color{};
  float                      deltatime{};
  float                      updatetime{1.f};

private:
  void Fall();
  void Gravity();
  void InitBlocks();
  void InitSize();
  void InitColor();
  void InitOrigin();
  void SetFollowers();
  void SetShape(std::pair<int,int>, std::pair<int,int>, std::pair<int,int>); // std::pair<x,y>
  void UpdateOriginCW();
  void UpdateOriginCCW();
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
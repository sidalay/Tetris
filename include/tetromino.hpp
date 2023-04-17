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
  void Fall();
  void Move(Tetro::Orientation);
  void RotateCW();
  void RotateCCW();
  std::array<Tetro::Block,4> GetBlocks() const {return blocks;}

private:
  std::array<Tetro::Block,4> blocks{};
  Tetro::Shape               type{};
  Tetro::Orientation         facing{Tetro::Orientation::UP};
  Color                      color{};
  float                      deltatime{};
  float                      updatetime{1.f};

private:
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

/* Gravity multiplier per level
/
/     [ 1 ]	       1.00000
/     [ 2 ]	       0.79300
/     [ 3 ]	       0.61780
/     [ 4 ]	       0.47273
/     [ 5 ]	       0.35520
/     [ 6 ]	       0.26200
/     [ 7 ]	       0.18968
/     [ 8 ]	       0.13473
/     [ 9 ]	       0.09388
/     [ 10 ]       0.06415
/     [ 11 ]       0.04298
/     [ 12 ]       0.02822
/     [ 13 ]       0.01815
/     [ 14 ]       0.01144
/     [ 15 ]       0.00706
/     [ 16 ]       0.00426
/     [ 17 ]       0.00252
/     [ 18 ]       0.00146
/     [ 19 ]       0.00082
/     [ 20 ]       0.00046
*/
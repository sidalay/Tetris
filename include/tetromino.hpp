#ifndef TETROMINO_HPP
#define TETROMINO_HPP

#include "block.hpp"

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

enum class Movement
{
  DOWN, LEFT, RIGHT
};

enum class Rotation
{
  CW, CCW
};

struct Wallkick
{
  int col{};
  int row{};
};

struct Lock
{
  float time{0.70f};
  float delay{0.70f};
  bool  hold{};
  bool  active{};
};
  
}

struct Tetromino
{
public:
  Tetromino() = default;
  Tetromino(Tetro::Shape);

  void Tick();
  void Draw() const;
  void Draw(Color) const;
  void Draw(Vector2);
  void CheckScaling();
  void Fall();
  void Move(Tetro::Movement);
  void Rotate(const Tetro::Rotation);
  void WallKick(const Tetro::Wallkick, const Tetro::Rotation);
  void RotateWallKick(const Tetro::Rotation);
  void SetHoldState(Vector2);
  Color GetColor() const {return color;}
  Tetro::Shape GetType() const {return type;}
  Tetro::Orientation GetOrientation() const {return facing;}
  std::array<Tetro::Block,4> GetBlocks() const {return blocks;}
  std::array<Tetro::Block,4>& GetBlocks() {return blocks;}

private:
  std::array<Tetro::Block,4> blocks{};
  Tetro::Shape               type{};
  Tetro::Orientation         facing{Tetro::Orientation::UP};
  Tetro::Lock                lock{};
  Color                      color{0, 0, 0, 0};

private:
  void InitBlocks();
  void InitBlockSize();
  void InitBlockColor();
  void InitBlockOrigin();
  void SetFollowers();
  void SetShape(std::pair<int,int>, std::pair<int,int>, std::pair<int,int>); // std::pair<x,y>
  void UpdateOriginPos(const Tetro::Rotation);
  void UpdateFollowerPos();
  void UpdateBlockSize();
  void UpdateOriginScale();
  void UpdateRowCol();
  void WallKickMove(Tetro::Wallkick);
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
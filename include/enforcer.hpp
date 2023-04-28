#ifndef ENFORCER_HPP
#define ENFORCER_HPP

#include "matrix.hpp"
#include "tetromino.hpp"


namespace Enforcer
{
  using Map = std::map<std::pair<int,int>,bool>;
  
  bool MovementIsSafe(
    const Tetromino, 
    const Map&, 
    const Tetro::Movement);
  bool RotationIsSafe(
    Tetromino, 
    const Map&, 
    const Tetro::Rotation);
  bool WallkickIsSafe(
    const Tetromino, 
    const Map&, 
    const Tetro::Wallkick);
  Tetro::Wallkick WallKickEval(
    Tetromino, 
    const Map&, 
    const Tetro::Rotation);
  Tetro::Wallkick WallKickTest(
    Tetromino,
    const Map&,
    const std::array<Tetro::Wallkick,4>&&);
};

#endif // ENFORCER_HPP
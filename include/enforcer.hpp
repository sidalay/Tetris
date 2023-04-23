#ifndef ENFORCER_HPP
#define ENFORCER_HPP

#include "matrix.hpp"
#include "tetromino.hpp"

namespace Enforcer
{
  bool MovementIsSafe(
    const Tetromino, 
    const Playfield&, 
    const Tetro::Movement);
  bool RotationIsSafe(
    Tetromino, 
    const Playfield&, 
    const Tetro::Rotation);
  bool WallkickIsSafe(
    const Tetromino, 
    const Playfield&, 
    const Tetro::Wallkick);
  Tetro::Wallkick WallKickEval(
    Tetromino, 
    const Playfield&, 
    const Tetro::Rotation);
  Tetro::Wallkick WallKickTest(
    Tetromino,
    const Playfield&,
    const std::array<Tetro::Wallkick,4>&&);
};

#endif // ENFORCER_HPP
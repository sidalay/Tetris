#ifndef ENFORCER_HPP
#define ENFORCER_HPP

#include "matrix.hpp"
#include "tetromino.hpp"

namespace Enforcer
{
  bool IsBelowSafe(const Tetromino, const Playfield&);
  bool IsSideSafe(const Tetromino, const Playfield&, const Tetro::Orientation);
  Tetro::Wallkick WallKickEval(
    Tetromino, 
    const Playfield&, 
    const Tetro::Orientation, 
    const Tetro::Orientation);
  Tetro::Wallkick WallKickTest(
    Tetromino&,
    const Playfield&,
    const Tetro::Wallkick,
    const Tetro::Wallkick,
    const Tetro::Wallkick,
    const Tetro::Wallkick);
};

#endif // ENFORCER_HPP
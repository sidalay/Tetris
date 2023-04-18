#ifndef ENFORCER_HPP
#define ENFORCER_HPP

#include "matrix.hpp"
#include "tetromino.hpp"

namespace Enforcer
{
  bool IsBelowSafe(const Tetromino, const Playfield&);
  bool IsSideSafe(const Tetromino, const Playfield&, const Tetro::Orientation);
};

#endif // ENFORCER_HPP
#ifndef ENFORCER_HPP
#define ENFORCER_HPP

#include "matrix.hpp"
#include "tetromino.hpp"

namespace Enforcer
{
  bool IsBelowClear(const Tetromino&, const Playfield&);
  bool IsOutOfBounds(const Tetromino&, const Playfield&, const Tetro::Orientation);
};

#endif // ENFORCER_HPP
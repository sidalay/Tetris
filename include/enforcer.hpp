#ifndef ENFORCER_HPP
#define ENFORCER_HPP

#include "matrix.hpp"
#include "tetromino.hpp"

namespace Enforcer
{
  bool CheckOutOfBounds(const Tetromino&, const Playfield&, const Tetro::Orientation);
};

#endif // ENFORCER_HPP
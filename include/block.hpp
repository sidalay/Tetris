#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "raylib.h"

namespace Tetro
{
  struct Gradient
  {
    Color primary{};
    Color secondary{};
  };
  
  struct Block
  {
    Rectangle area{};
    Color     color{};
    Gradient  gradient{};
    int       screen_row{};
    int       screen_col{};

    void Tick();
    void Draw();

    [[nodiscard]] constexpr friend bool operator<(const Block& lhs, const Block& rhs) noexcept {return lhs.screen_row < rhs.screen_row;}
  };
}

#endif // BLOCK_HPP
#include "enforcer.hpp"

#include "window.hpp"

bool Enforcer::CheckOccupancy()
{
  return false;
}

bool Enforcer::CheckOutOfBounds(const Tetromino& t, const Playfield& p, const Tetro::Orientation direction)
{
  float cell_size{Window::height * Window::cell_size};
  auto blocks{t.GetBlocks()};
  auto border{p.GetBorder()};

  if (direction == Tetro::Orientation::LEFT) {
    for (auto& block : blocks) {
      if (block.area.x < border.x) {
        return true;
      } 
    }
  } else if (direction == Tetro::Orientation::RIGHT) {
    for (auto& block : blocks) {
      if (block.area.x + cell_size >= border.x + border.width) {
        return true;
      }
    }
  }
  return false;
}
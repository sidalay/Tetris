#include "enforcer.hpp"

#include "window.hpp"

bool Enforcer::CheckOutOfBounds(const Tetromino& t, const Playfield& p, const Tetro::Orientation direction)
{
  float cell_size{Window::height * Window::cell_size};
  auto blocks{t.GetBlocks()};
  auto border{p.GetBorder()};

  switch (direction)
  {
    case Tetro::Orientation::LEFT:
      for (auto& block : blocks) {
        if (block.area.x < border.x) {
          return true;
        } 
      }
      break;
    case Tetro::Orientation::RIGHT:
      for (auto& block : blocks) {
        if (block.area.x + cell_size >= border.x + border.width) {
          return true;
        }
      }
      break;
  }

  return false;
}
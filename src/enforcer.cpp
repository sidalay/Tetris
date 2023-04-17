#include "enforcer.hpp"

#include "window.hpp"

bool Enforcer::IsBelowClear(const Tetromino& t, const Playfield& p)
{
  float cell_size{Window::height * Window::cell_size_percentage};
  auto blocks{t.GetBlocks()};
  auto map{p.GetMatrixMap()};

  for (auto& block : blocks) {
    std::pair key{block.area.x, block.area.y + cell_size};
    bool occupied{map.at(key)};
    if (occupied) {
      return false;
    }
  }
  return true;
}

bool Enforcer::IsOutOfBounds(const Tetromino& t, const Playfield& p, const Tetro::Orientation direction)
{
  float cell_size{Window::height * Window::cell_size_percentage};
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
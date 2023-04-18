#include "enforcer.hpp"

#include "window.hpp"

bool Enforcer::IsBelowSafe(const Tetromino t, const Playfield& p)
{
  float cell_size{Window::height * Window::cell_size_percentage};
  auto blocks{t.GetBlocks()};
  auto map{p.GetMatrixMap()};

  for (auto& block : blocks) {
    std::pair key{static_cast<int>(block.area.x), static_cast<int>(block.area.y + cell_size)};
    bool occupied{map.at(key)};
    if (occupied) {
      return false;
    }
  }
  return true;
}

bool Enforcer::IsSideSafe(const Tetromino t, const Playfield& p, const Tetro::Orientation direction)
{
  float cell_size{Window::height * Window::cell_size_percentage};
  auto blocks{t.GetBlocks()};
  auto map{p.GetMatrixMap()};

  if (direction == Tetro::Orientation::LEFT) {
    for (auto& block : blocks) {
      std::pair key{static_cast<int>(block.area.x - cell_size), static_cast<int>(block.area.y)};
      bool occupied{map.at(key)};
      if (occupied) {
        return false;
      }
    }
  } else if (direction == Tetro::Orientation::RIGHT) {
    for (auto& block : blocks) {
      std::pair key{static_cast<int>(block.area.x + cell_size), static_cast<int>(block.area.y)};
      bool occupied{map.at(key)};
      if (occupied) {
        return false;
      }
    }
  }

  return true;
}
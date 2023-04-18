#include "enforcer.hpp"

#include "window.hpp"

bool Enforcer::IsBelowSafe(const Tetromino t, const Playfield& p)
{
  const float cell_size{Window::height * Window::cell_size_percentage};
  const auto blocks{t.GetBlocks()};
  const auto map{p.GetMatrixMap()};

  for (auto& block : blocks) {
    std::pair key{block.screen_row + 1, block.screen_col + 1};
    bool occupied{map.at(key)};
    if (occupied) {
      return false;
    }
  }
  return true;
}

bool Enforcer::IsSideSafe(const Tetromino t, const Playfield& p, const Tetro::Orientation direction)
{
  const float cell_size{Window::height * Window::cell_size_percentage};
  const auto blocks{t.GetBlocks()};
  const auto map{p.GetMatrixMap()};

  if (direction == Tetro::Orientation::LEFT) {
    for (auto& block : blocks) {
      std::pair key{block.screen_row, block.screen_col};
      bool occupied{map.at(key)};
      if (occupied) {
        return false;
      }
    }
  } else if (direction == Tetro::Orientation::RIGHT) {
    for (auto& block : blocks) {
      std::pair key{block.screen_row, block.screen_col + 2};
      bool occupied{map.at(key)};
      if (occupied) {
        return false;
      }
    }
  }

  return true;
}
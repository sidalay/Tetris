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

bool Enforcer::IsSideSafe(
  const Tetromino t, 
  const Playfield& p, 
  const Tetro::Orientation direction)
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

Tetro::Wallkick Enforcer::WallKick(
  const Tetromino t, 
  const Playfield& p, 
  const Tetro::Orientation current,
  const Tetro::Orientation rotation)
{
  const float cell_size{Window::height * Window::cell_size_percentage};
  const auto blocks{t.GetBlocks()};
  const auto map{p.GetMatrixMap()};

  switch (current) 
  {
    case Tetro::Orientation::UP:
      if (rotation == Tetro::Orientation::RIGHT) {        // 0>>1

      } else if (rotation == Tetro::Orientation::LEFT) {  // 0>>3  

      }
      break;
    case Tetro::Orientation::RIGHT:
      if (rotation == Tetro::Orientation::RIGHT) {        // 1>>

      } else if (rotation == Tetro::Orientation::LEFT) {
        
      }
      break;
    case Tetro::Orientation::DOWN:
      if (rotation == Tetro::Orientation::RIGHT) {

      } else if (rotation == Tetro::Orientation::LEFT) {
        
      }
      break;
    case Tetro::Orientation::LEFT:
      if (rotation == Tetro::Orientation::RIGHT) {

      } else if (rotation == Tetro::Orientation::LEFT) {
        
      }
      break;
  }
}
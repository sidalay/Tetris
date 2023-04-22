#include "enforcer.hpp"

#include "window.hpp"

bool Enforcer::IsSafe(
  const Tetromino t,
  const Playfield& p)
{
  const float cell_size{Window::height * Window::cell_size_percentage};
  const auto blocks{t.GetBlocks()};
  const auto map{p.GetMatrixMap()};

  for (auto& block : blocks) {
    std::array<bool,3> occupied{
      map.at(std::make_pair(block.screen_row, block.screen_col - 1)), // movement left
      map.at(std::make_pair(block.screen_row, block.screen_col + 1)), // movement right
      map.at(std::make_pair(block.screen_row + 1, block.screen_col))  // movement down
    };
    for (bool filled : occupied) {
      if (filled) {
        return false;
      }
    }
  }
  return true;
}

bool Enforcer::IsSafe(
  const Tetromino t, 
  const Playfield& p, 
  const Tetro::Movement direction)
{
  const float cell_size{Window::height * Window::cell_size_percentage};
  const auto blocks{t.GetBlocks()};
  const auto map{p.GetMatrixMap()};

  if (direction == Tetro::Movement::LEFT) {
    for (auto& block : blocks) {
      std::pair key{block.screen_row, block.screen_col - 1};
      bool occupied{map.at(key)};
      if (occupied) {
        return false;
      }
    }
  } else if (direction == Tetro::Movement::RIGHT) {
    for (auto& block : blocks) {
      std::pair key{block.screen_row, block.screen_col + 1};
      bool occupied{map.at(key)};
      if (occupied) {
        return false;
      }
    }
  } else {
    for (auto& block : blocks) {
      std::pair key{block.screen_row + 1, block.screen_col};
      bool occupied{map.at(key)};
      if (occupied) {
        return false;
      }
    }
  }
  return true;
}

bool Enforcer::IsSafe(
    const Tetromino t, 
    const Playfield& p, 
    const Tetro::Wallkick kick)
{
  const float cell_size{Window::height * Window::cell_size_percentage};
  const auto blocks{t.GetBlocks()};
  const auto map{p.GetMatrixMap()};

  for (auto& block : blocks) {
    std::pair key{block.screen_row + kick.x, block.screen_col + kick.y};
    bool occupied{map.at(key)};
    if (occupied) {
      return false;
    }
  }
  return true;
}

Tetro::Wallkick Enforcer::WallKickEval(
  Tetromino t, 
  const Playfield& p, 
  const Tetro::Orientation current,
  const Tetro::Orientation rotation)
{
  const float cell_size{Window::height * Window::cell_size_percentage};

  if (t.GetType() == Tetro::Shape::I) {
    switch (current)
    {
      case Tetro::Orientation::UP:
        if (rotation == Tetro::Orientation::RIGHT) {        // 0>>1

        } else if (rotation == Tetro::Orientation::LEFT) {  // 0>>3

        }
        break;
      case Tetro::Orientation::RIGHT:
        if (rotation == Tetro::Orientation::RIGHT) {        // 0>>1

        } else if (rotation == Tetro::Orientation::LEFT) {  // 0>>3

        }
        break;
      case Tetro::Orientation::DOWN:
        if (rotation == Tetro::Orientation::RIGHT) {        // 0>>1

        } else if (rotation == Tetro::Orientation::LEFT) {  // 0>>3

        }
        break;
      case Tetro::Orientation::LEFT:
        if (rotation == Tetro::Orientation::RIGHT) {        // 0>>1

        } else if (rotation == Tetro::Orientation::LEFT) {  // 0>>3

        }
        break;
    }
  } else {
    switch (current) 
    {
      case Tetro::Orientation::UP:
        if (rotation == Tetro::Orientation::RIGHT) {        // 0>>1
          t.RotateCW();
          return WallKickTest(t, p, {-1,0}, {-1,1}, {0,-2}, {-1,-2});
        } else if (rotation == Tetro::Orientation::LEFT) {  // 0>>3
          t.RotateCCW();
          return WallKickTest(t, p, {1,0}, {1,1}, {0,-2}, {1,-2});
        }
      case Tetro::Orientation::RIGHT:
        if (rotation == Tetro::Orientation::RIGHT) {        // 1>>2
          t.RotateCW();
        } else if (rotation == Tetro::Orientation::LEFT) {  // 1>>0
          t.RotateCCW();
        }
        return WallKickTest(t, p, {1,0}, {1,-1}, {0,2}, {1,2});
      case Tetro::Orientation::DOWN:
        if (rotation == Tetro::Orientation::RIGHT) {        // 2>>3
          t.RotateCW();
          return WallKickTest(t, p, {1,0}, {1,1}, {0,-2}, {1,-2});
        } else if (rotation == Tetro::Orientation::LEFT) {  // 2>>1
          t.RotateCCW();
          return WallKickTest(t, p, {-1,0}, {-1,1}, {0,-2}, {-1,-2});
        }
      case Tetro::Orientation::LEFT:
        if (rotation == Tetro::Orientation::RIGHT) {        // 3>>0
          t.RotateCW();
        } else if (rotation == Tetro::Orientation::LEFT) {  // 3>>2
          t.RotateCCW();
        }
        return WallKickTest(t, p, {-1,0}, {-1,-1}, {0,2}, {-1,2});
    }
  }

  return Tetro::Wallkick{};
}

Tetro::Wallkick Enforcer::WallKickTest(
  Tetromino& t,
  const Playfield& p,
  const Tetro::Wallkick test1,
  const Tetro::Wallkick test2,
  const Tetro::Wallkick test3,
  const Tetro::Wallkick test4)
{

}
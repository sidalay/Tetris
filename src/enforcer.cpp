#include "enforcer.hpp"

#include "window.hpp"

bool Enforcer::MovementIsSafe(
  const Tetromino t, 
  const Map& map, 
  const Tetro::Movement direction)
{
  const auto blocks{t.GetBlocks()};

  // account for offset of invisble columns when we create keys
  if (direction == Tetro::Movement::LEFT) {
    for (const auto block : blocks) {
      std::pair key{block.screen_row, block.screen_col};
      bool occupied{map.at(key)};
      if (occupied) {
        return false;
      }
    }
  } else if (direction == Tetro::Movement::RIGHT) {
    for (const auto& block : blocks) {
      std::pair key{block.screen_row, block.screen_col + 2};
      bool occupied{map.at(key)};
      if (occupied) {
        return false;
      }
    }
  } else {
    for (const auto& block : blocks) {
      std::pair key{block.screen_row + 1, block.screen_col + 1};
      bool occupied{map.at(key)};
      if (occupied) {
        return false;
      }
    }
  }
  return true;
}

bool Enforcer::RotationIsSafe(
  Tetromino t,
  const Map& map,
  const Tetro::Rotation rotation)
{
  t.RotateWallKick(rotation);
  for (const auto block : t.GetBlocks()) {
    std::pair key{block.screen_row, block.screen_col + 1};
    bool occupied{map.at(key)};
    if (occupied) {
      return false;
    }
  }
  return true;
}

bool Enforcer::WallkickIsSafe(
    const Tetromino t, 
    const Map& map, 
    const Tetro::Wallkick kick)
{
  const auto blocks{t.GetBlocks()};

  for (const auto block : blocks) {
    std::pair key{block.screen_row - kick.row, (block.screen_col + 1) + kick.col};
    if (key.second < 0) {
      key.first = 0;
    } else if (key.second > 10) {
      key.first = 10;
    }
    bool occupied{map.at(key)};
    if (occupied) {
      return false;
    }
  }
  return true;
}

Tetro::Wallkick Enforcer::WallKickEval(
  Tetromino t, 
  const Map& map, 
  const Tetro::Rotation rotation)
{
  if (t.GetType() == Tetro::Shape::I) {
    switch (t.GetOrientation())
    {
      case Tetro::Orientation::UP:
        t.RotateWallKick(rotation);
        if (rotation == Tetro::Rotation::CW) {        // 0>>1
          return WallKickTest(t, map, {-2,0, 1,0, -2,-1, 1,2});
        } else if (rotation == Tetro::Rotation::CCW) {  // 0>>3
          return WallKickTest(t, map, {-1,0, 2,0, -1,2, 2,-1});
        }
      case Tetro::Orientation::RIGHT:
        t.RotateWallKick(rotation);
        if (rotation == Tetro::Rotation::CW) {        // 1>>2
          return WallKickTest(t, map, {-1,0, 2,0, -1,2, 2,-1});
        } else if (rotation == Tetro::Rotation::CCW) {  // 1>>0
          return WallKickTest(t, map, {2,0, -1,0, 2,1, -1,-2});
        }
      case Tetro::Orientation::DOWN:
        t.RotateWallKick(rotation);
        if (rotation == Tetro::Rotation::CW) {        // 2>>3
          return WallKickTest(t, map, {2,0, -1,0, 2,1, -1,-2});
        } else if (rotation == Tetro::Rotation::CCW) {  // 2>>1
          return WallKickTest(t, map, {1,0, -2,0, 1,-2, -2,1});
        }
      case Tetro::Orientation::LEFT:
        t.RotateWallKick(rotation);
        if (rotation == Tetro::Rotation::CW) {        // 3>>0
          return WallKickTest(t, map, {1,0, -2,0, 1,-2, -2,1});
        } else if (rotation == Tetro::Rotation::CCW) {  // 3>>2
          return WallKickTest(t, map, {-2,0, 1,0, -2,-1, 1,2});
        }
    }
  } else {
    switch (t.GetOrientation()) 
    {
      case Tetro::Orientation::UP:
        t.RotateWallKick(rotation);
        if (rotation == Tetro::Rotation::CW) {        // 0>>1
          return WallKickTest(t, map, {-1,0, -1,1, 0,-2, -1,-2});
        } else if (rotation == Tetro::Rotation::CCW) {  // 0>>3
          return WallKickTest(t, map, {1,0, 1,1, 0,-2, 1,-2});
        }
      case Tetro::Orientation::RIGHT:
        t.RotateWallKick(rotation);
        if (rotation == Tetro::Rotation::CW) {        // 1>>2
          return WallKickTest(t, map, {1,0, 1,-1, 0,2, 1,2});
        } else if (rotation == Tetro::Rotation::CCW) {  // 1>>0
          return WallKickTest(t, map, {1,0, 1,-1, 0,2, 1,2});
        }
      case Tetro::Orientation::DOWN:
        t.RotateWallKick(rotation);
        if (rotation == Tetro::Rotation::CW) {        // 2>>3
          return WallKickTest(t, map, {1,0, 1,1, 0,-2, 1,-2});
        } else if (rotation == Tetro::Rotation::CCW) {  // 2>>1
          return WallKickTest(t, map, {-1,0, -1,1, 0,-2, -1,-2});
        }
      case Tetro::Orientation::LEFT:
        t.RotateWallKick(rotation);
        if (rotation == Tetro::Rotation::CW) {        // 3>>0
          return WallKickTest(t, map, {-1,0, -1,-1, 0,2, -1,2});
        } else if (rotation == Tetro::Rotation::CCW) {  // 3>>2
          return WallKickTest(t, map, {-1,0, -1,-1, 0,2, -1,2});
        }
    }
  }
  return Tetro::Wallkick{0,0};
}

Tetro::Wallkick Enforcer::WallKickTest(
  Tetromino t,
  const Map& map,
  const std::array<Tetro::Wallkick,4>&& tests)
{
  for (const auto& kick : tests) {
    if (WallkickIsSafe(t, map, kick)) {
      return kick;
    }
  }
  return Tetro::Wallkick{0,0};
}

bool Enforcer::IsSpawnSafe(
  Tetromino t,
  const Map& map)
{
  const auto blocks{t.GetBlocks()};

  for (const auto block : blocks) {
    std::pair key{block.screen_row, block.screen_col + 1};
    bool occupied{map.at(key)};
    if (occupied) {
      return false;
    }
  }
  return true;
}

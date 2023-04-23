#include "tetromino.hpp"

#include "window.hpp"

const Color Cyan{0, 255, 255, 255};   // I
const Color Blue{0, 0, 255, 255};     // J
const Color Orange{255, 165, 0, 255}; // L
const Color Yellow{255, 255, 0, 255}; // O
const Color Green{0, 255, 0, 255};    // S
const Color Purple{128, 0, 128, 255}; // T
const Color Red{255, 0, 0, 255};      // Z
const Color Cleared{0, 0, 0, 0};      // Line Cleared

Tetromino::Tetromino(Tetro::Shape shape)
  : type{shape}
{
  InitBlocks();
}

void Tetromino::Tick()
{
  if (IsWindowResized()) {
    UpdateBlockSize();
    UpdateOriginScale();
  }
  UpdateRowCol();
  UpdateFollowerPos();
}

void Tetromino::Draw()
{
  for (auto& block : blocks) {
    DrawRectangleRec(block.area, block.color);
    DrawRectangleLinesEx(block.area, 2.f, BLACK);
  }
}

void Tetromino::Move(Tetro::Movement direction)
{
  float cell_size{Window::height * Window::cell_size_percentage};
  switch (direction)
  {
    case Tetro::Movement::DOWN:
      blocks[0].area.y += cell_size;
      break;
    case Tetro::Movement::LEFT:
      blocks[0].area.x -= cell_size;
      break;
    case Tetro::Movement::RIGHT:
      blocks[0].area.x += cell_size;
      break;
    default:
      break;
  }
}

void Tetromino::Move(Tetro::Wallkick kick) 
{
  float cell_size{Window::height * Window::cell_size_percentage};
  blocks[0].area.x += cell_size * kick.col;
  blocks[0].area.y -= cell_size * kick.row;
}

void Tetromino::RotateCW()
{
  switch (facing)
  {
    case Tetro::Orientation::UP:
      facing = Tetro::Orientation::RIGHT;
      break;
    case Tetro::Orientation::DOWN:
      facing = Tetro::Orientation::LEFT;
      break;
    case Tetro::Orientation::LEFT:
      facing = Tetro::Orientation::UP;
      break;
    case Tetro::Orientation::RIGHT:
      facing = Tetro::Orientation::DOWN;
      break;
  }
}

void Tetromino::RotateCCW()
{
  switch (facing)
  {
    case Tetro::Orientation::UP:
      facing = Tetro::Orientation::LEFT;
      break;
    case Tetro::Orientation::DOWN:
      facing = Tetro::Orientation::RIGHT;
      break;
    case Tetro::Orientation::LEFT:
      facing = Tetro::Orientation::DOWN;
      break;
    case Tetro::Orientation::RIGHT:
      facing = Tetro::Orientation::UP;
      break;
  }
}

void Tetromino::WallKickCW(const Tetro::Wallkick kick)
{
  if (kick.col == 0 && kick.row == 0) {
    return;
  }
  RotateCW();
  Move(kick);
}

void Tetromino::WallKickCCW(const Tetro::Wallkick kick)
{
  if (kick.col == 0 && kick.row == 0) {
    return;
  }
  RotateCCW();
  Move(kick);
}

void Tetromino::RotateWallKick(const Tetro::Rotation r)
{
  if (r == Tetro::Rotation::CW) {
    switch (facing)
    {
      case Tetro::Orientation::UP:
        facing = Tetro::Orientation::RIGHT;
        break;
      case Tetro::Orientation::DOWN:
        facing = Tetro::Orientation::LEFT;
        break;
      case Tetro::Orientation::LEFT:
        facing = Tetro::Orientation::UP;
        break;
      case Tetro::Orientation::RIGHT:
        facing = Tetro::Orientation::DOWN;
        break;
    }
  } else {
    switch (facing)
    {
      case Tetro::Orientation::UP:
        facing = Tetro::Orientation::LEFT;
        break;
      case Tetro::Orientation::DOWN:
        facing = Tetro::Orientation::RIGHT;
        break;
      case Tetro::Orientation::LEFT:
        facing = Tetro::Orientation::DOWN;
        break;
      case Tetro::Orientation::RIGHT:
        facing = Tetro::Orientation::UP;
        break;
    }
  }
  UpdateFollowerPos();
  UpdateRowCol();
}

void Tetromino::Fall()
{
  for (auto& block : blocks) {
    block.area.y += block.area.height;
  }
}

void Tetromino::InitBlocks()
{
  InitBlockSize();
  InitBlockColor();
  InitBlockOrigin();
  SetFollowers();
}

void Tetromino::InitBlockSize()
{
  float cell_size{Window::height * Window::cell_size_percentage};
  for (auto& block : blocks) {
    block.area.width = cell_size;
    block.area.height = cell_size;
  }
}

void Tetromino::InitBlockOrigin()
{
  Tetro::Block& origin{blocks.at(0)};
  float cell_size{Window::height * Window::cell_size_percentage};

  origin.area.x = Window::width/2 - cell_size; 
  origin.area.y = cell_size * 2.f;
  UpdateRowCol();
}

void Tetromino::SetShape(
  std::pair<int,int> one, 
  std::pair<int,int> two, 
  std::pair<int,int> three)
{
  for (int i{1}; i < blocks.size(); ++i) {
    if (i == 1) {
      blocks[i].area.x = blocks[0].area.x + (blocks[i].area.width * one.first);
      blocks[i].area.y = blocks[0].area.y + (blocks[i].area.height * one.second);
    } else if (i == 2) {
      blocks[i].area.x = blocks[0].area.x + (blocks[i].area.width * two.first);
      blocks[i].area.y = blocks[0].area.y + (blocks[i].area.height * two.second);
    } else {
      blocks[i].area.x = blocks[0].area.x + (blocks[i].area.width * three.first);
      blocks[i].area.y = blocks[0].area.y + (blocks[i].area.height * three.second);
    }
  }
}

void Tetromino::SetFollowers()
{
  switch (type)
  {
    case Tetro::Shape::I:
      SetShape(std::make_pair(-1,0), std::make_pair(1,0), std::make_pair(2,0));
      break;
    case Tetro::Shape::J:
      SetShape(std::make_pair(1,0), std::make_pair(-1,0), std::make_pair(-1,-1));
      break;
    case Tetro::Shape::L:
      SetShape(std::make_pair(-1,0), std::make_pair(1,0), std::make_pair(1,-1));
      break;
    case Tetro::Shape::O:
      SetShape(std::make_pair(0,-1), std::make_pair(1,-1), std::make_pair(1,0));
      break;
    case Tetro::Shape::S:
      SetShape(std::make_pair(-1,0), std::make_pair(0,-1), std::make_pair(1,-1));
      break;
    case Tetro::Shape::T:
      SetShape(std::make_pair(-1,0), std::make_pair(0,-1), std::make_pair(1,0));
      break;
    case Tetro::Shape::Z:
      SetShape(std::make_pair(1,0), std::make_pair(0,-1), std::make_pair(-1,-1));
      break;
  }
}

void Tetromino::InitBlockColor()
{
  switch (type)
  {
    case Tetro::Shape::I:
      color = Cyan;
      break;
    case Tetro::Shape::J:
      color = Blue;
      break;
    case Tetro::Shape::L:
      color = Orange;
      break;
    case Tetro::Shape::O:
      color = Yellow;
      break;
    case Tetro::Shape::S:
      color = Green;
      break;
    case Tetro::Shape::T:
      color = Purple;
      break;
    case Tetro::Shape::Z:
      color = Red;
      break;
  }

  for (auto& block : blocks) {
    block.color = this->color;
  }
}

void Tetromino::UpdateOriginCW()
{
  if (type != Tetro::Shape::I) {
    return;
  }

  float cell_size{Window::height * Window::cell_size_percentage};
  switch (facing)
  {
    case Tetro::Orientation::UP:
      blocks[0].area.y -= cell_size;
      break;
    case Tetro::Orientation::RIGHT:
      blocks[0].area.x += cell_size;
      break;
    case Tetro::Orientation::DOWN:
      blocks[0].area.y += cell_size;
      break;
    case Tetro::Orientation::LEFT:
      blocks[0].area.x -= cell_size;
      break;
  }
}

void Tetromino::UpdateOriginCCW()
{
  if (type != Tetro::Shape::I) {
    return;
  }

  float cell_size{Window::height * Window::cell_size_percentage};
  switch (facing)
  {
    case Tetro::Orientation::UP:
      blocks[0].area.x -= cell_size;
      break;
    case Tetro::Orientation::RIGHT:
      blocks[0].area.y -= cell_size;
      break;
    case Tetro::Orientation::DOWN:
      blocks[0].area.x += cell_size;
      break;
    case Tetro::Orientation::LEFT:
      blocks[0].area.y += cell_size;
      break;
  }
}

void Tetromino::UpdateBlockSize()
{
  InitBlockSize();
}

void Tetromino::UpdateOriginScale()
{
  Tetro::Block& origin{blocks.at(0)};
  float cell_size{Window::height * Window::cell_size_percentage};
  float borderX{(Window::width - (Window::well_width * Window::height)) * .5f};

  origin.area.y = cell_size * origin.screen_row;
  origin.area.x = borderX + (cell_size * origin.screen_col); 
}

void Tetromino::UpdateRowCol()
{
  float cell_size{Window::height * Window::cell_size_percentage};
  float borderX{(Window::width - (Window::well_width * Window::height)) * .5f};

  for (auto& block : blocks) {
    block.screen_row = block.area.y / static_cast<int>(cell_size);
    block.screen_col = (static_cast<int>(block.area.x - borderX) / static_cast<int>(cell_size)) + 1;
  }

}

void Tetromino::UpdateFollowerPos()
{
  switch (facing)
  {
    case Tetro::Orientation::UP: {
      SetFollowers();
      break;
    }
    case Tetro::Orientation::RIGHT: {
      switch (type)
      {
        case Tetro::Shape::I:
          SetShape(std::make_pair(0,-1), std::make_pair(0,1), std::make_pair(0,2));
          break;
        case Tetro::Shape::J:
          SetShape(std::make_pair(0,1), std::make_pair(0,-1), std::make_pair(1,-1));
          break;
        case Tetro::Shape::L:
          SetShape(std::make_pair(0,-1), std::make_pair(0,1), std::make_pair(1,1));
          break;
        case Tetro::Shape::O:
          SetShape(std::make_pair(0,-1), std::make_pair(1,-1), std::make_pair(1,0));
          break;
        case Tetro::Shape::S:
          SetShape(std::make_pair(0,-1), std::make_pair(1,0), std::make_pair(1,1));
          break;
        case Tetro::Shape::T:
          SetShape(std::make_pair(0,-1), std::make_pair(1,0), std::make_pair(0,1));
          break;
        case Tetro::Shape::Z:
          SetShape(std::make_pair(0,1), std::make_pair(1,0), std::make_pair(1,-1));
          break;
      }
      break;
    }
    case Tetro::Orientation::DOWN: {
      switch (type)
      {
        case Tetro::Shape::I:
          SetShape(std::make_pair(1,0), std::make_pair(-1,0), std::make_pair(-2,0));
          break;
        case Tetro::Shape::J:
          SetShape(std::make_pair(-1,0), std::make_pair(1,0), std::make_pair(1,1));
          break;
        case Tetro::Shape::L:
          SetShape(std::make_pair(1,0), std::make_pair(-1,0), std::make_pair(-1,1));
          break;
        case Tetro::Shape::O:
          SetShape(std::make_pair(0,-1), std::make_pair(1,-1), std::make_pair(1,0));
          break;
        case Tetro::Shape::S:
          SetShape(std::make_pair(1,0), std::make_pair(0,1), std::make_pair(-1,1));
          break;
        case Tetro::Shape::T:
          SetShape(std::make_pair(1,0), std::make_pair(0,1), std::make_pair(-1,0));
          break;
        case Tetro::Shape::Z:
          SetShape(std::make_pair(-1,0), std::make_pair(0,1), std::make_pair(1,1));
          break;
      }
      break;
    }
    case Tetro::Orientation::LEFT: {
      switch (type)
      {
        case Tetro::Shape::I:
          SetShape(std::make_pair(0,1), std::make_pair(0,-1), std::make_pair(0,-2));
          break;
        case Tetro::Shape::J:
          SetShape(std::make_pair(0,-1), std::make_pair(0,1), std::make_pair(-1,1));
          break;
        case Tetro::Shape::L:
          SetShape(std::make_pair(0,1), std::make_pair(0,-1), std::make_pair(-1,-1));
          break;
        case Tetro::Shape::O:
          SetShape(std::make_pair(0,-1), std::make_pair(1,-1), std::make_pair(1,0));
          break;
        case Tetro::Shape::S:
          SetShape(std::make_pair(0,1), std::make_pair(-1,0), std::make_pair(-1,-1));
          break;
        case Tetro::Shape::T:
          SetShape(std::make_pair(0,1), std::make_pair(-1,0), std::make_pair(0,-1));
          break;
        case Tetro::Shape::Z:
          SetShape(std::make_pair(0,-1), std::make_pair(-1,0), std::make_pair(-1,1));
          break;
      }
      break;
    }
  }
}

/*
/   [1][0][2][3]
/
/   [3]
/   [2][0][1]
/
/         [3]
/   [1][0][2]
/
/   [1][2]
/   [0][3]
/
/      [2][3]
/   [1][0]
/
/      [2]
/   [1][0][3]
/
/   [3][2]
/      [0][1]
/
*/
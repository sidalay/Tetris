#include "tetromino.hpp"

const Color Cyan{0, 255, 255, 255};   // I
const Color Blue{0, 0, 255, 255};     // J
const Color Orange{255, 165, 0, 255}; // L
const Color Yellow{255, 255, 0, 255}; // O
const Color Green{0, 255, 0, 255};    // S
const Color Purple{128, 0, 128, 255}; // T
const Color Red{255, 0, 0, 255};      // Z

const float cell_size{1.f/26.f};      // 100% / 22 cells 

Tetromino::Tetromino(Tetro::Shape shape)
  : type{shape}
{
  InitBlocks();
}

void Tetromino::Tick()
{
  deltatime += GetFrameTime();
  if (deltatime >= updatetime) {
    Fall();
    deltatime = 0.f;
  }
  UpdateBlockPos();
}

void Tetromino::Draw()
{
  for (auto& block : blocks) {
    DrawRectangleRec(block.area, color);
    DrawRectangleLinesEx(block.area, 2.f, BLACK);
  }
}

void Tetromino::Move(Tetro::Orientation direction)
{
  switch (direction)
  {
    case Tetro::Orientation::DOWN:
      blocks[0].area.y += blocks[0].area.height;
      break;
    case Tetro::Orientation::LEFT:
      blocks[0].area.x -= blocks[0].area.width;
      break;
    case Tetro::Orientation::RIGHT:
      blocks[0].area.x += blocks[0].area.width;
      break;
    default:
      break;
  }
}

void Tetromino::Rotate()
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

  UpdateOrigin();
}

void Tetromino::Fall()
{
  for (auto& block : blocks) {
    block.area.y += block.area.height;
  }
}

void Tetromino::InitBlocks()
{
  SetSize();
  SetColor();
  SetOrigin();
  SetFollowers();
}

void Tetromino::SetSize()
{
  for (auto& block : blocks) {
    block.area.width = Window::height * cell_size;
    block.area.height = Window::height * cell_size;
  }
}

void Tetromino::SetOrigin()
{
  blocks[0].area.x = Window::width/2 - blocks[0].area.width; 
  blocks[0].area.y = blocks[0].area.height;
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

void Tetromino::SetColor()
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
}

void Tetromino::UpdateOrigin()
{
  if (type != Tetro::Shape::I) {
    return;
  }

  switch (facing)
  {
    case Tetro::Orientation::UP:
      blocks[0].area.y -= Window::height * cell_size;
      break;
    case Tetro::Orientation::RIGHT:
      blocks[0].area.x += Window::height * cell_size;
      break;
    case Tetro::Orientation::DOWN:
      blocks[0].area.y += Window::height * cell_size;
      break;
    case Tetro::Orientation::LEFT:
      blocks[0].area.x -= Window::height * cell_size;
      break;
  }
}

void Tetromino::UpdateBlockPos()
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
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
  Drop();
}

void Tetromino::Draw()
{
  for (auto& block : blocks) {
    DrawRectangleRec(block.area, color);
    DrawRectangleLinesEx(block.area, 2.f, BLACK);
  }
}

void Tetromino::Rotate()
{

}

void Tetromino::Drop()
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
  if (type == Tetro::Shape::O) {
    blocks[0].area.x = Window::width/2 - (blocks[0].area.width * 1.f); 
  } else {
    blocks[0].area.x = Window::width/2 - (blocks[0].area.width * 2.f); 
  }
  blocks[0].area.y = blocks[0].area.height * 2.f;

  if (type == Tetro::Shape::Z) {
    blocks[0].area.y = blocks[0].area.height * 1.f;
  }
}

void Tetromino::SetShape(
  std::pair<int,int> one, 
  std::pair<int,int> two, 
  std::pair<int,int> three)
{
  for (int i{1}; i < blocks.size(); ++i) {
    if (i == 1) {
      blocks[i].area.x = blocks[0].area.x + (blocks[i].area.width * one.second);
      blocks[i].area.y = blocks[0].area.y - (blocks[i].area.height * one.first);
    } else if (i == 2) {
      blocks[i].area.x = blocks[0].area.x + (blocks[i].area.width * two.second);
      blocks[i].area.y = blocks[0].area.y - (blocks[i].area.height * two.first);
    } else {
      blocks[i].area.x = blocks[0].area.x + (blocks[i].area.width * three.second);
      blocks[i].area.y = blocks[0].area.y - (blocks[i].area.height * three.first);
    }
  }
}

void Tetromino::SetFollowers()
{
  switch (type)
  {
    case Tetro::Shape::I:
      SetShape(std::make_pair(0,1), std::make_pair(0,2), std::make_pair(0,3));
      break;
    case Tetro::Shape::J:
      SetShape(std::make_pair(1,0), std::make_pair(0,1), std::make_pair(0,2));
      break;
    case Tetro::Shape::L:
      SetShape(std::make_pair(0,1), std::make_pair(0,2), std::make_pair(1,2));
      break;
    case Tetro::Shape::O:
      SetShape(std::make_pair(1,0), std::make_pair(1,1), std::make_pair(0,1));
      break;
    case Tetro::Shape::S:
      SetShape(std::make_pair(0,1), std::make_pair(1,1), std::make_pair(1,2));
      break;
    case Tetro::Shape::T:
      SetShape(std::make_pair(0,1), std::make_pair(1,1), std::make_pair(0,2));
      break;
    case Tetro::Shape::Z:
      SetShape(std::make_pair(0,1), std::make_pair(-1,1), std::make_pair(-1,2));
      break;
  }
}

void Tetromino::UpdateFollowers()
{

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

void Tetromino::UpdateBlockPos()
{
  switch (facing)
  {
    case Tetro::Orientation::UP:
      break;
    case Tetro::Orientation::DOWN:
      break;
    case Tetro::Orientation::LEFT:
      break;
    case Tetro::Orientation::RIGHT:
      break;
  }
}
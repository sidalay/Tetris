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
  SetSpawn();
  SetColor();
}

void Tetromino::SetSize()
{
  for (auto& block : blocks) {
    block.area.width = Window::height * cell_size;
    block.area.height = Window::height * cell_size;
  }
}

void Tetromino::SetSpawn()
{
  if (type == Tetro::Shape::O) {
    blocks[0].area.x = Window::width/2 - (blocks[0].area.width * 1.f); 
  } else {
    blocks[0].area.x = Window::width/2 - (blocks[0].area.width * 2.f); 
  }
  blocks[0].area.y = blocks[0].area.height * 2.f;
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
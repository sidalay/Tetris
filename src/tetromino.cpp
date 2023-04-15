#include "tetromino.hpp"

const Color Cyan{0, 255, 255, 255};   // I
const Color Blue{0, 0, 255, 255};     // J
const Color Orange{255, 165, 0, 255}; // L
const Color Yellow{255, 255, 0, 255}; // O
const Color Green{0, 255, 0, 255};    // S
const Color Purple{128, 0, 128, 255}; // T
const Color Red{255, 0, 0, 255};      // Z

Tetromino::Tetromino(Tetro::Shape shape)
{
  switch (shape)
  {
    case Tetro::Shape::I:
      break;
    case Tetro::Shape::J:
      break;
    case Tetro::Shape::L:
      break;
    case Tetro::Shape::O:
      break;
    case Tetro::Shape::S:
      break;
    case Tetro::Shape::T:
      break;
    case Tetro::Shape::Z:
      break;
  }
}

void Tetromino::Rotate()
{

}

#include "controller.hpp"
#include "enforcer.hpp"

Controller::Controller(Playfield& playfield)
  : matrix{playfield}
{

}

void Controller::Tick()
{
  CheckInput();
}

void Controller::Spin(Tetro::Rotation rotation)
{
  Tetromino& tetro{matrix.GetCurrentTetro()};
  if (Enforcer::RotationIsSafe(tetro, matrix, rotation)) {
    tetro.Rotate(rotation);
  } else {
    tetro.WallKick(Enforcer::WallKickEval(tetro, matrix, rotation), rotation);
  }
}

void Controller::SoftDrop()
{
  Tetromino& tetro{matrix.GetCurrentTetro()};
  if (Enforcer::MovementIsSafe(tetro, matrix, Tetro::Movement::DOWN)) {
    tetro.Move(Tetro::Movement::DOWN);
  }
}

void Controller::HardDrop()
{

}

void Controller::SideStep(Tetro::Movement movement)
{
  Tetromino& tetro{matrix.GetCurrentTetro()};
  if (Enforcer::MovementIsSafe(tetro, matrix, movement)) {
    tetro.Move(movement);
  }
}

void Controller::CheckInput()
{
  if (IsKeyPressed(KEY_DOWN)) {
    SoftDrop();
  } else if (IsKeyPressed(KEY_UP)) {
    HardDrop();
  } else if (IsKeyPressed(KEY_LEFT)) {
    SideStep(Tetro::Movement::LEFT);
  } else if (IsKeyPressed(KEY_RIGHT)) {
    SideStep(Tetro::Movement::RIGHT);
  }

  if (IsKeyPressed(KEY_A)) {
    Spin(Tetro::Rotation::CCW);
  } else if (IsKeyPressed(KEY_D)) {
    Spin(Tetro::Rotation::CW);
  }
}
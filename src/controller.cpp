#include "controller.hpp"
#include "enforcer.hpp"

Controller::Controller(Playfield& playfield)
  : matrix{playfield}
{

}

void Controller::Tick()
{
  Tetromino& tetro{matrix.GetCurrentTetro()};
  CheckInput();
}

void Controller::Hold()
{
  
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
    deltatime += GetFrameTime();
    if (deltatime >= 1.f/20.f) {
      tetro.Move(Tetro::Movement::DOWN);
      deltatime = 0.f;
    }
  }
}

void Controller::HardDrop()
{
  Tetromino& tetro{matrix.GetCurrentTetro()};
  while (Enforcer::MovementIsSafe(tetro, matrix, Tetro::Movement::DOWN)) {
    tetro.Move(Tetro::Movement::DOWN);
  }
  matrix.SetLocked(true);
}

void Controller::SideStep(Tetro::Movement movement)
{
  Tetromino& tetro{matrix.GetCurrentTetro()};
  if (Enforcer::MovementIsSafe(tetro, matrix, movement)) {
    deltatime += GetFrameTime();
    if (deltatime >= 1.f/20.f) {
      tetro.Move(movement);
      deltatime = 0.f;
    }
  }
}

void Controller::CheckInput()
{
  if (IsKeyDown(KEY_DOWN)) {
    SoftDrop();
  } else if (IsKeyPressed(KEY_UP)) {
    HardDrop();
  } 
  
  if (IsKeyDown(KEY_LEFT)) {
    SideStep(Tetro::Movement::LEFT);
  } else if (IsKeyDown(KEY_RIGHT)) {
    SideStep(Tetro::Movement::RIGHT);
  } 
  
  if (IsKeyPressed(KEY_LEFT_SHIFT)) {
    Hold();
  }

  if (IsKeyPressed(KEY_A)) {
    Spin(Tetro::Rotation::CCW);
  } else if (IsKeyPressed(KEY_D)) {
    Spin(Tetro::Rotation::CW);
  }
}
#include "controller.hpp"
#include "enforcer.hpp"

#define HARD_DROP   KEY_UP
#define SOFT_DROP   KEY_DOWN
#define STEP_LEFT   KEY_LEFT
#define STEP_RIGHT  KEY_RIGHT
#define ROTATE_CW   KEY_D
#define ROTATE_CCW  KEY_A
#define HOLD        KEY_LEFT_SHIFT
#define PAUSE       KEY_P

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
  matrix.GetHandler().Hold();
}

void Controller::Spin(Tetro::Rotation rotation)
{
  Tetromino& tetro{matrix.GetCurrentTetro()};
  if (Enforcer::RotationIsSafe(tetro, matrix.GetMatrixMap(), rotation)) {
    tetro.Rotate(rotation);
  } else {
    tetro.WallKick(Enforcer::WallKickEval(tetro, matrix.GetMatrixMap(), rotation), rotation);
  }
}

void Controller::SoftDrop()
{
  Tetromino& tetro{matrix.GetCurrentTetro()};
  if (Enforcer::MovementIsSafe(tetro, matrix.GetMatrixMap(), Tetro::Movement::DOWN)) {
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
  while (Enforcer::MovementIsSafe(tetro, matrix.GetMatrixMap(), Tetro::Movement::DOWN)) {
    tetro.Move(Tetro::Movement::DOWN);
  }
  matrix.GetHandler().SetLocked(true);
}

void Controller::SideStep(Tetro::Movement movement)
{
  Tetromino& tetro{matrix.GetCurrentTetro()};
  if (Enforcer::MovementIsSafe(tetro, matrix.GetMatrixMap(), movement)) {
    deltatime += GetFrameTime();
    if (deltatime >= 1.f/15.f) {
      tetro.Move(movement);
      deltatime = 0.f;
    }
  }
}

void Controller::CheckInput()
{
  if (IsKeyDown(SOFT_DROP)) {
    SoftDrop();
  } else if (IsKeyPressed(HARD_DROP)) {
    HardDrop();
  } 
  
  if (IsKeyDown(STEP_LEFT)) {
    SideStep(Tetro::Movement::LEFT);
  } else if (IsKeyDown(STEP_RIGHT)) {
    SideStep(Tetro::Movement::RIGHT);
  } 
  
  if (IsKeyPressed(HOLD)) {
    Hold();
  }

  if (IsKeyPressed(ROTATE_CCW)) {
    Spin(Tetro::Rotation::CCW);
  } else if (IsKeyPressed(ROTATE_CW)) {
    Spin(Tetro::Rotation::CW);
  }

  if (IsKeyUp(STEP_LEFT) && IsKeyUp(STEP_RIGHT) && IsKeyUp(SOFT_DROP)) {
    deltatime = 1.f/20.f;
  }
}
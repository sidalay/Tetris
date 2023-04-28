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
  CheckGamepadInput();
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

void Controller::SoftDrop(float& time)
{
  Tetromino& tetro{matrix.GetCurrentTetro()};
  if (Enforcer::MovementIsSafe(tetro, matrix.GetMatrixMap(), Tetro::Movement::DOWN)) {
    time += GetFrameTime();
    if (time >= 1.f/20.f) {
      tetro.Move(Tetro::Movement::DOWN);
      time = 0.f;
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

void Controller::SideStep(Tetro::Movement movement, float& time)
{
  Tetromino& tetro{matrix.GetCurrentTetro()};
  if (Enforcer::MovementIsSafe(tetro, matrix.GetMatrixMap(), movement)) {
    time += GetFrameTime();
    if (time >= 1.f/15.f) {
      tetro.Move(movement);
      time = 0.f;
    }
  }
}

void Controller::Pause()
{
  matrix.Pause();
}

void Controller::Reset()
{
  matrix.Reset();
}

void Controller::CheckInput()
{
  if (!matrix.IsPaused()) {
    if (IsKeyDown(SOFT_DROP)) {
      SoftDrop(keyboard);
    } else if (IsKeyPressed(HARD_DROP)) {
      HardDrop();
    } 
    
    if (IsKeyDown(STEP_LEFT)) {
      SideStep(Tetro::Movement::LEFT, keyboard);
    } else if (IsKeyDown(STEP_RIGHT)) {
      SideStep(Tetro::Movement::RIGHT, keyboard);
    } 
    
    if (IsKeyPressed(HOLD)) {
      Hold();
    }

    if (IsKeyPressed(ROTATE_CCW)) {
      Spin(Tetro::Rotation::CCW);
    } else if (IsKeyPressed(ROTATE_CW)) {
      Spin(Tetro::Rotation::CW);
    }

    if (IsKeyPressed(RESET)) {
      Reset();
    }
  }

  if (IsKeyPressed(PAUSE)) {
    Pause();
  }

  if (IsKeyUp(STEP_LEFT) && IsKeyUp(STEP_RIGHT) && IsKeyUp(SOFT_DROP)) {
    keyboard = 1.f/20.f;
  }
}

void Controller::CheckGamepadInput()
{
  if (IsGamepadAvailable(0)) {
    if (!matrix.IsPaused()) {
      if (IsGamepadButtonDown(0, GP_SOFT_DROP)) {
        SoftDrop(gamepad);
      } else if (IsGamepadButtonPressed(0, GP_HARD_DROP) || IsGamepadButtonPressed(0, GP_HARD_DROP_ALT)) {
        HardDrop();
      }

      if (IsGamepadButtonDown(0, GP_STEP_LEFT)) {
        SideStep(Tetro::Movement::LEFT, gamepad);
      } else if (IsGamepadButtonDown(0, GP_STEP_RIGHT)) {
        SideStep(Tetro::Movement::RIGHT, gamepad);
      }

      if (IsGamepadButtonPressed(0, GP_HOLD) || IsGamepadButtonPressed(0, GP_HOLD_ALT)) {
        Hold();
      }

      if (IsGamepadButtonPressed(0, GP_ROTATE_CCW) || IsGamepadButtonPressed(0, GP_ROTATE_CCW_ALT)) {
        Spin(Tetro::Rotation::CCW);
      } else if (IsGamepadButtonPressed(0, GP_ROTATE_CW) || IsGamepadButtonPressed(0, GP_ROTATE_CW_ALT)) {
        Spin(Tetro::Rotation::CW);
      }

      if (IsGamepadButtonPressed(0, GP_RESET)) {
        Reset();
      }
    }

    if (IsGamepadButtonPressed(0, GP_PAUSE)) {
      Pause();
    }

    if (IsGamepadButtonUp(0, GP_STEP_LEFT) && IsGamepadButtonUp(0, GP_STEP_RIGHT) && IsGamepadButtonUp(0, GP_SOFT_DROP)) {
      gamepad = 1.f/20.f;
    }
  }
}

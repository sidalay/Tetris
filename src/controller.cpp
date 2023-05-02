#include "controller.hpp"
#include "enforcer.hpp"

Controller::Controller(Playfield& playfield)
  : matrix{playfield}
{

}

void Controller::Tick()
{
  CheckKeyboardInput();
  CheckGamepadInput();
  DrawText(TextFormat("auto repeat: %f", deltatime.auto_repeat), 20, 300, 20, GREEN);
}

void Controller::Hold()
{
  matrix.GetHandler().Hold();
}

void Controller::Rotate(Tetro::Rotation rotation)
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
    if (time >= deltatime.drop_delay) {
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
    if (time >= deltatime.step_delay) {
      tetro.Move(movement);
      matrix.GetHandler().ResetLock();
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

void Controller::CheckSideStep()
{
  // set key last pressed
  if (IsKeyPressed(KB_STEP_LEFT)) {
    direction = Tetro::Movement::LEFT;
  } else if (IsKeyPressed(KB_STEP_RIGHT)) {
    direction = Tetro::Movement::RIGHT;
  }

  // Update auto repeat
  if (IsKeyDown(KB_STEP_LEFT) || IsKeyDown(KB_STEP_RIGHT) || IsGamepadButtonDown(0, GP_STEP_LEFT) || IsGamepadButtonDown(0, GP_STEP_RIGHT)) {
    deltatime.auto_repeat += GetFrameTime();
  }

  float repeat_delay{.2f};
  if (deltatime.auto_repeat < 0.01f || deltatime.auto_repeat >= repeat_delay) {
    // keyboard
    if (IsKeyDown(KB_STEP_LEFT) && IsKeyDown(KB_STEP_RIGHT)) {
      SideStep(direction, deltatime.kb_step);
    } else if (IsKeyDown(KB_STEP_LEFT)) {
      SideStep(Tetro::Movement::LEFT, deltatime.kb_step);
    } else if (IsKeyDown(KB_STEP_RIGHT)) {
      SideStep(Tetro::Movement::RIGHT, deltatime.kb_step);
    }

    // controller
    if (IsGamepadButtonDown(0, GP_STEP_LEFT)) {
      SideStep(Tetro::Movement::LEFT, deltatime.gp_step);
    } else if (IsGamepadButtonDown(0, GP_STEP_RIGHT)) {
      SideStep(Tetro::Movement::RIGHT, deltatime.gp_step);
    }
  }
  // Reset auto repeat
  if (IsGamepadAvailable(0)) {
    if (IsKeyUp(KB_STEP_LEFT) && IsKeyUp(KB_STEP_RIGHT) && IsGamepadButtonUp(0, GP_STEP_LEFT) && IsGamepadButtonUp(0, GP_STEP_RIGHT)) {
      deltatime.auto_repeat = 0.f;
    }
  } else {
    if (IsKeyUp(KB_STEP_LEFT) && IsKeyUp(KB_STEP_RIGHT)) {
      deltatime.auto_repeat = 0.f;
    }
  }
}

void Controller::CheckKeyboardInput()
{
  if (!matrix.IsPaused()) {
    if (IsKeyPressed(KB_ROTATE_CCW)) {
      Rotate(Tetro::Rotation::CCW);
    } else if (IsKeyPressed(KB_ROTATE_CW)) {
      Rotate(Tetro::Rotation::CW);
    }

    if (IsKeyDown(KB_SOFT_DROP)) {
      SoftDrop(deltatime.kb_drop);
    } else if (IsKeyPressed(KB_HARD_DROP)) {
      HardDrop();
    }
    
    CheckSideStep();
    
    if (IsKeyPressed(KB_HOLD)) {
      Hold();
    }

    if (IsKeyPressed(KB_RESET)) {
      Reset();
    }
  }

  if (IsKeyPressed(KB_PAUSE)) {
    Pause();
  }

  if (IsKeyUp(KB_STEP_LEFT) && IsKeyUp(KB_STEP_RIGHT)) {
    deltatime.kb_step = deltatime.step_delay;
  }
  if (IsKeyUp(KB_SOFT_DROP)) {
    deltatime.kb_drop = deltatime.step_delay;
  }
}

void Controller::CheckGamepadInput()
{
  if (IsGamepadAvailable(0)) {
    if (!matrix.IsPaused()) {
      if (IsGamepadButtonPressed(0, GP_ROTATE_CCW) || IsGamepadButtonPressed(0, GP_ROTATE_CCW_ALT)) {
        Rotate(Tetro::Rotation::CCW);
      } else if (IsGamepadButtonPressed(0, GP_ROTATE_CW) || IsGamepadButtonPressed(0, GP_ROTATE_CW_ALT)) {
        Rotate(Tetro::Rotation::CW);
      }

      if (IsGamepadButtonDown(0, GP_SOFT_DROP)) {
        SoftDrop(deltatime.gp_drop);
      } else if (IsGamepadButtonPressed(0, GP_HARD_DROP) || IsGamepadButtonPressed(0, GP_HARD_DROP_ALT)) {
        HardDrop();
      }

      CheckSideStep();

      if (IsGamepadButtonPressed(0, GP_HOLD) || IsGamepadButtonPressed(0, GP_HOLD_ALT)) {
        Hold();
      }

      if (IsGamepadButtonPressed(0, GP_RESET)) {
        Reset();
      }
    }

    if (IsGamepadButtonPressed(0, GP_PAUSE)) {
      Pause();
    }

    if (IsGamepadButtonUp(0, GP_STEP_LEFT) && IsGamepadButtonUp(0, GP_STEP_RIGHT)) {
      deltatime.gp_step = deltatime.step_delay;
    }
    if (IsGamepadButtonUp(0, GP_SOFT_DROP)) {
      deltatime.gp_drop = deltatime.step_delay;
    }
  }
}

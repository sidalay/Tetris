#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include "matrix.hpp"

struct Controller
{
  Controller(Playfield&);
  void Tick();

private:
  Playfield& matrix;
  float keyboard{1.f/20.f};
  float gamepad{1.f/20.f};

  void Hold();
  void Spin(Tetro::Rotation);
  void SoftDrop(float&);
  void HardDrop();
  void SideStep(Tetro::Movement, float&);
  void Pause();
  void CheckInput();
  void CheckGamepadInput();
};

#endif // CONTROLLER_HPP

#define HARD_DROP   KEY_UP
#define SOFT_DROP   KEY_DOWN
#define STEP_LEFT   KEY_LEFT
#define STEP_RIGHT  KEY_RIGHT
#define ROTATE_CW   KEY_D
#define ROTATE_CCW  KEY_A
#define HOLD        KEY_LEFT_SHIFT
#define PAUSE       KEY_P

#define GP_HARD_DROP   GAMEPAD_BUTTON_LEFT_FACE_UP
#define GP_SOFT_DROP   GAMEPAD_BUTTON_LEFT_FACE_DOWN
#define GP_STEP_LEFT   GAMEPAD_BUTTON_LEFT_FACE_LEFT
#define GP_STEP_RIGHT  GAMEPAD_BUTTON_LEFT_FACE_RIGHT
#define GP_ROTATE_CCW  GAMEPAD_BUTTON_RIGHT_FACE_UP
#define GP_ROTATE_CW   GAMEPAD_BUTTON_RIGHT_FACE_RIGHT
#define GP_HOLD        GAMEPAD_BUTTON_RIGHT_FACE_LEFT
#define GP_PAUSE       GAMEPAD_BUTTON_MIDDLE_RIGHT

#define GP_HARD_DROP_ALT   GAMEPAD_BUTTON_RIGHT_FACE_DOWN
#define GP_SOFT_DROP_ALT   
#define GP_STEP_LEFT_ALT   
#define GP_STEP_RIGHT_ALT  
#define GP_ROTATE_CCW_ALT  GAMEPAD_BUTTON_LEFT_TRIGGER_1
#define GP_ROTATE_CW_ALT   GAMEPAD_BUTTON_RIGHT_TRIGGER_1
#define GP_HOLD_ALT        GAMEPAD_BUTTON_RIGHT_TRIGGER_2
#define GP_PAUSE_ALT       
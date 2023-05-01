#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include "matrix.hpp"


class Controller
{
struct Deltatime
{
  float kb_drop{1.f/20.f};
  float kb_step{1.f/15.f};
  float gp_drop{1.f/20.f};
  float gp_step{1.f/15.f};
  float auto_repeat{0.f};
  const float drop_delay{1.f/20.f};
  const float step_delay{1.f/15.f};
};

public:
  Controller(Playfield&);
  void Tick();

private:
  Playfield& matrix;
  Deltatime deltatime;
  Tetro::Movement direction{};

  void Hold();
  void Rotate(Tetro::Rotation);
  void SoftDrop(float&);
  void HardDrop();
  void SideStep(Tetro::Movement, float&);
  void Pause();
  void Reset();
  void CheckSideStep();
  void CheckKeyboardInput();
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
#define RESET       KEY_F1

#define GP_HARD_DROP   GAMEPAD_BUTTON_LEFT_FACE_UP
#define GP_SOFT_DROP   GAMEPAD_BUTTON_LEFT_FACE_DOWN
#define GP_STEP_LEFT   GAMEPAD_BUTTON_LEFT_FACE_LEFT
#define GP_STEP_RIGHT  GAMEPAD_BUTTON_LEFT_FACE_RIGHT
#define GP_ROTATE_CCW  GAMEPAD_BUTTON_RIGHT_FACE_UP
#define GP_ROTATE_CW   GAMEPAD_BUTTON_RIGHT_FACE_RIGHT
#define GP_HOLD        GAMEPAD_BUTTON_RIGHT_FACE_LEFT
#define GP_PAUSE       GAMEPAD_BUTTON_MIDDLE_RIGHT
#define GP_RESET       GAMEPAD_BUTTON_MIDDLE_LEFT

#define GP_HARD_DROP_ALT   GAMEPAD_BUTTON_RIGHT_FACE_DOWN
#define GP_SOFT_DROP_ALT   
#define GP_STEP_LEFT_ALT   
#define GP_STEP_RIGHT_ALT  
#define GP_ROTATE_CCW_ALT  GAMEPAD_BUTTON_LEFT_TRIGGER_1
#define GP_ROTATE_CW_ALT   GAMEPAD_BUTTON_RIGHT_TRIGGER_1
#define GP_HOLD_ALT        GAMEPAD_BUTTON_RIGHT_TRIGGER_2
#define GP_PAUSE_ALT       
#define GP_RESET_ALT
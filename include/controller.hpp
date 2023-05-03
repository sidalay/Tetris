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
  explicit Controller(Playfield&);
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

// GAMEPLAY CONTROLS
#define KB_HARD_DROP        KEY_UP
#define KB_SOFT_DROP        KEY_DOWN
#define KB_STEP_LEFT        KEY_LEFT
#define KB_STEP_RIGHT       KEY_RIGHT
#define KB_ROTATE_CW        KEY_D
#define KB_ROTATE_CCW       KEY_A
#define KB_HOLD             KEY_LEFT_SHIFT
#define KB_PAUSE            KEY_P
#define KB_RESET            KEY_F1

#define KB_HARD_DROP_ALT   
#define KB_SOFT_DROP_ALT   
#define KB_STEP_LEFT_ALT   
#define KB_STEP_RIGHT_ALT  
#define KB_ROTATE_CW_ALT   
#define KB_ROTATE_CCW_ALT  
#define KB_HOLD_ALT        
#define KB_PAUSE_ALT       
#define KB_RESET_ALT       

#define GP_HARD_DROP       GAMEPAD_BUTTON_LEFT_FACE_UP
#define GP_SOFT_DROP       GAMEPAD_BUTTON_LEFT_FACE_DOWN
#define GP_STEP_LEFT       GAMEPAD_BUTTON_LEFT_FACE_LEFT
#define GP_STEP_RIGHT      GAMEPAD_BUTTON_LEFT_FACE_RIGHT
#define GP_ROTATE_CCW      GAMEPAD_BUTTON_RIGHT_FACE_UP
#define GP_ROTATE_CW       GAMEPAD_BUTTON_RIGHT_FACE_RIGHT
#define GP_HOLD            GAMEPAD_BUTTON_RIGHT_FACE_LEFT
#define GP_PAUSE           GAMEPAD_BUTTON_MIDDLE_RIGHT
#define GP_RESET           GAMEPAD_BUTTON_MIDDLE_LEFT

#define GP_HARD_DROP_ALT   GAMEPAD_BUTTON_RIGHT_FACE_DOWN
#define GP_SOFT_DROP_ALT   
#define GP_STEP_LEFT_ALT   
#define GP_STEP_RIGHT_ALT  
#define GP_ROTATE_CCW_ALT  GAMEPAD_BUTTON_LEFT_TRIGGER_1
#define GP_ROTATE_CW_ALT   GAMEPAD_BUTTON_RIGHT_TRIGGER_1
#define GP_HOLD_ALT        GAMEPAD_BUTTON_RIGHT_TRIGGER_2
#define GP_PAUSE_ALT       
#define GP_RESET_ALT

// MENU CONTROLS
#define KB_SELECT          KEY_ENTER
#define KB_BACK            KEY_BACKSPACE

#define KB_SELECT_ALT      KEY_SPACE
#define KB_BACK_ALT        KEY_ESCAPE

#define GP_SELECT          GAMEPAD_BUTTON_RIGHT_FACE_DOWN
#define GP_BACK            GAMEPAD_BUTTON_RIGHT_FACE_RIGHT

#define GP_SELECT_ALT      GAMEPAD_BUTTON_MIDDLE_RIGHT
#define GP_BACK_ALT
#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include "matrix.hpp"

#define HARD_DROP   KEY_UP
#define SOFT_DROP   KEY_DOWN
#define STEP_LEFT   KEY_LEFT
#define STEP_RIGHT  KEY_RIGHT
#define ROTATE_CW   KEY_D
#define ROTATE_CCW  KEY_A
#define HOLD        KEY_LEFT_SHIFT
#define PAUSE       KEY_P

struct Controller
{
  Controller(Playfield&);
  void Tick();

private:
  Playfield& matrix;
  float deltatime{1.f/20.f};

  void Hold();
  void Spin(Tetro::Rotation);
  void SoftDrop();
  void HardDrop();
  void SideStep(Tetro::Movement);
  void CheckInput();
};

#endif // CONTROLLER_HPP
#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include "matrix.hpp"

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
#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "raylib.h"

#include <string>

struct Window
{
  int width{1280};
  int height{720};
  std::string title{"tetris"};

  void Tick();
};

#endif // WINDOW_HPP
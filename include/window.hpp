#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "raylib.h"

#include <string>

namespace Window
{
  extern int width;
  extern int height;
  extern std::string title;

  void Tick();
};

#endif // WINDOW_HPP
#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <string>

namespace Window
{
  extern int width;
  extern int height;
  extern std::string title;
  extern const float cell_size_percentage;
  extern const float well_width;
  extern const float well_height;
  extern const float h_margin;

  void Tick();
};

#endif // WINDOW_HPP
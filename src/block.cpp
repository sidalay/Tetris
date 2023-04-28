#include "block.hpp"

#include "window.hpp"

void Tetro::Block::Tick() 
{
  float cell_size{Window::height * Window::cell_size_percentage};
  float borderX{(Window::width - (Window::well_width * Window::height)) * .5f};
  area.y = cell_size * screen_row;
  area.x = borderX + (cell_size * screen_col); 
  area.width = cell_size;
  area.height = cell_size;
}

void Tetro::Block::Draw()
{
  float offset{1.f};
  DrawRectangleRec(area, color);
  Rectangle outline{area.x - offset, area.y - offset, area.width + offset, area.height + offset};
  DrawRectangleLinesEx(outline, 2.f, BLACK);
}
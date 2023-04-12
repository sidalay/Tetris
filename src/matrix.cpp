#include "matrix.hpp"

Playfield::Playfield()
{
  UpdateFrames();
  InitializeMatrix();
}

void Playfield::Tick()
{
  UpdateFrames();
  UpdateMatrix();
}

void Playfield::Draw()
{
  DrawMatrix();
  DrawBorder();
}

void Playfield::DrawBorder()
{
  DrawRectangleLines(border.area.x, border.area.y, border.area.width, border.area.height, WHITE);
  // DrawRectangleLines(489 - (hold.area.x + spacing), 59, hold.area.x+2, hold.area.y+2, WHITE);
  // DrawRectangleLines(489 + border.area.x + spacing, 59, hold.area.x+2, hold.area.y+2, WHITE);
  // DrawRectangleLines(489 + border.area.x + spacing, 59 + preview.area.x + spacing, preview.area.x+2, preview.area.y+2, WHITE);
}

void Playfield::DrawMatrix()
{
  for (auto& cell : matrix) {
    DrawRectangle(cell.area.x, cell.area.y, cell.area.width, cell.area.height, cell.color);
    DrawRectangleLines(cell.area.x, cell.area.y, cell.area.width, cell.area.height, BLACK);
  }
}

void Playfield::DrawHold()
{
  
}

void Playfield::DrawPreview()
{
  
}

void Playfield::InitializeMatrix()
{
  int count{};
  matrix.reserve(240);
  for (float y{}; y < border.area.height; y += Window::height * .045f) {
    for (float x{}; x < border.area.width; x += Window::height * .045f) {
      if (static_cast<int>(y) % 2 == 0) {
        matrix.emplace_back(
          Rectangle{border.area.x + x, 
                    border.area.y + y, 
                    Window::height * .045f, 
                    Window::height * .045f}, 
                    count++ % 2 == 0 ? Color{ 15, 14, 14, 255 } : Color{ 20, 19, 19, 255 });
      } else {
        matrix.emplace_back(
          Rectangle{border.area.x + x, 
                    border.area.y + y, 
                    Window::height * .045f, 
                    Window::height * .045f}, 
                    count++ % 2 != 0 ? Color{ 15, 14, 14, 255 } : Color{ 20, 19, 19, 255 });
      }
    }
  }
}

void Playfield::UpdateFrames()
{
  border.area.x = Window::width * .3125f;
  border.area.y = Window::height * .05f;
  border.area.width = Window::width * .375f;
  border.area.height = Window::height * .9f;
}

void Playfield::UpdateMatrix()
{

}
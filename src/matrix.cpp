#include "matrix.hpp"

const float cell_size{.045f}; // 4.5% of height 
const float well_width{10.f * cell_size}; // 10 cells wide
const float w_margin{(1.f - well_width) * .5f}; // 22.5% margin
const float h_margin{.05f}; // 5% from top/bottom of screen
const float well_height{1 - (h_margin * 2.f)}; // 90% of height  

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
  // DrawMatrix();
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

// void Playfield::InitializeMatrix()
// {
//   int count{};
//   matrix.reserve(240);
//   for (float y{0}; y < border.area.height + (4 * (Window::height * cell_size)); y += Window::height * cell_size) {
//     for (float x{1}; x < border.area.width; x += Window::height * cell_size) {
//       if (static_cast<int>(y) % 2 == 0) {
//         matrix.emplace_back(
//           Rectangle{border.area.x + x, 
//                     border.area.y + y, 
//                     Window::height * cell_size, 
//                     Window::height * cell_size}, 
//                     count++ % 2 == 0 ? Color{ 15, 14, 14, 255 } : Color{ 20, 19, 19, 255 });
//       } else {
//         matrix.emplace_back(
//           Rectangle{border.area.x + x, 
//                     border.area.y + y, 
//                     Window::height * cell_size, 
//                     Window::height * cell_size}, 
//                     count++ % 2 != 0 ? Color{ 15, 14, 14, 255 } : Color{ 20, 19, 19, 255 });
//       }
//     }
//   }
// }

void Playfield::InitializeMatrix()
{
  
}

void Playfield::UpdateFrames()
{
  border.area.x = Window::width * ((1.f - ((Window::height * well_width)/Window::width)) * .5f);
  border.area.y = Window::height * h_margin;
  border.area.width = Window::height * well_width;
  border.area.height = Window::height * well_height;
}

void Playfield::UpdateMatrix()
{
  if (IsWindowResized()) {

  }
}

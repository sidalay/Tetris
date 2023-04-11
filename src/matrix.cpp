#include "matrix.hpp"

Playfield::Playfield()
{
  InitializeMatrix();
}

void Playfield::Tick()
{

}

void Playfield::Draw()
{
  DrawBorder();
  DrawMatrix();
}

void Playfield::DrawBorder()
{
  DrawRectangleLines(489, 59, border.x+2, border.y+2, WHITE);
  DrawRectangleLines(489 - (hold.x + spacing), 59, hold.x+2, hold.y+2, WHITE);
  DrawRectangleLines(489 + border.x + spacing, 59, next.x+2, next.y+2, WHITE);
  DrawRectangleLines(489 + border.x + spacing, 59 + preview.x + spacing, preview.x+2, preview.y+2, WHITE);
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

void Playfield::DrawNext()
{

}

void Playfield::DrawPreview()
{
  
}

void Playfield::InitializeMatrix()
{
  int count{};
  matrix.reserve(240);
  for (float y{}; y < border.y; y += border.y / grid.y) {
    for (float x{}; x < border.x; x += border.x / grid.x) {
      if (static_cast<int>(y) % 2 == 0) {
        matrix.emplace_back(Rectangle{490 + x, 60 + y, border.x / grid.x, border.y / grid.y}, count++ % 2 == 0 ? Color{ 15, 14, 14, 255 } : Color{ 20, 19, 19, 255 });
      } else {
        matrix.emplace_back(Rectangle{490 + x, 60 + y, border.x / grid.x, border.y / grid.y}, count++ % 2 != 0 ? Color{ 15, 14, 14, 255 } : Color{ 20, 19, 19, 255 });
      }
    }
  }
}
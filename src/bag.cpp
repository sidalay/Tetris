#include "bag.hpp"
#include "window.hpp"

Bag::Bag() 
{
  Fill();
}

void Bag::Tick()
{
  for (auto& tetromino : bag) {
    tetromino.Tick();
  }
}

void Bag::Draw()
{
  float cell_size{Window::height * Window::cell_size_percentage};
  Vector2 area{cell_size * 9.f, cell_size * 4.f};
  for (int i{}; i < 3; ++i) {
    if (bag[i].GetType() == Tetro::Shape::I) {
      bag[i].Draw(Vector2{area.x - (cell_size * 0.5f), area.y - cell_size * 0.5f});
    } else if (bag[i].GetType() == Tetro::Shape::O) {
      bag[i].Draw(Vector2{area.x - (cell_size * 0.5f), area.y});
    } else {
      bag[i].Draw(area);
    }
    area.y += cell_size * 5.f;
  }
}

void Bag::Fill()
{
  std::vector<int> shapes{randomizer()};
  for (auto& shape : shapes) {
    bag.emplace_back(Tetromino{Tetro::Shape{shape}});
  }
}

Tetromino Bag::Pull()
{
  Tetromino piece{bag.front()};
  bag.erase(bag.begin());
  if (bag.size() < 8) {
    Fill();
  }
  return piece;
}


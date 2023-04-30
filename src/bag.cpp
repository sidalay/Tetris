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

void Bag::Draw(Rectangle bagframe)
{
  int tetrominos{5};
  float cell_size{Window::height * Window::cell_size_percentage};
  float w_margin{bagframe.width - (cell_size * 4.f)}; // d = (W - (n*tw))
  float h_margin{(bagframe.height - (tetrominos * (cell_size * 2.f))) / (tetrominos + 1)}; // d = (H - (n*th)) / n + 1 

  for (int i{1}; i <= tetrominos; ++i) {
    Vector2 pos{
      bagframe.x + w_margin + (bagframe.width * .1f), 
      bagframe.y + (i * h_margin) + ((i-1) * (cell_size * 2.f))
    };
    if (bag[i-1].GetType() == Tetro::Shape::I) {
      bag[i-1].Draw(Vector2{pos.x, pos.y - (cell_size * .5f)});
    } else if (bag[i-1].GetType() == Tetro::Shape::O) {
      bag[i-1].Draw(pos);
    } else {
      bag[i-1].Draw(Vector2{pos.x + (cell_size * .5f), pos.y});
    }
  }
}

void Bag::Reset()
{
  bag.clear();
  Fill();
}

void Bag::CheckScaling()
{
  for (auto& tetromino : bag) {
    tetromino.CheckScaling();
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


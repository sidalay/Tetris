#include "bag.hpp"

Bag::Bag() 
{
  for (int i{}; i < 2; ++i) {
    Fill();
  }
}

void Bag::Tick()
{
  for (auto& tetromino : bag) {
    tetromino.Tick();
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


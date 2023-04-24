#include "bag.hpp"

Bag::Bag() 
{
  Fill();
}

void Bag::Fill()
{
  std::vector<double> rolled{};
  std::vector<double> ws{1.0/7.0, 1.0/7.0, 1.0/7.0, 1.0/7.0, 1.0/7.0, 1.0/7.0, 1.0/7.0};
  for (double i{7.0}; i > 0.0; --i) {
    for (auto& w : ws) {
      w = 1.0/i;
    }
    for (auto& roll : rolled) {
      ws.at(roll) = 0.0;
    }
    std::discrete_distribution<int> d(std::begin(ws), std::end(ws));
    int shape{d(randomizer.GetEngine())};
    rolled.push_back(shape);
    bag.emplace_back(Tetromino{Tetro::Shape{shape}});
  }
}

void Bag::Pull()
{

}


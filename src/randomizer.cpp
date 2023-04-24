#include "randomizer.hpp"

std::vector<int> Randomizer::operator()()
{
  std::vector<int> rolled{};
  std::vector<double> ws{1.0/7.0, 1.0/7.0, 1.0/7.0, 1.0/7.0, 1.0/7.0, 1.0/7.0, 1.0/7.0};
  for (double i{7.0}; i > 0.0; --i) {
    for (auto& w : ws) {
      w = 1.0/i;
    }
    for (auto& roll : rolled) {
      ws.at(roll) = 0.0;
    }
    std::discrete_distribution<int> dist(std::begin(ws), std::end(ws));
    rolled.push_back(dist(RandomEngine));
  }
  return rolled;
}
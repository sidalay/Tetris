#include "randomizer.hpp"

#include <array>

std::vector<int> Randomizer::operator()()
{
  std::vector<int> rolled{};
  std::array<double, 7> probabilities{};
  for (double total{7.0}; total > 0.0; --total) {
    for (auto& chance : probabilities) {
      chance = 1.0/total;
    }
    for (auto& roll : rolled) {
      probabilities.at(roll) = 0.0;
    }
    std::discrete_distribution<int> dist(std::begin(probabilities), std::end(probabilities));
    rolled.push_back(dist(RandomEngine));
  }
  return rolled;
}
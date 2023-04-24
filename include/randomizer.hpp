#ifndef RANDOMIZER_HPP
#define RANDOMIZER_HPP

#include <random>
#include <vector>

struct Randomizer
{
public:
  Randomizer() = default;
  std::vector<int> operator()();
private:
  std::random_device  Seed;
  std::mt19937        RandomEngine{std::mt19937{Seed()}};
};

#endif // RANDOMIZER_HPP
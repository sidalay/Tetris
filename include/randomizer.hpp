#ifndef RANDOMIZER_HPP
#define RANDOMIZER_HPP

#include <random>

struct Randomizer
{
public:
  Randomizer() = default;
  int operator()(std::uniform_int_distribution<int>& Range);
  std::mt19937& GetEngine() {return RandomEngine;}
private:
  std::random_device  Seed;
  std::mt19937        RandomEngine{std::mt19937{Seed()}};
};

#endif // RANDOMIZER_HPP
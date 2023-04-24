#include "randomizer.hpp"

int Randomizer::operator()(std::uniform_int_distribution<int>& Range)
{
  return Range(RandomEngine);
}
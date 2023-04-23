#include "bag.hpp"

#include <iostream>

Bag::Bag() 
{
  Fill();
}

void Bag::Fill()
{
  std::uniform_int_distribution<int> range{0,6};
  for (int i{}; i < 7; ++i) {
    std::cout << randomizer(range) << ' ';
  }
}

void Bag::Pull()
{

}


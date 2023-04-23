#ifndef BAG_HPP
#define BAG_HPP

#include "randomizer.hpp"
#include "tetromino.hpp"

#include <vector>

struct Bag
{
public:
  Bag();

  // Retrieve a piece
  void Pull();
  // View current Bag

  // Fill the bag
  void Fill();
private:
  std::vector<Tetromino> bag{};
  Randomizer             randomizer{};
  
  // Check capacity
  bool IsEmpty() const {return bag.empty();}
};

#endif // BAG_HPP
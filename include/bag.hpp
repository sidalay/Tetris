#ifndef BAG_HPP
#define BAG_HPP

#include "randomizer.hpp"
#include "tetromino.hpp"

struct Bag
{
public:
  Bag();

  void Tick();
  void Draw(Rectangle);
  void Reset();
  void CheckScaling();
  Tetromino Pull();
  [[nodiscard]] const std::vector<Tetromino> View() const {return bag;}

private:
  std::vector<Tetromino> bag{};
  Randomizer             randomizer{};
  
  void Fill();
};

#endif // BAG_HPP
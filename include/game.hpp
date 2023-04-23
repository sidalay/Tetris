#ifndef GAME_HPP
#define GAME_HPP

#include "bag.hpp"
#include "matrix.hpp"

namespace Game
{
  enum class State
  {

  };

  struct Properties
  {
    float     deltatime{};
    float     updatetime{1.f/144.f};
    float     lockdown{};
    int       fps{144};
    Playfield matrix{};

    // test
    float tetro_deltatime{};
    float tetro_updatetime{1.f};
    Tetromino tetro_test{Tetro::Shape::Z};
    Bag bag{};
  };

  void Run();
  void Initialize(Properties&);
  void Tick(Properties&);
}

#endif // GAME_HPP
#ifndef GAME_HPP
#define GAME_HPP

#include "controller.hpp"

namespace Game
{
  enum class State
  {

  };

  struct Properties
  {
    float     deltatime{};
    float     updatetime{1.f/60.f};
    float     lockdown{};
    int       fps{60};
    Playfield matrix{};

    // test
    float tetro_deltatime{};
    float tetro_updatetime{1.f};
    Controller controller{matrix};
    Bag bag{};
    Tetromino tetro_current{bag.Pull()};
  };

  void Run();
  void Initialize(Properties&);
  void Tick(Properties&);
}

#endif // GAME_HPP
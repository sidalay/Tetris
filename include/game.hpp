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
    float     updatetime{1.f/144.f};
    float     lockdown{};
    int       fps{144};
    Playfield matrix{};

    // test
    float tetro_deltatime{};
    float tetro_updatetime{1.f};
    Controller controller{matrix};
  };

  void Run();
  void Initialize(Properties&);
  void Tick(Properties&);
}

#endif // GAME_HPP
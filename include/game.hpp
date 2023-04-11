#ifndef GAME_HPP
#define GAME_HPP

#include "window.hpp"
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
    Window    window{};
    Playfield matrix{};
  };

  void Run();
  void Initialize(Properties&);
  void Tick(Properties&);
}

#endif // GAME_HPP
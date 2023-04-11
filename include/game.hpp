#ifndef GAME_HPP
#define GAME_HPP

namespace Game
{
  struct Properties
  {
    float deltatime{};
    float lockdown{};
  };

  void Run();
  void Tick();
  void Initialize();
}

#endif // GAME_HPP
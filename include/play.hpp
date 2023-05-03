#ifndef PLAY_HPP
#define PLAY_HPP

#include "matrix.hpp"
#include "level.hpp"
#include "score.hpp"
#include "controller.hpp"

namespace Game
{

class Play
{
public:
enum class Mode {
  NEUTRAL, MARATHON, ULTRA, FORTY, ENDLESS, VERSUS
};

  void Run();
  void Tick();
  void Draw();
  void SetMode(Mode newMode) {mode = newMode;}
private:
  Mode       mode{};
  Level      level{};
  Score      score{};
  Playfield  playfield{};
  Controller controller{playfield};

  void TickMarathon();
  void DrawMarathon();

  void TickUltra();
  void DrawUltra();

  void TickForty();
  void DrawForty();

  void TickEndless();
  void DrawEndless();

  void TickVersus();
  void DrawVersus();
};

}

#endif // PLAY_HPP
#ifndef PLAY_HPP
#define PLAY_HPP

#include "matrix.hpp"
#include "level.hpp"
#include "score.hpp"

namespace Game
{

class Play
{
enum class Mode {
  MARATHON, ULTRA, FORTY, ENDLESS, VERSUS
};

public:
  void Run();
private:
  Mode mode{Play::Mode::MARATHON};
  Playfield playfield{};
  Level level{};
  Score score{};
};

}

#endif // PLAY_HPP
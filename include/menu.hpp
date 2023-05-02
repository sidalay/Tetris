#ifndef MENU_HPP
#define MENU_HPP

#include "play.hpp"
#include "controller.hpp"

namespace Game
{

class Menu 
{
enum class Screen {
  TITLE, MAIN, PLAY, PAUSE, SETTINGS, GAMEOVER, HELP
};

public:
  explicit Menu() = default;

  void Tick();
  void Draw();
  [[nodiscard]] constexpr Screen CurrentScreen()const {return screen;}

private:
  Screen screen{};
  // Controller controller{};

  void TickTitle();
  void DrawTitle();

  void TickMain();
  void DrawMain();

  void TickPlay();
  void DrawPlay();

  void TickPause();
  void DrawPause();

  void TickSettings();
  void DrawSettings();

  void TickGameover();
  void DrawGameover();

  void TickHelp();
  void DrawHelp();
};

}

#endif // MENU_HPP
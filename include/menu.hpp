#ifndef MENU_HPP
#define MENU_HPP

#include "controller.hpp"
#include "play.hpp"
#include "lerp.hpp"

namespace Game
{

class Menu 
{
enum class Screen {
  TITLE, MAIN, PLAY, SETTINGS, GAMEOVER, HELP
};
enum class State {
  NEUTRAL, PAUSE, COUNTDOWN, TRANSITION_IN, TRANSITION_OUT
};
enum class Selection {
  START, SETTINGS, HELP, PAUSE, BACK, MARATHON, ULTRA, VERSUS, FORTY
};

public:
  explicit Menu() = default;

  void Tick();
  void Draw();
  [[nodiscard]] constexpr Screen CurrentScreen() const {return current_screen;}

private:
  Screen     current_screen{};
  Screen     next_screen{};
  State      state{};
  Selection  select{};
  float      transition{};
  float      countdown{3.f};
  // Controller controller{};

  void TickScreen();
  void DrawScreen();
  void TickState();
  void DrawState();

  void TickTitle();
  void DrawTitle();

  void TickMain();
  void DrawMain();

  void TickPlay();
  void DrawPlay();

  void TickSettings();
  void DrawSettings();

  void TickGameover();
  void DrawGameover();

  void TickHelp();
  void DrawHelp();

  void TickNeutral();

  void TickPause();
  void DrawPause();

  void TickCountdown();
  void DrawCountdown();

  void TransitionIn(Screen);
  void TransitionOut();
  void DrawTransition();

};

}

#endif // MENU_HPP
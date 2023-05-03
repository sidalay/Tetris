#ifndef MENU_HPP
#define MENU_HPP

#include "play.hpp"
#include "lerp.hpp"

namespace Game
{

class Menu 
{
enum class Screen {
  TITLE, MAIN, PLAY, GAME, SETTINGS, GAMEOVER, HELP
};
enum class State {
  NEUTRAL, PAUSE, COUNTDOWN, QUIT, TRANSITION_IN, TRANSITION_OUT
};
enum class Selection {
  NEUTRAL, START, SETTINGS, HELP, PAUSE, BACK, QUIT, CONFIRM_QUIT, CANCEL, RESUME, MARATHON, ULTRA, VERSUS, FORTY, ENDLESS
};
enum class Movement {
  UP, DOWN, LEFT, RIGHT
};
struct Properties {
  float transition{};
  float countdown{3.f};
  int   select_index{};
  bool  standby{};
  bool  exit{};
};

public:
  explicit Menu() = default;

  void Tick();
  void Draw();
  [[nodiscard]] constexpr bool ShouldExit() const noexcept {return menu.exit;}
  [[nodiscard]] constexpr Screen CurrentScreen() const noexcept {return current_screen;}

private:
  Screen     current_screen{};
  Screen     next_screen{};
  State      state{};
  Selection  select{};
  Properties menu{};
  Play       play{};

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

  void TickGame();
  void DrawGame();

  void TickSettings();
  void DrawSettings();

  void TickGameover();
  void DrawGameover();

  void TickHelp();
  void DrawHelp();

  void TickQuit();
  void DrawQuit();

  void TickNeutral();

  void TickPause();
  void DrawPause();

  void TickCountdown();
  void DrawCountdown();

  void Button(Selection, Rectangle, int);
  void DrawButton(Selection, Rectangle, int);

  void Transition(Screen);
  void TransitionIn(Screen);
  void TransitionOut();
  void DrawTransition();

  void CycleMenu(std::vector<Selection>&);
  bool CheckInputSelect();
  bool CheckInputBack();
  bool CheckInputCycle(Menu::Movement);
  bool CheckInputPause();

};

}

#endif // MENU_HPP
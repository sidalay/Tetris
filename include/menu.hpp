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
  NEUTRAL, START, SETTINGS, HELP, PAUSE, BACK, MARATHON, ULTRA, VERSUS, FORTY
};
struct Properties {
  float transition{};
  float countdown{3.f};
  int   select_index{};
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
  Properties menu{};
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

  void Button(Selection, Rectangle, int);
  void DrawButton(Selection, Rectangle, int);

  void Transition(Screen);
  void TransitionIn(Screen);
  void TransitionOut();
  void DrawTransition();

  void CycleMenu(std::vector<Selection>&);
  bool CheckSelectInput();

};

}

#endif // MENU_HPP
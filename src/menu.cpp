#include "menu.hpp"

#include "window.hpp"

void Game::Menu::Tick()
{
  TickScreen();
  TickState();
}

void Game::Menu::Draw()
{
  DrawScreen();
  DrawState();
}

void Game::Menu::TickScreen()
{
  if (state != State::PAUSE && state != State::COUNTDOWN) {
    switch (current_screen)
    {
    case Screen::TITLE:
      TickTitle();
      break;
    case Screen::MAIN:
      TickMain();
      break;
    case Screen::PLAY:
      TickPlay();
      break;
    case Screen::SETTINGS:
      TickSettings();
      break;
    case Screen::GAMEOVER:
      TickGameover();
      break;
    case Screen::HELP:
      TickHelp();
      break;
    }
  }
}

void Game::Menu::DrawScreen()
{
  switch (current_screen)
  {
  case Screen::TITLE:
    DrawTitle();
    break;
  case Screen::MAIN:
    DrawMain();
    break;
  case Screen::PLAY:
    DrawPlay();
    break;
  case Screen::SETTINGS:
    DrawSettings();
    break;
  case Screen::GAMEOVER:
    DrawGameover();
    break;
  case Screen::HELP:
    DrawHelp();
    break;
  }
}

void Game::Menu::TickState()
{
  switch (state)
  {
    case State::NEUTRAL:
      TickNeutral();
      break;
    case State::PAUSE:
      TickPause();
      break;
    case State::COUNTDOWN:
      TickCountdown();
      break;
    case State::TRANSITION_IN:
      TransitionIn(next_screen);
      break;
    case State::TRANSITION_OUT:
      TransitionOut();
      break;
  }
}

void Game::Menu::DrawState()
{
  switch (state)
  {
    case State::NEUTRAL:
      break;
    case State::PAUSE:
      DrawPause();
      break;
    case State::COUNTDOWN:
      DrawCountdown();
      break;
    case State::TRANSITION_IN: [[fallthrough]];
    case State::TRANSITION_OUT:
      DrawTransition();
      break;
  }
}

void Game::Menu::TickTitle()
{
  if (IsKeyPressed(KB_SELECT) || IsKeyPressed(KB_SELECT_ALT)) {
    Transition(Screen::MAIN);
  }
}

void Game::Menu::DrawTitle()
{
  // DrawLine(Window::width/2, 0, Window::width/2, Window::height, RAYWHITE);
  DrawText("TITLE SCREEN", Window::width/2 - 3*26, Window::height/2 - 100, 20, GREEN);
  DrawText("Press Enter", Window::width/2 - 3*22, Window::height/2, 20, GREEN);
}

void Game::Menu::TickMain()
{
  std::vector<Selection> select_options{Selection::START, Selection::SETTINGS, Selection::HELP};

  CycleMenu(select_options);

  Rectangle button_rec{Window::width*0.5f - ((Window::width*0.1f)*0.5f), Window::height*0.5f, Window::width * 0.1f, Window::height * 0.05f};
  Button(Selection::START, button_rec, 0);
  Button(Selection::SETTINGS, button_rec, 1);
  Button(Selection::HELP, button_rec, 2);
}

void Game::Menu::DrawMain()
{
  DrawText("MAIN SCREEN", Window::width/2 - 3*24, Window::height/2 - 100, 20, GREEN);
  // DrawText("Press Enter", Window::width/2 - 3*22, Window::height/2, 20, GREEN);
}

void Game::Menu::TickPlay()
{
  std::vector<Selection> select_options{};
  CycleMenu(select_options);
}

void Game::Menu::DrawPlay()
{
  DrawText("PLAY SCREEN", Window::width/2 - 3*24, Window::height/2 - 100, 20, GREEN);
}

void Game::Menu::TickSettings()
{
  std::vector<Selection> select_options{};
  CycleMenu(select_options);
}

void Game::Menu::DrawSettings()
{
  DrawText("SETTINGS SCREEN", Window::width/2 - 3*28, Window::height/2 - 100, 20, GREEN);
}

void Game::Menu::TickGameover()
{
  std::vector<Selection> select_options{};
  CycleMenu(select_options);
}

void Game::Menu::DrawGameover()
{
  DrawText("GAMEOVER SCREEN", Window::width/2 - 3*28, Window::height/2 - 100, 20, GREEN);
}

void Game::Menu::TickHelp()
{
  std::vector<Selection> select_options{};
  CycleMenu(select_options);
}

void Game::Menu::DrawHelp()
{
  DrawText("HELP SCREEN", Window::width/2 - 3*24, Window::height/2 - 100, 20, GREEN);
}

void Game::Menu::TickNeutral()
{
  if (IsKeyPressed(KB_PAUSE)) {
    state = State::PAUSE;
  }
}

void Game::Menu::TickPause()
{
  if (IsKeyPressed(KB_PAUSE)) {
    state = State::COUNTDOWN;
  }
}

void Game::Menu::DrawPause()
{
  DrawRectangle(0, 0, Window::width, Window::height, Color{0,0,0,255});
  DrawText("PAUSE SCREEN", Window::width/2 - 3*26, Window::height/2 - 100, 20, GREEN);
  DrawText("Press P", Window::width/2 - 3*15, Window::height/2, 20, GREEN);
}

void Game::Menu::TickCountdown()
{
  menu.countdown -= GetFrameTime();
  if (menu.countdown <= 0.f) {
    menu.countdown = 3.f;
    state = State::NEUTRAL;
    current_screen = Screen::TITLE;
  }
}

void Game::Menu::DrawCountdown()
{
  DrawRectangle(0, 0, Window::width, Window::height, Color{0,0,0,240});
  if (menu.countdown > 2.f) {
    DrawText("3", Window::width/2 - 20, Window::height/2, 40, GREEN);
  } else if (menu.countdown > 1.f) {
    DrawText("2", Window::width/2 - 20, Window::height/2, 40, GREEN);
  } else {
    DrawText("1", Window::width/2 - 20, Window::height/2, 40, GREEN);
  }
}

void Game::Menu::Button(Selection button_type, Rectangle shape, int id)
{
  if (CheckSelectInput()) {
    switch (select)
    {
      case Selection::START:
        Transition(Screen::PLAY);
        break;
      case Selection::PAUSE:
        break;
      case Selection::SETTINGS:
        Transition(Screen::SETTINGS);
        break;
      case Selection::BACK:
        break;
      case Selection::HELP:
        Transition(Screen::HELP);
        break;
      case Selection::MARATHON:
        break;
      case Selection::ULTRA:
        break;
      case Selection::FORTY:
        break;
      case Selection::VERSUS:
        break;
      default:
        break;
    }
  }

  // draw buttons
  DrawButton(button_type, shape, id);
}

void Game::Menu::DrawButton(Selection button_type, Rectangle shape, int id)
{
  // highlight button if selected
  Color highlight{0,70,255,100};
  if (select != button_type) {
    highlight = {0,255,255,0};
  }

  // set height offset based on button id
  shape.y += (shape.height * 2.f) * id;

  DrawRectangleRounded(shape, 0.5f, 4, GRAY);
  DrawRectangleRounded(shape, 0.5f, 4, highlight);
  DrawRectangleRoundedLines(shape, 0.5f, 4, 2.f, RAYWHITE);

  float offset{1.f};
  DrawRectangleRoundedLines(
    Rectangle{
      shape.x + offset, 
      shape.y + offset, 
      shape.width - offset*2.f, 
      shape.height - offset*2.f
    }, 
    0.5f, 4, 2.f, BLACK
  );
}

void Game::Menu::Transition(Screen next)
{
  state = State::TRANSITION_IN;
  next_screen = next;
}

void Game::Menu::TransitionIn(Screen next)
{
  menu.transition += GetFrameTime();
  if (menu.transition >= 1.f) {
    state = State::TRANSITION_OUT;
    current_screen = next;
    menu.transition = 2.f;
  }
}

void Game::Menu::TransitionOut()
{
  menu.transition -= GetFrameTime();
  if (menu.transition <= 0.f) {
    state = State::NEUTRAL;
    menu.transition = 0.f;
  }
}

void Game::Menu::DrawTransition()
{
  if (state == State::TRANSITION_IN) {
    DrawRectangle(0,0,Window::width, Window::height, Color{0,0,0, static_cast<unsigned char>(Game::Lerp(0,255, menu.transition))});
  } else {
    DrawRectangle(0,0,Window::width, Window::height, Color{0,0,0, static_cast<unsigned char>(Game::Lerp(0,255, menu.transition * 0.5f))});
  }
}

void Game::Menu::CycleMenu(std::vector<Selection>& options)
{
  // add neutral selection
  options.push_back(Selection::NEUTRAL);

  // cycle through selection options
  if (IsKeyPressed(KB_UP)) {
    if (--menu.select_index < 0) {
      menu.select_index = options.size() - 2;
    }
  } else if (IsKeyPressed(KB_DOWN)) {
    if (++menu.select_index >= options.size() - 1) {
      menu.select_index = 0;
    }
  }

  // back out
  if (IsKeyPressed(KB_BACK)) {
    if (select == Selection::NEUTRAL) {
      switch (current_screen) 
      {
        case Screen::MAIN:
          Transition(Screen::TITLE);
          break;
        case Screen::PLAY: [[fallthrough]];
        case Screen::SETTINGS: [[fallthrough]];
        case Screen::HELP:
          Transition(Screen::MAIN);
        default:
          break;
      }
    } else {
      menu.select_index = options.size() - 1;
    }
  }

  // set "hovered" selection
  select = options[menu.select_index];
}

bool Game::Menu::CheckSelectInput()
{
  if (IsGamepadAvailable(0)) {
    if (IsGamepadButtonPressed(0, GP_SELECT) || IsGamepadButtonPressed(0, GP_SELECT_ALT)) {
      return true;
    }
  }
  if (IsKeyPressed(KB_SELECT) || IsKeyPressed(KB_SELECT_ALT)) {
    return true;
  }
  return false;
}

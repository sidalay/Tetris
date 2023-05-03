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
  if (state != State::PAUSE && state != State::COUNTDOWN && !menu.standby) {
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
    case Screen::GAME:
      TickGame();
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
  case Screen::GAME:
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
    case State::QUIT:
      TickQuit();
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
    case State::QUIT:
      DrawQuit();
      break;
    case State::TRANSITION_IN: [[fallthrough]];
    case State::TRANSITION_OUT:
      DrawTransition();
      break;
  }
}

void Game::Menu::TickTitle()
{
  if (CheckInputSelect()) {
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
  std::vector<Selection> select_options{Selection::START, Selection::SETTINGS, Selection::HELP, Selection::QUIT};
  CycleMenu(select_options);
}

void Game::Menu::DrawMain()
{
  DrawText("MAIN SCREEN", Window::width/2 - 3*24, Window::height/2 - 100, 20, GREEN);
  Rectangle button_left{Window::width*0.5f - ((Window::width * 0.02f) + Window::width * 0.1f), Window::height*0.5f, Window::width * 0.1f, Window::height * 0.05f};
  Rectangle button_right{Window::width*0.5f + Window::width * 0.02f, Window::height*0.5f, Window::width * 0.1f, Window::height * 0.05f};
  Button(Selection::START, button_left, 0);
  Button(Selection::SETTINGS, button_left, 1);
  Button(Selection::HELP, button_right, 0);
  Button(Selection::QUIT, button_right, 1);
}

void Game::Menu::TickPlay()
{
  std::vector<Selection> select_options{Selection::MARATHON, Selection::ULTRA, Selection::ENDLESS, Selection::FORTY, Selection::VERSUS};
  CycleMenu(select_options);
}

void Game::Menu::DrawPlay()
{
  DrawText("PLAY SCREEN", Window::width/2 - 3*24, Window::height/2 - 100, 20, GREEN);
  Rectangle button_rec{Window::width*0.5f - ((Window::width*0.1f)*0.5f), Window::height*0.5f, Window::width * 0.1f, Window::height * 0.05f};
  Button(Selection::MARATHON, button_rec, 0);
  Button(Selection::ULTRA, button_rec, 1);
  Button(Selection::ENDLESS, button_rec, 2);
  Button(Selection::FORTY, button_rec, 3);
  Button(Selection::VERSUS, button_rec, 4);
}

void Game::Menu::TickGame()
{
  
  play.Run();
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

void Game::Menu::TickQuit()
{
  std::vector<Selection> select_options{Selection::CONFIRM_QUIT, Selection::CANCEL};
  CycleMenu(select_options);
}

void Game::Menu::DrawQuit()
{
  DrawRectangle(Window::width * 0.2f, Window::height * 0.2, Window::width * 0.6f, Window::height * 0.6f, Color{10,20,10,255});
  DrawText("QUIT SCREEN", Window::width/2 - 3*24, Window::height/2 - 100, 20, GREEN);
  Rectangle button_rec{Window::width*0.5f - ((Window::width*0.1f)*0.5f), Window::height*0.5f, Window::width * 0.1f, Window::height * 0.05f};
  Button(Selection::CONFIRM_QUIT, button_rec, 0);
  Button(Selection::CANCEL, button_rec, 1);
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
  if (CheckInputSelect()) {
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
      case Selection::QUIT:
        state = State::QUIT;
        menu.standby = true;
        break;
      case Selection::CONFIRM_QUIT:
        menu.exit = true;
        break;
      case Selection::CANCEL:
        state = State::NEUTRAL;
        menu.standby = false;
        break;
      case Selection::MARATHON:
        play.SetMode(Play::Mode::MARATHON);
        Transition(Screen::GAME);
        break;
      case Selection::ULTRA:
        play.SetMode(Play::Mode::ULTRA);
        Transition(Screen::GAME);
        break;
      case Selection::FORTY:
        play.SetMode(Play::Mode::FORTY);
        Transition(Screen::GAME);
        break;
      case Selection::VERSUS:
        play.SetMode(Play::Mode::VERSUS);
        Transition(Screen::GAME);
        break;
      case Selection::ENDLESS:
        play.SetMode(Play::Mode::ENDLESS);
        Transition(Screen::GAME);
        break;
      case Selection::NEUTRAL:
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

  Vector2 pos{shape.x + 10.f, shape.y + 10.f};
  Color text_color{BLACK};
  int font_size{20};
  switch (button_type)
  {
    case Selection::START:
      DrawText("START", pos.x, pos.y, font_size, text_color);
      break;
    case Selection::PAUSE:
      DrawText("PAUSE", pos.x, pos.y, font_size, text_color);
      break;
    case Selection::SETTINGS:
      DrawText("SETTINGS", pos.x, pos.y, font_size, text_color);
      break;
    case Selection::BACK:
      DrawText("BACK", pos.x, pos.y, font_size, text_color);
      break;
    case Selection::HELP:
      DrawText("HELP", pos.x, pos.y, font_size, text_color);
      break;
    case Selection::QUIT:
      DrawText("QUIT", pos.x, pos.y, font_size, text_color);
      break;
    case Selection::CONFIRM_QUIT:
      DrawText("CONFIRM", pos.x, pos.y, font_size, text_color);
      break;
    case Selection::CANCEL:
      DrawText("CANCEL", pos.x, pos.y, font_size, text_color);
      break;
    case Selection::MARATHON:
      DrawText("MARATHON", pos.x, pos.y, font_size, text_color);
      break;
    case Selection::ULTRA:
      DrawText("ULTRA", pos.x, pos.y, font_size, text_color);
      break;
    case Selection::FORTY:
      DrawText("FORTY", pos.x, pos.y, font_size, text_color);
      break;
    case Selection::VERSUS:
      DrawText("VERSUS", pos.x, pos.y, font_size, text_color);
      break;
    case Selection::ENDLESS:
      DrawText("ENDLESS", pos.x, pos.y, font_size, text_color);
      break;
    case Selection::NEUTRAL:
      break;
  }
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
  } else if (state == State::TRANSITION_OUT) {
    DrawRectangle(0,0,Window::width, Window::height, Color{0,0,0, static_cast<unsigned char>(Game::Lerp(0,255, menu.transition * 0.5f))});
  }
}

void Game::Menu::CycleMenu(std::vector<Selection>& options)
{
  // add neutral selection
  options.push_back(Selection::NEUTRAL);

  // cycle through selection options
  if (CheckInputCycle(Menu::Movement::UP)) {
    if (--menu.select_index < 0) {
      menu.select_index = options.size() - 2;
    }
  } else if (CheckInputCycle(Menu::Movement::DOWN)) {
    if (++menu.select_index >= options.size() - 1) {
      menu.select_index = 0;
    }
  } else if (CheckInputCycle(Menu::Movement::LEFT)) {
    if (menu.select_index - 2 < 0) {
      menu.select_index = (options.size() - 1) + (menu.select_index - 2);
    } else {
      menu.select_index -= 2;
    }
  } else if (CheckInputCycle(Menu::Movement::RIGHT)) {
    if (menu.select_index + 2 >= options.size() - 1) {
      menu.select_index = 0;
    } else {
      menu.select_index += 2;
    }
  }

  // back out
  if (CheckInputBack()) {
    if (select == Selection::NEUTRAL && !menu.standby) {
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
    // check for back on pop up menus
    if (state != State::NEUTRAL && menu.standby) {
      state = State::NEUTRAL;
      menu.standby = false;
      menu.select_index = 0;
    }
  }

  // set "hovered" selection
  select = options[menu.select_index];
}

bool Game::Menu::CheckInputSelect()
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

bool Game::Menu::CheckInputBack()
{
  if (IsGamepadAvailable(0)) {
    if (IsGamepadButtonPressed(0, GP_BACK)) {
      return true;
    }
  }
  if (IsKeyPressed(KB_BACK) || IsKeyPressed(KB_BACK_ALT)) {
    return true;
  }
  return false;
}

bool Game::Menu::CheckInputCycle(Menu::Movement direction)
{
  if (direction == Menu::Movement::UP) {
    if (IsGamepadAvailable(0)) {
      if (IsGamepadButtonPressed(0, GP_UP)) {
        return true;
      }
    }
    if (IsKeyPressed(KB_UP)) {
      return true;
    }
  } else if (direction == Menu::Movement::DOWN) {
    if (IsGamepadAvailable(0)) {
      if (IsGamepadButtonPressed(0, GP_DOWN)) {
        return true;
      }
    }
    if (IsKeyPressed(KB_DOWN)) {
      return true;
    }
  } else if (direction == Menu::Movement::LEFT) {
    if (IsGamepadAvailable(0)) {
      if (IsGamepadButtonPressed(0, GP_LEFT)) {
        return true;
      }
    }
    if (IsKeyPressed(KB_LEFT)) {
      return true;
    }
  } else if (direction == Menu::Movement::RIGHT) {
    if (IsGamepadAvailable(0)) {
      if (IsGamepadButtonPressed(0, GP_RIGHT)) {
        return true;
      }
    }
    if (IsKeyPressed(KB_RIGHT)) {
      return true;
    }
  }
  return false;
}

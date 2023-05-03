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
    case State::TRANSITION_IN:
      [[fallthrough]];
    case State::TRANSITION_OUT:
      DrawTransition();
      break;
  }
}

void Game::Menu::TickTitle()
{
  if (IsKeyPressed(KB_SELECT) || IsKeyPressed(KB_SELECT_ALT)) {
    state = State::TRANSITION_IN;
    next_screen = Screen::MAIN;
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
  // if (IsKeyPressed(KEY_ENTER)) {
  //   state = State::TRANSITION_IN;
  //   next_screen = Screen::TITLE;
  // }
  Rectangle button_rec{Window::width*0.5f - ((Window::width*0.1f)*0.5f), Window::height*0.5f, Window::width * 0.1f, Window::height * 0.05f};
  Button(Selection::START, button_rec, 0);
  Button(Selection::SETTINGS, button_rec, 1);
}

void Game::Menu::DrawMain()
{
  DrawText("MAIN SCREEN", Window::width/2 - 3*24, Window::height/2 - 100, 20, GREEN);
  DrawText("Press Enter", Window::width/2 - 3*22, Window::height/2, 20, GREEN);
}

void Game::Menu::TickPlay()
{
}

void Game::Menu::DrawPlay()
{
}

void Game::Menu::TickSettings()
{
}

void Game::Menu::DrawSettings()
{
}

void Game::Menu::TickGameover()
{
}

void Game::Menu::DrawGameover()
{
}

void Game::Menu::TickHelp()
{
}

void Game::Menu::DrawHelp()
{
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
  countdown -= GetFrameTime();
  if (countdown <= 0.f) {
    countdown = 3.f;
    state = State::NEUTRAL;
    current_screen = Screen::TITLE;
  }
}

void Game::Menu::DrawCountdown()
{
  DrawRectangle(0, 0, Window::width, Window::height, Color{0,0,0,240});
  if (countdown > 2.f) {
    DrawText("3", Window::width/2 - 20, Window::height/2, 40, GREEN);
  } else if (countdown > 1.f) {
    DrawText("2", Window::width/2 - 20, Window::height/2, 40, GREEN);
  } else {
    DrawText("1", Window::width/2 - 20, Window::height/2, 40, GREEN);
  }
}

void Game::Menu::Button(Selection button_type, Rectangle shape, int id)
{
  // highlight button if selected
  Color highlight{0,70,255,100};
  if (select != button_type) {
    highlight = {0,255,255,0};
  }

  // set height offset based on button id
  shape.y += (shape.height * 2.f) * id;

  // draw buttons
  switch (select)
  {
    case Selection::START:
      DrawButton(shape, highlight);
      break;
    case Selection::PAUSE:
      break;
    case Selection::SETTINGS:
      DrawButton(shape, highlight);
      break;
    case Selection::BACK:
      DrawButton(shape, highlight);
      break;
    case Selection::HELP:
      DrawButton(shape, highlight);
      break;
    case Selection::MARATHON:
      DrawButton(shape, highlight);
      break;
    case Selection::ULTRA:
      DrawButton(shape, highlight);
      break;
    case Selection::FORTY:
      DrawButton(shape, highlight);
      break;
    case Selection::VERSUS:
      DrawButton(shape, highlight);
      break;
    default:
      break;
  }
}

void Game::Menu::DrawButton(Rectangle shape, Color highlight)
{
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

void Game::Menu::TransitionIn(Screen next)
{
  transition += GetFrameTime();
  if (transition >= 1.f) {
    state = State::TRANSITION_OUT;
    current_screen = next;
    transition = 2.f;
  }
}

void Game::Menu::TransitionOut()
{
  transition -= GetFrameTime();
  if (transition <= 0.f) {
    state = State::NEUTRAL;
    transition = 0.f;
  }
}

void Game::Menu::DrawTransition()
{
  if (state == State::TRANSITION_IN) {
    DrawRectangle(0,0,Window::width, Window::height, Color{0,0,0, static_cast<unsigned char>(Game::Lerp(0,255, transition))});
  } else {
    DrawRectangle(0,0,Window::width, Window::height, Color{0,0,0, static_cast<unsigned char>(Game::Lerp(0,255, transition * 0.5f))});
  }
}

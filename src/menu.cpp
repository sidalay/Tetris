#include "menu.hpp"

void Game::Menu::Tick()
{
  switch (screen)
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
  case Screen::PAUSE:
    TickPause();
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

void Game::Menu::Draw()
{
  switch (screen)
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
  case Screen::PAUSE:
    DrawPause();
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

void Game::Menu::TickTitle()
{
}

void Game::Menu::DrawTitle()
{
}

void Game::Menu::TickMain()
{
}

void Game::Menu::DrawMain()
{
}

void Game::Menu::TickPlay()
{
}

void Game::Menu::DrawPlay()
{
}

void Game::Menu::TickPause()
{
}

void Game::Menu::DrawPause()
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

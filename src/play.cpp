#include "play.hpp"

void Game::Play::Run()
{
  Tick();
  Draw();
}

void Game::Play::Tick()
{
  switch (mode)
  {
    case Play::Mode::NEUTRAL:
      return;
    case Play::Mode::MARATHON: {
      TickMarathon();
      break;
    }
    case Play::Mode::ULTRA:
      TickUltra();
      break;
    case Play::Mode::ENDLESS:
      TickEndless();
      controller.Tick();
      break;
    case Play::Mode::FORTY:
      TickForty();
      break;
    case Play::Mode::VERSUS:
      TickVersus();
      break;
  }
}

void Game::Play::Draw()
{
  switch (mode)
  {
    case Play::Mode::NEUTRAL:
      return;
    case Play::Mode::MARATHON: {
      DrawMarathon();
      break;
    }
    case Play::Mode::ULTRA:
      DrawMarathon();
      break;
    case Play::Mode::ENDLESS:
      DrawEndless();
      break;
    case Play::Mode::FORTY:
      DrawForty();
      break;
    case Play::Mode::VERSUS:
      DrawVersus();
      break;
  }
}

void Game::Play::TickMarathon()
{
}

void Game::Play::DrawMarathon()
{
}

void Game::Play::TickUltra()
{
}

void Game::Play::DrawUltra()
{
}

void Game::Play::TickForty()
{
}

void Game::Play::DrawForty()
{
}

void Game::Play::TickEndless()
{
  playfield.Tick();
}

void Game::Play::DrawEndless()
{
  playfield.Draw();
}

void Game::Play::TickVersus()
{
}

void Game::Play::DrawVersus()
{
}

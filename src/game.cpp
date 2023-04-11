#include "game.hpp"

void Game::Run()
{
  Properties game{};
  Game::Initialize(game);

  if (IsWindowReady()) {
    while (!WindowShouldClose()) {
      Game::Tick(game);
    }
  }

  CloseWindow();
}

void Game::Initialize(Properties& game)
{
  SetTraceLogLevel(LOG_WARNING);
  SetTargetFPS(game.fps);
  InitWindow(game.window.width, game.window.height, game.window.title.c_str());
}

void Game::Tick(Properties& game)
{
  game.deltatime += GetFrameTime();

  if (game.deltatime >= game.updatetime) {
    game.window.Tick();
    game.deltatime = 0.f;
  }

  BeginDrawing();
  ClearBackground(BLACK);
  EndDrawing();
}
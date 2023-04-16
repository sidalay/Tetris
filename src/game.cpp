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
  InitWindow(Window::width, Window::height, Window::title.c_str());
  SetWindowState(FLAG_WINDOW_RESIZABLE);
  SetWindowMinSize(800, 600);
}

void Game::Tick(Properties& game)
{
  game.deltatime += GetFrameTime();


  if (game.deltatime >= game.updatetime) {
    Window::Tick();
    game.matrix.Tick();
    game.deltatime = 0.f;
  }

  // test
  game.tetro_deltatime += GetFrameTime();
  if (game.tetro_deltatime >= game.tetro_updatetime)
  {
    game.test.Tick();
    game.tetro_deltatime = 0.f;
  }

  BeginDrawing();
  ClearBackground(BLACK);

  game.matrix.Draw();
  // test
  game.test.Draw();
  
  EndDrawing();
}
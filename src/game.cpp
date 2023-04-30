#include "game.hpp"

#include "window.hpp"
#include "enforcer.hpp"

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
  HideCursor();
}

void Game::Tick(Properties& game)
{
  game.deltatime += GetFrameTime();

  if (game.deltatime >= game.updatetime) {
    Window::Tick();
    game.matrix.Tick();
    //  ------------------------------------- test
    game.controller.Tick();
    //  ------------------------------------- test
    game.deltatime = 0.f;
  }

  BeginDrawing();
  ClearBackground(BLACK);

  game.matrix.Draw();

  EndDrawing();
}
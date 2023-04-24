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
}

void Game::Tick(Properties& game)
{
  game.deltatime += GetFrameTime();


  if (game.deltatime >= game.updatetime) {
    Window::Tick();
    game.matrix.Tick();
    //  ------------------------------------- test
    // game.tetro_current.Tick();
    // game.bag.Tick();
    game.controller.Tick();
    //  ------------------------------------- test
    game.deltatime = 0.f;
  }

  //  ------------------------------------- test
  // game.tetro_deltatime += GetFrameTime();
  // if (game.tetro_deltatime >= game.tetro_updatetime) {
  //   if (Enforcer::MovementIsSafe(game.tetro_current, game.matrix, Tetro::Movement::DOWN)) {
  //     game.tetro_current.Fall();
  //   }
  //   game.tetro_deltatime = 0.f;
  // }

  // if (IsKeyPressed(KEY_P)) {
  //   game.tetro_current = game.bag.Pull();
  // }
  //  ------------------------------------- test

  BeginDrawing();
  ClearBackground(BLACK);

  game.matrix.Draw();

  //  ------------------------------------- test
  // game.tetro_current.Draw();
  //  ------------------------------------- test
  
  EndDrawing();
}
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
    game.tetro_test.Tick();
    game.deltatime = 0.f;
  }

  // test
  game.tetro_deltatime += GetFrameTime();
  if (game.tetro_deltatime >= game.tetro_updatetime) {
    if (Enforcer::IsBelowClear(game.tetro_test, game.matrix)) {
      game.tetro_test.Fall();
    }
    game.tetro_deltatime = 0.f;
  }

  if (IsKeyPressed(KEY_D) || IsKeyPressed(KEY_UP)) {
    game.tetro_test.RotateCW();
  } else if (IsKeyPressed(KEY_A)) {
    game.tetro_test.RotateCCW();
  }

  if (IsKeyPressed(KEY_LEFT)) {
    if (!Enforcer::IsOutOfBounds(game.tetro_test, game.matrix, Tetro::Orientation::LEFT)) {
      game.tetro_test.Move(Tetro::Orientation::LEFT);
    }
  } else if (IsKeyPressed(KEY_RIGHT)) {
    if (!Enforcer::IsOutOfBounds(game.tetro_test, game.matrix, Tetro::Orientation::RIGHT)) {
      game.tetro_test.Move(Tetro::Orientation::RIGHT);
    }
  } else if (IsKeyPressed(KEY_DOWN)) {
    if (Enforcer::IsBelowClear(game.tetro_test, game.matrix)) {
      game.tetro_test.Move(Tetro::Orientation::DOWN);
    }
  }

  BeginDrawing();
  ClearBackground(BLACK);

  game.matrix.Draw();


  // test
  game.tetro_test.Draw();
  
  EndDrawing();
}
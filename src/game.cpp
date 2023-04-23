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
    game.tetro_test.Tick();
    //  ------------------------------------- test
    game.deltatime = 0.f;
  }

  //  ------------------------------------- test
  game.tetro_deltatime += GetFrameTime();
  if (game.tetro_deltatime >= game.tetro_updatetime) {
    if (Enforcer::MovementIsSafe(game.tetro_test, game.matrix, Tetro::Movement::DOWN)) {
      game.tetro_test.Fall();
    }
    game.tetro_deltatime = 0.f;
  }

  if (IsKeyPressed(KEY_D) || IsKeyPressed(KEY_UP)) {
    if (Enforcer::RotationIsSafe(game.tetro_test, game.matrix, Tetro::Rotation::CW)) {
      game.tetro_test.Rotate(Tetro::Rotation::CW);
    } else {
      // WallkickCW goes here
      game.tetro_test.WallKick(Enforcer::WallKickEval(game.tetro_test, game.matrix, Tetro::Rotation::CW), Tetro::Rotation::CW);
    }
  } else if (IsKeyPressed(KEY_A)) {
    if (Enforcer::RotationIsSafe(game.tetro_test, game.matrix, Tetro::Rotation::CCW)) {
      game.tetro_test.Rotate(Tetro::Rotation::CCW);
    } else {
      // WallkickCCW goes here
      game.tetro_test.WallKick(Enforcer::WallKickEval(game.tetro_test, game.matrix, Tetro::Rotation::CCW), Tetro::Rotation::CCW);
    }
  }

  if (IsKeyPressed(KEY_LEFT)) {
    if (Enforcer::MovementIsSafe(game.tetro_test, game.matrix, Tetro::Movement::LEFT)) {
      game.tetro_test.Move(Tetro::Movement::LEFT);
    }
  } else if (IsKeyPressed(KEY_RIGHT)) {
    if (Enforcer::MovementIsSafe(game.tetro_test, game.matrix, Tetro::Movement::RIGHT)) {
      game.tetro_test.Move(Tetro::Movement::RIGHT);
    }
  } else if (IsKeyPressed(KEY_DOWN)) {
    if (Enforcer::MovementIsSafe(game.tetro_test, game.matrix, Tetro::Movement::DOWN)) {
      game.tetro_test.Move(Tetro::Movement::DOWN);
    }
  }
  //  ------------------------------------- test

  BeginDrawing();
  ClearBackground(BLACK);

  game.matrix.Draw();

  //  ------------------------------------- test
  game.tetro_test.Draw();
  //  ------------------------------------- test
  
  EndDrawing();
}
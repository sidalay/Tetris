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
    game.test.Tick();
    game.deltatime = 0.f;
  }

  // test
  if (IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_UP)) {
    game.test.Rotate();
  }
  if (IsKeyPressed(KEY_LEFT)) {
    game.test.Move(Tetro::Orientation::LEFT);
  } else if (IsKeyPressed(KEY_RIGHT)) {
    game.test.Move(Tetro::Orientation::RIGHT);
  } else if (IsKeyPressed(KEY_DOWN)) {
    game.test.Move(Tetro::Orientation::DOWN);
  }

  BeginDrawing();
  ClearBackground(BLACK);

  game.matrix.Draw();
  // test
  game.test.Draw();
  
  EndDrawing();
}
#include "handler.hpp"

#include "enforcer.hpp"

Handler::Handler(Tetromino& fromMatrix, std::map<std::pair<int,int>,bool>& map)
  : tetromino{fromMatrix}, matrix{map}
{
  
}

void Handler::Tick()
{
  Gravity();
}

bool Handler::UpdateLock()
{
  DrawText(TextFormat("lock time: %f", lock.time), 20, 20, 20, RAYWHITE);
  if (!IsWindowResized()) {
    if (!Enforcer::MovementIsSafe(tetromino, matrix, Tetro::Movement::DOWN)) {
      lock.time += GetFrameTime();
      if (lock.time >= lock.delay) {
        lock.active = true;
      }
    } else {
      ResetLock();
    }
  }
  return CheckLock();
}

bool Handler::CheckLock()
{
  if (lock.active) {
    ResetLock();
    return true;
  }
  return false;
}

void Handler::ResetLock()
{
  lock.time = 0.f;
  lock.active = false;
}

void Handler::Gravity()
{
  if (!IsKeyDown(KEY_DOWN)) {
    gravitytime += GetFrameTime();
    if (gravitytime >= 1.f) {
      if (Enforcer::MovementIsSafe(tetromino, matrix, Tetro::Movement::DOWN)) {
        tetromino.Fall();
        ResetLock();
      }
      gravitytime = 0.f;
    }
  }
}
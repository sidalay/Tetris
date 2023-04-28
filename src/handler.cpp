#include "handler.hpp"

#include "enforcer.hpp"

bool operator==(const Color& lhs, const Color& rhs) 
{
  bool r{lhs.r == rhs.r};
  bool g{lhs.g == rhs.g};
  bool b{lhs.b == rhs.b};
  bool a{lhs.a == rhs.a};

  if (r && g && b && a) {
    return true;
  }
  return false;
} 

Handler::Handler(
  Tetromino& matrixTetro,
  Bag& matrixBag,  
  std::map<std::pair<int,int>,bool>& map)
  : tetromino{matrixTetro},
    bag{matrixBag},  
    matrix{map}
{
  
}

void Handler::Tick()
{
  hold.Tick();
  Gravity();
  ScaleHold();
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

bool Handler::UpdateLock()
{
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
    lock.hold = false;
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

void Handler::Hold()
{
  if (lock.hold) {
    return;
  }

  if (hold.GetColor() == Color{0, 0, 0, 0}) {
    hold = tetromino;
    tetromino = bag.Pull();
  } else {
    Tetromino temp{hold};
    hold = tetromino;
    tetromino = Tetromino{temp.GetType()};
  }
  hold.SetHoldState({area.x, area.y});
  lock.hold = true;
}

void Handler::DrawHold()
{
  if (hold.GetColor() == Color{0,0,0,0}) {
    return;
  }
  if (lock.hold) {
    hold.Draw(GRAY);
  } else {
    hold.Draw();
  }
}

void Handler::ScaleHold()
{
  if (IsWindowResized()) {
    hold.SetHoldState({area.x, area.y});
  }
}
#include "handler.hpp"

#include "controller.hpp"
#include "enforcer.hpp"
#include "window.hpp"

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
  ApplyGravity();
  ScaleHold();
}

void Handler::CheckScaling(Rectangle matrixArea)
{
  area = matrixArea;
  hold.CheckScaling();
  ScaleHold();
}

void Handler::ApplyGravity()
{
  if (IsKeyUp(KB_SOFT_DROP)) {
    deltatime += GetFrameTime();
    if (deltatime >= multiplier[level]) {
      if (Enforcer::MovementIsSafe(tetromino, matrix, Tetro::Movement::DOWN)) {
        tetromino.Fall();
        ResetLock();
      }
      deltatime = 0.f;
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
  hold.SetHoldState({area.x, area.y});
}

void Handler::DrawGhost()
{
  if (!IsWindowResized()) {
    float offset{};
    auto  tetro{tetromino.GetBlocks()};
    float cell_size{Window::height * Window::cell_size_percentage};
    Tetromino temp{tetromino};

    while (Enforcer::MovementIsSafe(temp, matrix, Tetro::Movement::DOWN)) {
      temp.Move(Tetro::Movement::DOWN);
      ++offset;
    }
    for (const auto block : tetro) {
      float thickness{1.f};
      Rectangle outline{
        block.area.x + thickness, 
        block.area.y + (cell_size * offset) + thickness, 
        block.area.width - thickness * 2.f, 
        block.area.height - thickness * 2.f};
      DrawRectangleLinesEx(outline, thickness, Color{ 245, 245, 245, 200 });
    }
  }
}

void Handler::Reset()
{
  hold = Tetromino{};
  lock.hold = false;
  level = 0;
}
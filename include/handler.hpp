#ifndef HANDLER_HPP
#define HANDLER_HPP

#include "bag.hpp"
#include "tetromino.hpp"

#include <map>

class Handler
{
public:
  Handler(
    Tetromino&, 
    Bag&, 
    std::map<std::pair<int,int>,bool>&);

  void Tick();

  void Hold();
  void DrawHold();
  void DrawGhost();
  void ScaleHold();
  bool UpdateLock();
  void UpdateArea(Rectangle matrixArea) {area = matrixArea;}
  void SetLocked(bool active) {lock.active = active;}
  [[nodiscard]] bool IsLocked() const {return lock.active;}
  [[nodiscard]] bool IsHeld() const {return lock.hold;}
private:
  float            gravitytime{};
  Tetro::Lock      lock{};
  Tetromino        hold{};
  Tetromino&       tetromino;
  Bag&             bag;
  Rectangle        area{};
  const std::map<std::pair<int,int>,bool>& matrix;

  void Gravity();
  bool CheckLock();
  void ResetLock();
};

bool operator==(const Color& lhs, const Color& rhs);

#endif // HANDLER_HPP
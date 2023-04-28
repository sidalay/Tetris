#ifndef HANDLER_HPP
#define HANDLER_HPP

#include "bag.hpp"
#include "tetromino.hpp"

#include <map>

// handles locking, holding, and ghost state for the Tetromino inside of the matrix/playfield

// Gravity multiplier per level
struct Gravity
{
  std::array<float,20> levels
  {
    1.00000f, 0.79300f, 0.61780f, 0.47273f,
    0.35520f, 0.26200f, 0.18968f, 0.13473f,
    0.09388f, 0.06415f, 0.04298f, 0.02822f,
    0.01815f, 0.01144f, 0.00706f, 0.00426f,
    0.00252f, 0.00146f, 0.00082f, 0.00046f
  };

  float operator[](const int i) {return levels[i];}
};

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
  void LevelUp() {++level;}
  void Reset() {level = 0;}
  [[nodiscard]] bool IsLocked() const {return lock.active;}
  [[nodiscard]] bool IsHeld() const {return lock.hold;}
private:
  int              level{};
  float            deltatime{};
  Gravity          multiplier{};
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
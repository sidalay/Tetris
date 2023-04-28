#ifndef HANDLER_HPP
#define HANDLER_HPP

#include "tetromino.hpp"

#include <map>

struct Handler
{
public:
  Handler(Tetromino&, std::map<std::pair<int,int>,bool>&);

  void Tick();
  bool UpdateLock();
  void SetLocked(bool active) {lock.active = active;}
private:
  float            gravitytime{};
  Tetro::Lock      lock{};
  Tetromino        hold{};
  Tetromino&       tetromino;
  const std::map<std::pair<int,int>,bool>& matrix;

  void Gravity();
  bool CheckLock();
  void ResetLock();
};

#endif // HANDLER_HPP
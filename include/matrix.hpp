#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "tetromino.hpp"

#include <vector>

struct Cell
{
  Rectangle area{};
  Color     color{};
  bool      occupied{};
};

struct Frame
{
  Rectangle area{};
  Vector2   grid{};
  std::vector<std::vector<Cell>> matrix{};
  // Todo: Texture member
};

struct Playfield
{
public: 
  Playfield();

  void Tick();
  void Draw();
  Rectangle GetBorder() const {return frames.at(0).area;}

public:
  std::vector<Frame> frames{};

private:
  void DrawFrames();
  void DrawMatrices();
  void UpdateFrames();
  void UpdateMatrices();
  void InitializeFrames();
  void InitializeMatrices();
  void InitCells(Frame&, int, int);
};

#endif // MATRIX_HPP
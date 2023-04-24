#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "tetromino.hpp"
#include "bag.hpp"

#include <vector>
#include <map>

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

struct Lock
{
  float time{};
  float delay{0.5f};
  bool  active{};
};

struct Playfield
{
public: 
  Playfield();

  void Tick();
  void Draw();
  [[nodiscard]] Rectangle GetBorder() const {return frames.at(0).area;}
  [[nodiscard]] std::map<std::pair<int,int>,bool> GetMatrixMap() const {return matrix_map;}

private:
  std::vector<Frame>                frames{};
  std::vector<Tetro::Block>         blocks{};
  std::map<std::pair<int,int>,bool> matrix_map{};
  Bag                               bag{};
  Tetromino                         currentpiece{bag.Pull()};
  Lock                              lock{};

  void DrawFrames();
  void DrawMatrices();
  void UpdateFrames();
  void UpdateMatrices();
  void InitializeFrames();
  void InitializeMatrices();
  void InitCells(Frame&, int, int);
  void InitMap();
  void UpdateCells(Frame&, int, int);
};

#endif // MATRIX_HPP
#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "bag.hpp"

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
  [[nodiscard]] Tetromino& GetCurrentTetro() {return tetromino;}
  [[nodiscard]] Rectangle GetBorder() const {return frames.at(0).area;}
  [[nodiscard]] std::map<std::pair<int,int>,bool> GetMatrixMap() const {return matrix_map;}

private:
  std::vector<Frame>                frames{};
  std::vector<Tetro::Block>         blocks{};
  std::map<std::pair<int,int>,bool> matrix_map{};
  Bag                               bag{};
  Tetromino                         tetromino{bag.Pull()};
  // Tetromino                         hold;
  Lock                              lock{};
  float                             gravitytime{};

  void DrawFrames();
  void DrawMatrices();
  void UpdateFrames();
  void UpdateMatrices();
  void InitializeFrames();
  void InitializeMatrices();
  void InitCells(Frame&, int, int);
  void InitMap();
  void UpdateCells(Frame&, int, int);

  void Gravity();
  void DrawTetromino();
  void UpdateTetromino();
  void DrawBag();
  void UpdateBag();

  // --------------- test
  void BagPull();
};

#endif // MATRIX_HPP
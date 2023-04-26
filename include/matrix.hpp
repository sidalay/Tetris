#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "bag.hpp"

#include <map>

struct Cell
{
  Rectangle area{};
  Color     color{};
  Color     outline{};
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
  void Hold();
  void SetLocked(bool active) {lock.active = active;}
  [[nodiscard]] Tetromino& GetCurrentTetro() {return tetromino;}
  [[nodiscard]] Rectangle GetBorder() const {return frames.at(0).area;}
  [[nodiscard]] std::map<std::pair<int,int>,bool> GetMatrixMap() const {return matrix_map;}

private:
  std::vector<Frame>                        frames{};
  std::map<std::pair<int,int>,Tetro::Block> blocks{};
  std::map<std::pair<int,int>,bool>         matrix_map{};
  Tetro::Lock                               lock{};
  Bag                                       bag{};
  Tetromino                                 tetromino;
  Tetromino                                 hold{};
  float                                     gravitytime{};

  void DrawFrames();
  void DrawMatrices();
  void UpdateFrames();
  void UpdateMatrices();
  void InitializeFrames();
  void InitializeMatrices();
  void InitCells(Frame&, int, int);
  void InitMap();
  void UpdateCells(Frame&, int, int);
  void UpdateCellState();

  void Gravity();
  void DrawTetromino();
  void UpdateTetromino();
  void DrawHold();
  void UpdateHold();
  void BagPull();
  void DrawBag();
  void UpdateBag();
  void CheckLock();
  void DrawBlocks();
  void DrawGhost();
  void CaptureBlocks();
  void UpdateBlocks();
  void OccupyMatrix(const Tetro::Block&);
  void ResetLock();
  void UpdateLock();

  void CheckLine(int);
  void ClearLine(int);
  void DropLine(int);
};

#endif // MATRIX_HPP
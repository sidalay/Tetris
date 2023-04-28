#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "bag.hpp"
#include "handler.hpp"

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
  [[nodiscard]] Handler& GetHandler() {return handler;}
  [[nodiscard]] Tetromino& GetCurrentTetro() {return tetromino;}
  [[nodiscard]] Rectangle GetBorder() const {return frames.at(0).area;}
  [[nodiscard]] const std::map<std::pair<int,int>,bool>& GetMatrixMap() const {return matrix;}

private:
  std::vector<Frame>                        frames{};
  std::map<std::pair<int,int>,Tetro::Block> blocks{};
  std::map<std::pair<int,int>,bool>         matrix{};
  Bag                                       bag{};
  Tetro::Lock                               lock{};
  Tetromino                                 tetromino;
  Tetromino                                 hold{};
  Handler                                   handler{tetromino, matrix};
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

  void DrawBag();
  void DrawTetromino();
  void DrawHold();
  void UpdateHold();
  void BagPull();
  void UpdateBag();
  void UpdateTetromino();
  void DrawGhost();
  void DrawBlocks();
  void CaptureBlocks();
  void UpdateBlocks();
  void OccupyMatrix(const Tetro::Block&);

  void UpdateHandler();

  void CheckLine(int);
  void ClearLine(int);
  void DropLine(int);
};

#endif // MATRIX_HPP
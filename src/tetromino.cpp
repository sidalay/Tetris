#include "tetromino.hpp"

#include "window.hpp"

const Color Cyan      { 0, 255, 255, 255 };   // I
const Color Blue      { 0, 0, 255, 255 };     // J
const Color Orange    { 255, 165, 0, 255 };   // L
const Color Yellow    { 255, 255, 0, 255 };   // O
const Color Green     { 0, 255, 0, 255 };     // S
const Color Purple    { 128, 0, 128, 255 };   // T
const Color Red       { 255, 0, 0, 255 };     // Z
const Color Clear     { 0, 0, 0, 0 };         // Line Cleared

// gradients

// Cyan
const Color G_Primary_Cyan     { 0, 255, 255, 255 };
const Color G_Secondary_Cyan   { 0, 134, 253, 255 };

// Blue
const Color G_Primary_Blue     { 7, 200, 249, 255 };
const Color G_Secondary_Blue   { 9, 31, 241, 255 };

// Orange
const Color G_Primary_Orange   { 255, 215, 100, 255 };
const Color G_Secondary_Orange { 255, 78, 0, 255 };

// Yellow
const Color G_Primary_Yellow   { 255, 255, 150, 255 };
const Color G_Secondary_Yellow { 255, 195, 0, 255 };

// Green
const Color G_Primary_Green    { 106, 199, 167, 255 };
const Color G_Secondary_Green  { 3, 59, 42, 255 };

// Purple
const Color G_Primary_Purple   { 248, 114, 233, 255 };
const Color G_Secondary_Purple { 61, 5, 221, 255 };

// Red
const Color G_Primary_Red      { 248, 155, 41, 255 };
const Color G_Secondary_Red    { 255, 15, 85, 255 };

// Gray
const Color G_Primary_Gray      { 255, 255, 255, 225 };
const Color G_Secondary_Gray    { 62, 62, 62, 225 };


Tetromino::Tetromino(Tetro::Shape shape)
  : type{shape}
{
  InitBlocks();
}

void Tetromino::Tick()
{
  UpdateFollowerPos();
  UpdateRowCol();
}

void Tetromino::CheckScaling()
{
  if (IsWindowResized()) {
    UpdateBlockSize();
    UpdateOriginScale();
    UpdateFollowerPos();
  }
}

void Tetromino::Draw() const
{
  float offset{1.f};
  for (auto& block : blocks) {
    DrawRectangleGradientV(block.area.x, block.area.y, block.area.width, block.area.height, block.gradient.primary, block.gradient.secondary);
    Rectangle outline{block.area.x - offset, block.area.y - offset, block.area.width + offset, block.area.height + offset};
    DrawRectangleLinesEx(outline, 2.f, BLACK);
  }
}

void Tetromino::Draw(Vector2 pos)
{
  float cell_size{Window::height * Window::cell_size_percentage};
  // make copy of tetromino
  Tetromino tetro{*this};
  // set origin
  tetro.GetBlocks().at(0).area.x = pos.x;
  tetro.GetBlocks().at(0).area.y = pos.y + (cell_size * 0.5f);
  // set shape
  tetro.SetFollowers();

  float offset{1.f};
  for (auto block : tetro.GetBlocks()) {
    DrawRectangleGradientV(block.area.x, block.area.y, block.area.width, block.area.height, block.gradient.primary, block.gradient.secondary);
    Rectangle outline{block.area.x - offset, block.area.y - offset, block.area.width + offset, block.area.height + offset};
    DrawRectangleLinesEx(outline, 2.f, BLACK);
  }
}

void Tetromino::Draw(Color disabled) const
{
  float offset{1.f};
  for (auto& block : blocks) {
    DrawRectangleGradientV(block.area.x, block.area.y, block.area.width, block.area.height, block.gradient.primary, block.gradient.secondary);
    DrawRectangleGradientV(block.area.x, block.area.y, block.area.width, block.area.height, G_Primary_Gray, G_Secondary_Gray);
    Rectangle area{block.area.x - offset, block.area.y - offset, block.area.width + offset, block.area.height + offset};
    DrawRectangleLinesEx(area, 2.f, BLACK);
  }
}

void Tetromino::Move(Tetro::Movement direction)
{
  float cell_size{Window::height * Window::cell_size_percentage};
  switch (direction)
  {
    case Tetro::Movement::DOWN:
      blocks[0].area.y += cell_size;
      break;
    case Tetro::Movement::LEFT:
      blocks[0].area.x -= cell_size;
      break;
    case Tetro::Movement::RIGHT:
      blocks[0].area.x += cell_size;
      break;
    default:
      break;
  }
  UpdateFollowerPos();
  UpdateRowCol();
}

void Tetromino::WallKickMove(Tetro::Wallkick kick) 
{
  float cell_size{Window::height * Window::cell_size_percentage};
  blocks[0].area.x += cell_size * kick.col;
  blocks[0].area.y -= cell_size * kick.row;
}

void Tetromino::Rotate(const Tetro::Rotation rotation)
{
  if (rotation == Tetro::Rotation::CW) {
    switch (facing)
    {
      case Tetro::Orientation::UP:
        facing = Tetro::Orientation::RIGHT;
        break;
      case Tetro::Orientation::DOWN:
        facing = Tetro::Orientation::LEFT;
        break;
      case Tetro::Orientation::LEFT:
        facing = Tetro::Orientation::UP;
        break;
      case Tetro::Orientation::RIGHT:
        facing = Tetro::Orientation::DOWN;
        break;
    }
  } else {
    switch (facing)
    {
      case Tetro::Orientation::UP:
        facing = Tetro::Orientation::LEFT;
        break;
      case Tetro::Orientation::DOWN:
        facing = Tetro::Orientation::RIGHT;
        break;
      case Tetro::Orientation::LEFT:
        facing = Tetro::Orientation::DOWN;
        break;
      case Tetro::Orientation::RIGHT:
        facing = Tetro::Orientation::UP;
        break;
    }
  }
  UpdateOriginPos(rotation);
}

void Tetromino::WallKick(const Tetro::Wallkick kick, const Tetro::Rotation rotation)
{
  if (kick.col == 0 && kick.row == 0) {
    return;
  }
  Rotate(rotation);
  WallKickMove(kick);
}

void Tetromino::RotateWallKick(const Tetro::Rotation rotation)
{
  if (rotation == Tetro::Rotation::CW) {
    switch (facing)
    {
      case Tetro::Orientation::UP:
        facing = Tetro::Orientation::RIGHT;
        break;
      case Tetro::Orientation::DOWN:
        facing = Tetro::Orientation::LEFT;
        break;
      case Tetro::Orientation::LEFT:
        facing = Tetro::Orientation::UP;
        break;
      case Tetro::Orientation::RIGHT:
        facing = Tetro::Orientation::DOWN;
        break;
    }
  } else {
    switch (facing)
    {
      case Tetro::Orientation::UP:
        facing = Tetro::Orientation::LEFT;
        break;
      case Tetro::Orientation::DOWN:
        facing = Tetro::Orientation::RIGHT;
        break;
      case Tetro::Orientation::LEFT:
        facing = Tetro::Orientation::DOWN;
        break;
      case Tetro::Orientation::RIGHT:
        facing = Tetro::Orientation::UP;
        break;
    }
  }
  UpdateOriginPos(rotation);
  UpdateFollowerPos();
  UpdateRowCol();
}

void Tetromino::Fall()
{
  for (auto& block : blocks) {
    block.area.y += block.area.height;
  }
}

void Tetromino::InitBlocks()
{
  InitBlockSize();
  InitBlockColor();
  InitBlockOrigin();
  SetFollowers();
  UpdateRowCol();
}

void Tetromino::InitBlockSize()
{
  float cell_size{Window::height * Window::cell_size_percentage};
  for (auto& block : blocks) {
    block.area.width = cell_size;
    block.area.height = cell_size;
  }
}

void Tetromino::InitBlockColor()
{
  for (auto& block : blocks) {
    switch (type)
    {
      case Tetro::Shape::I:
        color = Cyan;
        block.color = Cyan;
        block.gradient.primary = G_Primary_Cyan;
        block.gradient.secondary = G_Secondary_Cyan;
        break;
      case Tetro::Shape::J:
        color = Blue;
        block.color = Blue;
        block.gradient.primary = G_Primary_Blue;
        block.gradient.secondary = G_Secondary_Blue;
        break;
      case Tetro::Shape::L:
        color = Orange;
        block.color = Orange;
        block.gradient.primary = G_Primary_Orange;
        block.gradient.secondary = G_Secondary_Orange;
        break;
      case Tetro::Shape::O:
        color = Yellow;
        block.color = Yellow;
        block.gradient.primary = G_Primary_Yellow;
        block.gradient.secondary = G_Secondary_Yellow;
        break;
      case Tetro::Shape::S:
        color = Green;
        block.color = Green;
        block.gradient.primary = G_Primary_Green;
        block.gradient.secondary = G_Secondary_Green;
        break;
      case Tetro::Shape::T:
        color = Purple;
        block.color = Purple;
        block.gradient.primary = G_Primary_Purple;
        block.gradient.secondary = G_Secondary_Purple;
        break;
      case Tetro::Shape::Z:
        color = Red;
        block.color = Red;
        block.gradient.primary = G_Primary_Red;
        block.gradient.secondary = G_Secondary_Red;
        break;
    }
  }
}

void Tetromino::InitBlockOrigin()
{
  Tetro::Block& origin{blocks.at(0)};
  float cell_size{Window::height * Window::cell_size_percentage};

  origin.area.x = Window::width/2 - cell_size; 
  origin.area.y = cell_size * 2.f;
  UpdateRowCol();
}

void Tetromino::SetShape(
  std::pair<int,int> one, 
  std::pair<int,int> two, 
  std::pair<int,int> three)
{
  for (int i{1}; i < blocks.size(); ++i) {
    if (i == 1) {
      blocks[i].area.x = blocks[0].area.x + (blocks[i].area.width * one.first);
      blocks[i].area.y = blocks[0].area.y + (blocks[i].area.height * one.second);
    } else if (i == 2) {
      blocks[i].area.x = blocks[0].area.x + (blocks[i].area.width * two.first);
      blocks[i].area.y = blocks[0].area.y + (blocks[i].area.height * two.second);
    } else {
      blocks[i].area.x = blocks[0].area.x + (blocks[i].area.width * three.first);
      blocks[i].area.y = blocks[0].area.y + (blocks[i].area.height * three.second);
    }
  }
}

void Tetromino::SetFollowers()
{
  switch (type)
  {
    case Tetro::Shape::I:
      SetShape(std::make_pair(-1,0), std::make_pair(1,0), std::make_pair(2,0));
      break;
    case Tetro::Shape::J:
      SetShape(std::make_pair(1,0), std::make_pair(-1,0), std::make_pair(-1,-1));
      break;
    case Tetro::Shape::L:
      SetShape(std::make_pair(-1,0), std::make_pair(1,0), std::make_pair(1,-1));
      break;
    case Tetro::Shape::O:
      SetShape(std::make_pair(0,-1), std::make_pair(1,-1), std::make_pair(1,0));
      break;
    case Tetro::Shape::S:
      SetShape(std::make_pair(-1,0), std::make_pair(0,-1), std::make_pair(1,-1));
      break;
    case Tetro::Shape::T:
      SetShape(std::make_pair(-1,0), std::make_pair(0,-1), std::make_pair(1,0));
      break;
    case Tetro::Shape::Z:
      SetShape(std::make_pair(1,0), std::make_pair(0,-1), std::make_pair(-1,-1));
      break;
  }
}

void Tetromino::SetHoldState(Vector2 holdframe)
{
  float cell_size{Window::height * Window::cell_size_percentage};
  
  if (type == Tetro::Shape::I) {
    blocks[0].area.x = holdframe.x + (cell_size * 1.5f);
    blocks[0].area.y = holdframe.y + (cell_size * 2.f);
  } else if (type == Tetro::Shape::O) {
    blocks[0].area.x = holdframe.x + (cell_size * 1.5f);
    blocks[0].area.y = holdframe.y + (cell_size * 2.5f);
  } else {
    blocks[0].area.x = holdframe.x + (cell_size * 2.f);
    blocks[0].area.y = holdframe.y + (cell_size * 2.5f);
  }
  facing = Tetro::Orientation::UP;
  UpdateFollowerPos();
}

void Tetromino::UpdateOriginPos(const Tetro::Rotation rotation)
{
  if (type != Tetro::Shape::I) {
    return;
  }

  float cell_size{Window::height * Window::cell_size_percentage};

  if (rotation == Tetro::Rotation::CW) {
    switch (facing)
    {
      case Tetro::Orientation::UP:
        blocks[0].area.y -= cell_size;
        break;
      case Tetro::Orientation::RIGHT:
        blocks[0].area.x += cell_size;
        break;
      case Tetro::Orientation::DOWN:
        blocks[0].area.y += cell_size;
        break;
      case Tetro::Orientation::LEFT:
        blocks[0].area.x -= cell_size;
        break;
    } 
  } else {
    switch (facing)
    {
      case Tetro::Orientation::UP:
        blocks[0].area.x -= cell_size;
        break;
      case Tetro::Orientation::RIGHT:
        blocks[0].area.y -= cell_size;
        break;
      case Tetro::Orientation::DOWN:
        blocks[0].area.x += cell_size;
        break;
      case Tetro::Orientation::LEFT:
        blocks[0].area.y += cell_size;
        break;
    }
  }
  UpdateRowCol();
}

void Tetromino::UpdateBlockSize()
{
  InitBlockSize();
}

void Tetromino::UpdateOriginScale()
{
  Tetro::Block& origin{blocks.at(0)};
  float cell_size{Window::height * Window::cell_size_percentage};
  float borderX{(Window::width - (Window::well_width * Window::height)) * .5f};

  origin.area.y = cell_size * origin.screen_row;
  origin.area.x = borderX + (cell_size * origin.screen_col); 
}

void Tetromino::UpdateRowCol()
{
  float cell_size{Window::height * Window::cell_size_percentage};
  float borderX{(Window::width - (Window::well_width * Window::height)) * .5f};

  for (auto& block : blocks) {
    block.screen_row = block.area.y / static_cast<int>(cell_size);
    block.screen_col = static_cast<int>(block.area.x - borderX) / static_cast<int>(cell_size); // DONT ADD 1 TO THIS!!!!!!!!!!!!!!!!!!!!!
  }
}

void Tetromino::UpdateFollowerPos()
{
  switch (facing)
  {
    case Tetro::Orientation::UP: {
      SetFollowers();
      break;
    }
    case Tetro::Orientation::RIGHT: {
      switch (type)
      {
        case Tetro::Shape::I:
          SetShape(std::make_pair(0,-1), std::make_pair(0,1), std::make_pair(0,2));
          break;
        case Tetro::Shape::J:
          SetShape(std::make_pair(0,1), std::make_pair(0,-1), std::make_pair(1,-1));
          break;
        case Tetro::Shape::L:
          SetShape(std::make_pair(0,-1), std::make_pair(0,1), std::make_pair(1,1));
          break;
        case Tetro::Shape::O:
          SetShape(std::make_pair(0,-1), std::make_pair(1,-1), std::make_pair(1,0));
          break;
        case Tetro::Shape::S:
          SetShape(std::make_pair(0,-1), std::make_pair(1,0), std::make_pair(1,1));
          break;
        case Tetro::Shape::T:
          SetShape(std::make_pair(0,-1), std::make_pair(1,0), std::make_pair(0,1));
          break;
        case Tetro::Shape::Z:
          SetShape(std::make_pair(0,1), std::make_pair(1,0), std::make_pair(1,-1));
          break;
      }
      break;
    }
    case Tetro::Orientation::DOWN: {
      switch (type)
      {
        case Tetro::Shape::I:
          SetShape(std::make_pair(1,0), std::make_pair(-1,0), std::make_pair(-2,0));
          break;
        case Tetro::Shape::J:
          SetShape(std::make_pair(-1,0), std::make_pair(1,0), std::make_pair(1,1));
          break;
        case Tetro::Shape::L:
          SetShape(std::make_pair(1,0), std::make_pair(-1,0), std::make_pair(-1,1));
          break;
        case Tetro::Shape::O:
          SetShape(std::make_pair(0,-1), std::make_pair(1,-1), std::make_pair(1,0));
          break;
        case Tetro::Shape::S:
          SetShape(std::make_pair(1,0), std::make_pair(0,1), std::make_pair(-1,1));
          break;
        case Tetro::Shape::T:
          SetShape(std::make_pair(1,0), std::make_pair(0,1), std::make_pair(-1,0));
          break;
        case Tetro::Shape::Z:
          SetShape(std::make_pair(-1,0), std::make_pair(0,1), std::make_pair(1,1));
          break;
      }
      break;
    }
    case Tetro::Orientation::LEFT: {
      switch (type)
      {
        case Tetro::Shape::I:
          SetShape(std::make_pair(0,1), std::make_pair(0,-1), std::make_pair(0,-2));
          break;
        case Tetro::Shape::J:
          SetShape(std::make_pair(0,-1), std::make_pair(0,1), std::make_pair(-1,1));
          break;
        case Tetro::Shape::L:
          SetShape(std::make_pair(0,1), std::make_pair(0,-1), std::make_pair(-1,-1));
          break;
        case Tetro::Shape::O:
          SetShape(std::make_pair(0,-1), std::make_pair(1,-1), std::make_pair(1,0));
          break;
        case Tetro::Shape::S:
          SetShape(std::make_pair(0,1), std::make_pair(-1,0), std::make_pair(-1,-1));
          break;
        case Tetro::Shape::T:
          SetShape(std::make_pair(0,1), std::make_pair(-1,0), std::make_pair(0,-1));
          break;
        case Tetro::Shape::Z:
          SetShape(std::make_pair(0,-1), std::make_pair(-1,0), std::make_pair(-1,1));
          break;
      }
      break;
    }
  }
}

/*
/   [1][0][2][3]
/
/   [3]
/   [2][0][1]
/
/         [3]
/   [1][0][2]
/
/   [1][2]
/   [0][3]
/
/      [2][3]
/   [1][0]
/
/      [2]
/   [1][0][3]
/
/   [3][2]
/      [0][1]
/
*/
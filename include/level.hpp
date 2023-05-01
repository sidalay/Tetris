#ifndef LEVEL_HPP
#define LEVEL_HPP

struct Lines
{
  int cleared{};
  int previous{};
};


struct Level
{
  int current{};
  Lines lines{};

  [[nodiscard]] constexpr int LinesCleared() const noexcept {return lines.cleared - lines.previous;}
};

#endif // LEVEL_HPP
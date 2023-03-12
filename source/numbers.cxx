#include "numbers.h"

std::vector<reed::Vector2>
reed::Rectangle::corners()
{
  return std::vector<Vector2>{ top_left,
                               Vector2{ bottom_right.X(), top_left.Y() },
                               bottom_right,
                               Vector2{ top_left.X(), bottom_right.Y() } };
}

reed::Millimeter operator""_mm(unsigned long long int value)
{
  return static_cast<reed::Millimeter>(value);
}

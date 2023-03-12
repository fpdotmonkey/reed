#ifndef __REED_NUMBERS_H__
#define __REED_NUMBERS_H__

#include <cstddef>
#include <cstdint>
#include <tuple>
#include <vector>

namespace reed {

using u8 = std::uint8_t;   //< An integer ranging from 0 to 256
using i8 = std::int8_t;    //< An integer ranging from -128 to +127
using u16 = std::uint16_t; //< An integer ranging from 0 to 65536
using i16 = std::int16_t;  //< An integer ranging from -32768 to +32767
using u32 = std::uint32_t; //< An integer ranging from 0 to 2^32
using i32 = std::int32_t;  //< An integer ranging from -2^31 to 2^31 - 1
using u64 = std::uint64_t; //< An integer ranging from 0 to 2^64
using i64 = std::int64_t;  //< An integer ranging from -2^63 to 2^63 - 1

const i64 I64_MIN = INT64_MIN;
const i64 I64_MAX = INT64_MAX;

using f32 = float;  //< 32-bit floating point number
using f64 = double; //< 64-bit floating point number

using usize = std::size_t; //< A machine integer used for indexing

/**
  The smallest indivisible unit of distance used for this project.

  The largest absolute value it can represent is approximately
  equivalent to one lightyear.
*/
using Millimeter = i64;

const Millimeter MILLIMETER_MIN = I64_MIN;
const Millimeter MILLIMETER_MAX = I64_MAX;

/**
  A simple 2D mathematical vector

  X should be understood to be positive to the right and Y positive Down
*/
class Vector2
{
private:
  reed::Millimeter x, y;

public:
  Vector2(Millimeter x, Millimeter y)
    : x(x)
    , y(y)
  {
  }

  reed::Millimeter X() { return x; }
  reed::Millimeter Y() { return y; }
};

/**
  A right-angle quadrilateral with unequal sides
*/
class Rectangle
{
private:
  Vector2 top_left, bottom_right;

public:
  /**
    A rectangle that spans the two points

    Mind that @c top_left indeed be above and to the left of
    @c bottom_right
  */
  Rectangle(Vector2 top_left, Vector2 bottom_right)
    : top_left(top_left)
    , bottom_right(bottom_right)
  {
  }

  std::vector<Vector2> corners();
};

using Path = std::vector<Vector2>;
using Polygon = std::vector<Vector2>;

template<typename T>
int
sign(T val)
{
  return (T(0) < val) - (val < T(0));
}

} // namespace reed

/**
  This makes it so you can write 8649 mm as `8649_mm`
*/
reed::Millimeter operator""_mm(unsigned long long int value);

#endif // __REED_NUMBERS_H__

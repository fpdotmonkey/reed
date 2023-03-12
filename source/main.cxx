#include <cstdio>
#include <memory>

#include "Aabb.h"
#include "numbers.h"
#include "ping_pong_path.h"

#define UNUSED(x) (void)x

int
main(int argc, char** argv)
{
  UNUSED(argc);
  UNUSED(argv);

  // field geometry
  reed::Rectangle field{ reed::Vector2{ 0_mm, 0_mm },
                         reed::Vector2{ 10000_mm, 10000_mm } };
  reed::Millimeter mowing_pitch = 500_mm;

  // the trajectory the robot ought to take
  reed::Path motion_plan = ping_pong_path(field, mowing_pitch);

  // Print out the results for plotting in Mathematica

  // field
  std::printf("Graphics[{Dashed,Black");
  std::printf(",Line[{");
  std::vector<reed::Vector2> field_perimeter = field.corners();
  for (size_t i = 0; i < field_perimeter.size(); ++i) {
    std::printf("{%li,%li},", field_perimeter[i].X(), field_perimeter[i].Y());
  }
  std::printf(
    "{%li,%li}}]", field_perimeter.front().X(), field_perimeter.front().Y());

  // motion plan
  std::printf(",Dashing[{}],Red,Line[{");
  for (size_t i = 0; i < motion_plan.size() - 1; ++i) {
    std::printf("{%li,%li},", motion_plan[i].X(), motion_plan[i].Y());
  }
  std::printf("{%li,%li}", motion_plan.back().X(), motion_plan.back().Y());
  std::printf("}]");
  std::printf("}]\n");

  return 0;
}

#include <cstdlib>

#include "ping_pong_path.h"
#include "utilities.h"

reed::Path
reed::ping_pong_path(reed::Rectangle field, reed::Millimeter pitch)
{
  std::vector<Vector2> field_corners = field.corners();
  Millimeter field_height =
    field_corners.back().Y() - field_corners.front().Y();

  Path ping_pong = reed::Path{};

  bool to_the_right = true;
  for (Millimeter y = field_corners.front().Y();
       std::abs(y) <= std::abs(field_corners.back().Y());
       y += sign(field_height) * pitch) {
    if (to_the_right) {
      ping_pong.push_back(Vector2{ field_corners[0].X(), y });
      ping_pong.push_back(Vector2{ field_corners[1].X(), y });
    } else {
      ping_pong.push_back(Vector2{ field_corners[1].X(), y });
      ping_pong.push_back(Vector2{ field_corners[0].X(), y });
    }
    to_the_right = !to_the_right;
  }

  return ping_pong;
}

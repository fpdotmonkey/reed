#include <cstdio>

#include "pathPlanning/Comb.h"

#define UNUSED(x) (void)x

int
main(int argc, char** argv)
{
  UNUSED(argc);
  UNUSED(argv);

  cura::SliceDataStorage storage{};

  cura::Comb path{ &storage,
                   LayerIndex{ 0 },
                   /* comb_boundary_inside_minimum */ nullptr,
                   /* comb_boundary_inside_optimal */ nullptr,
                   /* offset_from_outlines */ 0,
                   /* travel_avoid_distance */ 0,
                   /* move_inside_distance */ 0 };

  return 0;
}

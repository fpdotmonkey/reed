#!/usr/bin/env python3


import math
import sys
from typing import Tuple, List


class Vector2:
    _x: int
    _y: int

    def __init__(self, x, y) -> None:
        self._x = x
        self._y = y

    def x(self) -> int:
        return self._x

    def y(self) -> int:
        return self._y

    def __repr__(self) -> str:
        return "{" + f"{self._x},{self._y}" + "}"


class Rectangle:
    _top_left: Vector2
    _bottom_right: Vector2

    def __init__(self, top_left: Vector2, bottom_right: Vector2) -> None:
        self._top_left = top_left
        self._bottom_right = bottom_right

    def corners(self) -> List[Vector2]:
        return [
            self._top_left,
            Vector2(self._bottom_right.x(), self._top_left.y()),
            self._bottom_right,
            Vector2(self._top_left.x(), self._bottom_right.y()),
        ]

    def __repr__(self) -> str:
        loop = self.corners()
        loop.append(loop[0])
        return str(Path(loop))


class Path:
    _coordinates: List[Vector2]

    def __init__(self, coordinates) -> None:
        self._coordinates = coordinates

    def __repr__(self) -> str:
        return "{" + ",".join(
            str(coordinate) for coordinate in self._coordinates
        ) + "}"


def ping_pong_path(field: Rectangle, pitch: int) -> Path:
    field_corners: List[Vector2] = field.corners()
    field_height: int = field_corners[-1].y() - field_corners[0].y()

    path: List[Vector2] = []

    to_the_right = True
    for y in range(
        field_corners[0].y(),
        field_corners[-1].y(),
        int(math.copysign(pitch, field_height))
    ):
        if to_the_right:
            path.append(Vector2(field_corners[0].x(), y))
            path.append(Vector2(field_corners[1].x(), y))
        else:
            path.append(Vector2(field_corners[1].x(), y))
            path.append(Vector2(field_corners[0].x(), y))
        to_the_right = not to_the_right

    return Path(path)


def main():
    field = Rectangle(Vector2(0, 0), Vector2(10_000, 10_000))
    mowing_pitch: int = 500

    motion_plan: List[Vector2] = ping_pong_path(field, mowing_pitch)

    print(
        "Graphics[{Dashed,Black,Line["
        + str(field)
        + "],Dashing[{}],Red,Line["
        + str(motion_plan)
        + "]}]"
    )


if __name__ == "__main__":
    main()


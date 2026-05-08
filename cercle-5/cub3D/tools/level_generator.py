#!/usr/bin/env python3
"""Generate procedural Cub3D maps with rooms, corridors, and doors."""

import argparse
import math
import os
import random
import sys

DEFAULT_TEXTURES = {
    "NO": "assets/walls/north.xpm",
    "SO": "assets/walls/south.xpm",
    "WE": "assets/walls/west.xpm",
    "EA": "assets/walls/east.xpm",
    "DO": "assets/walls/door.xpm",
}

FLOOR_CEILS = [
    ((100, 100, 100), (50, 50, 150)),
    ((120, 90, 70), (30, 40, 90)),
    ((80, 90, 120), (40, 60, 80)),
    ((90, 70, 50), (50, 40, 70)),
]

DIRECTIONS = ["N", "S", "E", "W"]

MIN_ROOM_SIZE = 5
MAX_ROOM_SIZE = 11


def clamp(value, minimum, maximum):
    return max(minimum, min(maximum, value))


class Room:
    def __init__(self, x, y, w, h):
        self.x = x
        self.y = y
        self.w = w
        self.h = h

    @property
    def center(self):
        return (self.x + self.w // 2, self.y + self.h // 2)

    def intersects(self, other, margin=1):
        return not (
            self.x + self.w + margin <= other.x
            or self.x >= other.x + other.w + margin
            or self.y + self.h + margin <= other.y
            or self.y >= other.y + other.h + margin
        )


def make_grid(width, height):
    return [["1" for _ in range(width)] for _ in range(height)]


def carve_room(grid, room):
    for y in range(room.y, room.y + room.h):
        for x in range(room.x, room.x + room.w):
            grid[y][x] = "0"


def place_pillars(grid, room):
    if room.w < 7 or room.h < 7:
        return
    count = random.randint(0, 2)
    for _ in range(count):
        px = random.randint(room.x + 2, room.x + room.w - 3)
        py = random.randint(room.y + 2, room.y + room.h - 3)
        grid[py][px] = "1"


def carve_h_corridor(grid, x1, x2, y):
    for x in range(min(x1, x2), max(x1, x2) + 1):
        grid[y][x] = "0"


def carve_v_corridor(grid, y1, y2, x):
    for y in range(min(y1, y2), max(y1, y2) + 1):
        grid[y][x] = "0"


def corridor_path(start, end):
    x1, y1 = start
    x2, y2 = end
    if random.choice([True, False]):
        return [(x, y1) for x in range(min(x1, x2), max(x1, x2) + 1)] + [
            (x2, y) for y in range(min(y1, y2), max(y1, y2) + 1)
        ]
    return [(x1, y) for y in range(min(y1, y2), max(y1, y2) + 1)] + [
        (x, y2) for x in range(min(x1, x2), max(x1, x2) + 1)
    ]


def add_door(grid, path):
    if len(path) < 3:
        return None
    candidate = path[len(path) // 2]
    x, y = candidate
    if grid[y][x] == "0":
        grid[y][x] = "2"
        return candidate
    return None


def generate_rooms(width, height, room_count):
    rooms = []
    tries = 0
    while len(rooms) < room_count and tries < room_count * 15:
        w = random.randint(MIN_ROOM_SIZE, MAX_ROOM_SIZE)
        h = random.randint(MIN_ROOM_SIZE, MAX_ROOM_SIZE)
        x = random.randint(1, width - w - 2)
        y = random.randint(1, height - h - 2)
        candidate = Room(x, y, w, h)
        if any(candidate.intersects(other) for other in rooms):
            tries += 1
            continue
        rooms.append(candidate)
        tries += 1
    return rooms


def connect_rooms(grid, rooms):
    if len(rooms) < 2:
        return []
    centers = [room.center for room in rooms]
    used = {0}
    remaining = set(range(1, len(rooms)))
    door_positions = []
    while remaining:
        best_pair = None
        best_dist = None
        for i in used:
            for j in remaining:
                d = (centers[i][0] - centers[j][0]) ** 2 + (centers[i][1] - centers[j][1]) ** 2
                if best_dist is None or d < best_dist:
                    best_dist = d
                    best_pair = (i, j)
        if best_pair is None:
            break
        i, j = best_pair
        path = corridor_path(centers[i], centers[j])
        for x, y in path:
            grid[y][x] = "0"
        door = add_door(grid, path)
        if door:
            door_positions.append(door)
        used.add(j)
        remaining.remove(j)
    return door_positions


def carve_rooms_and_corridors(width, height, room_count):
    grid = make_grid(width, height)
    rooms = generate_rooms(width, height, room_count)
    if not rooms:
        return grid, [], []
    for room in rooms:
        carve_room(grid, room)
        place_pillars(grid, room)
    door_positions = connect_rooms(grid, rooms)

    # add some decorative alcoves and openings
    for room in rooms:
        if random.random() < 0.45:
            for _ in range(random.randint(1, 2)):
                rx = random.randint(room.x + 2, room.x + room.w - 3)
                ry = random.randint(room.y + 2, room.y + room.h - 3)
                grid[ry][rx] = "0"

    return grid, rooms, door_positions


def place_player(grid, rooms):
    if not rooms:
        return None
    room = random.choice(rooms)
    x = clamp(room.x + room.w // 2, room.x + 1, room.x + room.w - 2)
    y = clamp(room.y + room.h // 2, room.y + 1, room.y + room.h - 2)
    direction = random.choice(DIRECTIONS)
    grid[y][x] = direction
    return (x, y, direction)


def build_map_text(lines, floor_ceil):
    config = []
    for key, path in DEFAULT_TEXTURES.items():
        config.append(f"{key} {path}")
    f, c = floor_ceil
    config.append(f"F {f[0]},{f[1]},{f[2]}")
    config.append(f"C {c[0]},{c[1]},{c[2]}")
    return config + ["" ] + ["".join(row) for row in lines]


def save_map(path, grid, floor_ceil):
    lines = build_map_text(grid, floor_ceil)
    os.makedirs(os.path.dirname(path), exist_ok=True)
    with open(path, "w", encoding="utf-8") as f:
        for line in lines:
            f.write(line + "\n")


def parse_args():
    parser = argparse.ArgumentParser(description="Generate procedural Cub3D maps.")
    parser.add_argument("output", help="Output .cub file path")
    parser.add_argument("--width", type=int, default=41, help="Map width in tiles")
    parser.add_argument("--height", type=int, default=25, help="Map height in tiles")
    parser.add_argument("--rooms", type=int, default=5, help="Approximate number of rooms")
    parser.add_argument("--seed", type=int, default=None, help="Random seed")
    return parser.parse_args()


def main():
    args = parse_args()
    if args.seed is not None:
        random.seed(args.seed)
    width = max(21, args.width if args.width % 2 == 1 else args.width + 1)
    height = max(15, args.height if args.height % 2 == 1 else args.height + 1)
    room_count = clamp(args.rooms, 3, 8)

    grid, rooms, doors = carve_rooms_and_corridors(width, height, room_count)
    player = place_player(grid, rooms)
    if player is None:
        raise RuntimeError("Failed to place player spawn")

    floor_ceil = random.choice(FLOOR_CEILS)
    save_map(args.output, grid, floor_ceil)
    print(f"Generated {args.output} ({width}x{height}) with {len(rooms)} rooms and {len(doors)} door(s).")
    print(f"Player spawn at {player[0]},{player[1]} facing {player[2]}.")


if __name__ == "__main__":
    main()

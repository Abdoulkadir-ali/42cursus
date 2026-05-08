import random
import sys

def generate_giant_map(width, height, filename):
    with open(filename, 'w') as f:
        f.write("NO assets/walls/north.xpm\n")
        f.write("SO assets/walls/south.xpm\n")
        f.write("WE assets/walls/west.xpm\n")
        f.write("EA assets/walls/east.xpm\n")
        f.write("DO assets/door/idle/idle0.xpm\n")
        f.write("\n")
        f.write("F 20,20,20\n")
        f.write("C 200,200,200\n")
        f.write("\n")
        
        # Draw a big box with a maze-like structure
        map_grid = [['1' for _ in range(width)] for _ in range(height)]
        
        for y in range(1, height - 1):
            for x in range(1, width - 1):
                if random.random() > 0.3:
                    map_grid[y][x] = '0'
                elif random.random() > 0.95:
                    map_grid[y][x] = '2' # Door
                else:
                    map_grid[y][x] = '1' # Wall
        
        # Place player
        map_grid[height//2][width//2] = 'N'
        
        for row in map_grid:
            f.write("".join(row) + "\n")

if __name__ == "__main__":
    w = int(sys.argv[1]) if len(sys.argv) > 1 else 500
    h = int(sys.argv[2]) if len(sys.argv) > 2 else 500
    name = sys.argv[3] if len(sys.argv) > 3 else "maps/gigantic.cub"
    generate_giant_map(w, h, name)

import sys
import random
import os

def generate_rt_stress(n_objects, output_file):
    """
    Generates a miniRT .rt file with a large number of spheres arranged in a grid.
    """
    # Header: Ambient, Camera, and two Lights for better depth
    # Moved camera further back to accommodate 100k objects
    header = [
        "A 0.2 210,220,255",
        "C 0,150,450 0,-0.2,-1 70",
        "L 100,300,200 0.7 255,250,230",
        "L -150,200,300 0.5 200,230,255"
    ]
    
    # Ensure the directory exists
    os.makedirs(os.path.dirname(output_file), exist_ok=True)
    
    try:
        with open(output_file, 'w') as f:
            for line in header:
                f.write(line + '\n')
            
            # Calculate grid dimensions to distribute 100k objects
            # We want a cuboid distribution
            side_x = int(n_objects**(1/3))
            side_y = side_x
            side_z = (n_objects + (side_x * side_y) - 1) // (side_x * side_y)
            
            spacing = 10.0 # Wide spacing to avoid too much overlap
            
            count = 0
            print(f"Writing {n_objects} objects...")
            
            for z in range(side_z):
                for y in range(side_y):
                    for x in range(side_x):
                        if count >= n_objects:
                            break
                        
                        # Slightly vary the diameter to look more natural
                        diameter = 3.0 + random.random() * 2.0
                        
                        # Center the grid on X, but stack Y upwards and Z backwards
                        pos_y = (y) * spacing + (diameter / 2.0) + 1.1
                        pos_x = (x - side_x/2) * spacing
                        pos_z = -(z) * spacing
                        
                        # Generate harmonious colors instead of pure random for better aesthetics
                        # Using HSL-like approach: high saturation, medium brightness
                        r = random.randint(100, 255)
                        g = random.randint(100, 255)
                        b = random.randint(100, 255)
                        
                        # Add a tiny bit of jitter to positions so it's not a perfect grid (better for stress testing BVH)
                        jitter = 2.0
                        pos_x += (random.random() - 0.5) * jitter
                        pos_y += (random.random() - 0.5) * jitter
                        pos_z += (random.random() - 0.5) * jitter
                        
                        f.write(f"sp {pos_x:.2f},{pos_y:.2f},{pos_z:.2f} {diameter:.2f} {r},{g},{b}\n")
                        count += 1
                        
                        if count % 10000 == 0:
                            print(f" Progress: {count}/{n_objects} ({(count/n_objects)*100:.1f}%)")
                if count >= n_objects:
                    break
            
            # Add a large floor plane
            f.write("pl 0,0,0 0,1,0 150,150,150\n")
            
        print(f"Successfully generated {output_file} with {count} objects.")
        return True
    except Exception as e:
        print(f"Error writing file: {e}")
        return False

if __name__ == "__main__":
    # Default settings
    N = 100000
    OUTPUT_DIR = "maps/rt"
    FILENAME = "stress_100k.rt"
    
    # Simple CLI argument parsing
    if len(sys.argv) > 1:
        try:
            N = int(sys.argv[1])
        except ValueError:
            print(f"Invalid number: {sys.argv[1]}. Using default 100,000.")
            
    if len(sys.argv) > 2:
        FILENAME = sys.argv[2]
        if not FILENAME.endswith(".rt"):
            FILENAME += ".rt"

    # Resolve full path relative to script location or absolute
    target_path = os.path.join(OUTPUT_DIR, FILENAME)
    
    # If the script is run from within /scripts/, we might need to adjust path
    # But usually it's run from the root.
    if not os.path.isabs(target_path) and not os.path.exists("maps"):
        # Attempt to find maps directory
        if os.path.exists("../maps"):
            target_path = os.path.join("../maps/rt", FILENAME)

    generate_rt_stress(N, target_path)

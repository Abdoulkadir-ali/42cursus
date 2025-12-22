# FDF - 3D Wireframe Viewer

FDF (Fil de Fer) is a 3D wireframe visualization program that renders topographic maps from `.fdf` files. It provides interactive 3D exploration with multiple projection modes, real-time transformations, and advanced rendering optimizations.

## Features

- **3D Wireframe Rendering**: Displays topographic data as connected line segments in 3D space
- **Dual Projection Systems**: Parallel (isometric-like) and Conic (perspective) projections
- **Interactive Controls**: Real-time rotation, zoom, translation, and parameter adjustment
- **Dynamic Tessellation**: Adaptive mesh subdivision for enhanced detail
- **Color Mapping**: Multiple color schemes including gradient, solid, zebra, neon, and cyberpunk styles
- **GUI Interface**: On-screen controls and information panels
- **Optimization Features**: View frustum culling, level-of-detail (LOD), and rendering optimizations

## Technical Implementation

### Core Mathematics

#### Projection Systems

**Parallel Projection (Isometric-like)**:
- Uses shear transformation controlled by angle α (alpha)
- Projection matrix includes shear components: `mat.m[0][2] = cotan`, `mat.m[1][2] = cotan`
- Compensates for camera translation drift with inverse shear offset
- Z-normalization range: -2/(10000-0.1) for depth buffering

**Conic Projection (Perspective)**:
- Field-of-view (FOV) controlled by angle α
- Standard perspective matrix with aspect ratio correction
- Near plane offset: -2.0 * 0.1 for clipping
- Perspective divide enabled via `mat.m[3][2] = -1.0`

#### Transformation Pipeline

The rendering pipeline follows a Model-View-Projection (MVP) matrix approach:

1. **Model Space**: Points centered around grid center, Z-scaled by `z_scale` factor
2. **View Space**: 
   - Rotation applied via 3×3 rotation matrix stored in camera
   - Translation (dolly) moves camera back by calculated distance
   - Distance calculation: `cam_dist = 500.0f / tan_half_fov` for perspective mode
3. **Projection Space**: Unified matrix handles both parallel and conic projections
4. **Screen Space**: Final scaling and offset to viewport coordinates

#### Matrix Operations

- **Identity Matrix**: Standard 4×4 identity initialization
- **Matrix Multiplication**: Standard 4×4 matrix multiplication for combining transformations
- **Translation Matrix**: Adds translation components to identity matrix
- **Scale Matrix**: Multiplies diagonal elements for uniform/non-uniform scaling
- **Rotation Matrix**: Built from 3×3 rotation matrix stored in camera structure

#### Tessellation Algorithm

Implements adaptive mesh subdivision:
- **Direct Copy**: Original grid points (even coordinates)
- **Horizontal Interpolation**: Linear interpolation between adjacent X points
- **Vertical Interpolation**: Linear interpolation between adjacent Y points
- **Center Interpolation**: Bilinear interpolation using diagonal neighbors

Color interpolation uses linear blending between neighboring points.

#### Vector Mathematics

Supports multiple vector types:
- `t_vec2/t_vec2d`: 2D integer/double precision vectors
- `t_vec3/t_vec3d`: 3D integer/double precision vectors
- `t_vecu2/t_vecu3`: Unsigned integer vectors

Operations include:
- Component-wise addition, subtraction, multiplication, division
- Scalar multiplication and division
- Euclidean distance calculations
- Min/max component extraction

### Rendering Optimizations

#### View Frustum Culling
- Calculates bounding boxes for line segments
- Tests against view frustum planes
- Eliminates invisible geometry before rasterization

#### Level of Detail (LOD)
- Dynamically adjusts tessellation level based on distance
- Reduces computational load for distant objects
- Maintains visual quality for close-up views

#### Z-Buffering
- Maintains depth information per pixel
- Prevents rendering artifacts from overlapping geometry
- Uses view-space Z coordinates for accurate depth testing

### Color and Styling

#### Color Interpolation
- Linear color blending between grid points
- Supports RGB and potentially other color spaces
- Maintains color continuity across tessellated surfaces

#### Style Presets
- **Default**: Standard height-based coloring
- **Gradient**: Smooth color transitions
- **Solid**: Uniform coloring
- **Zebra**: Alternating stripe patterns
- **Neon**: High-contrast glowing effects
- **Cyberpunk**: Futuristic color schemes

### GUI System

#### Control Panels
- Real-time parameter adjustment
- Visual feedback for current settings
- Multiple style themes (Tron Blue, Tron Orange, Matrix, Cyberpunk, Neon Grid)

#### Information Display
- Current projection mode
- Camera parameters (rotation, zoom, offset)
- Performance metrics
- Map statistics

## Dependencies

- **MiniLibX**: X11-based graphics library for Linux
- **Libft**: Custom C standard library implementation
- **X11 Libraries**: X11, Xext for window management
- **Math Library**: Standard math functions for trigonometry and floating-point operations

## Installation

1. Clone the repository and navigate to the project directory
2. Ensure MiniLibX and Libft are properly configured
3. Run `make` to compile the project

```bash
make
```

## Usage

### Basic Execution
```bash
./fdf [map_file.fdf]
```

If no file is specified, the program loads all available maps from the `maps/` directory.

### Map File Format
FDF files contain topographic data in the following format:
- Each line represents a row of points
- Values are space-separated integers representing height (Z-coordinate)
- Optional: Color values in hexadecimal format (0xRRGGBB)

Example:
```
0 0 0 0
0 1 2 0
0 2 4 0
0 0 0 0
```

### Controls

#### Camera Movement
- **Arrow Keys**: Rotate view (X/Y axes)
- **Q/E**: Rotate around Z-axis
- **WASD**: Translate camera position
- **Mouse Drag**: Rotate view (alternative to arrow keys)

#### Zoom and Scale
- **Mouse Wheel**: Zoom in/out
- **+/- Keys**: Adjust zoom level
- **Page Up/Down**: Fine zoom adjustment
- **Z/X**: Adjust Z-axis scaling

#### Projection Controls
- **P**: Toggle between Parallel and Conic projection
- **A/S**: Adjust projection angle α (shear for parallel, FOV for conic)

#### Map Navigation
- **Tab**: Cycle through available maps
- **Space**: Reset camera to default position

#### Style Controls
- **C**: Cycle through color styles
- **G**: Cycle through GUI themes
- **T**: Toggle tessellation on/off

#### Optimization
- **O**: Toggle optimization features
- **L**: Adjust level-of-detail
- **F**: Adjust frustum culling margin

#### Miscellaneous
- **H**: Toggle help panel
- **I**: Toggle information display
- **ESC**: Exit program

## Project Structure

```
fdf/
├── includes/          # Header files
├── srcs/             # Source code
│   ├── core/         # Main program logic
│   ├── events/       # Input handling
│   ├── geometry/     # Mathematical operations
│   ├── graphics/     # Rendering pipeline
│   ├── gui/          # User interface
│   ├── render/       # Camera and projection
│   └── window/       # Window management
├── libft/            # Custom standard library
├── minilibx-linux/   # Graphics library
├── maps/             # Sample map files
└── objs/             # Compiled object files
```

## Performance Considerations

- **SIMD Optimizations**: Uses AVX instructions for vector operations
- **Fast Math**: Compiler optimizations for floating-point calculations
- **Memory Management**: Efficient allocation and cleanup of large datasets
- **Threading**: Potential for parallel processing of independent operations

## Development Notes

This implementation demonstrates advanced computer graphics concepts including:
- Homogeneous coordinates and matrix transformations
- Multiple projection systems
- Real-time 3D rendering optimizations
- Interactive GUI design
- Cross-platform graphics programming with X11

The code is structured for maintainability with clear separation of concerns between geometry, rendering, and user interface components.</content>
<parameter name="filePath">/home/abdali/cursus/cercle-3/fdf/README.md
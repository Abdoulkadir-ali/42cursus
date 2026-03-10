# Geometry Map Style

## Directory Structure

- `style.c`: assign point colors from the active style.
- `themes.c`: predefined color themes used by map styling.

## How It Works

Style helpers transform raw z values or preserved source colors into display
colors. The active map style determines whether colors come from gradients,
simple themes, or the original map data.

## Developer Notes

- `MAP_STYLE_RAW` preserves imported colors without recomputation.
- Theme helpers stay small so style switching in the event system remains cheap.
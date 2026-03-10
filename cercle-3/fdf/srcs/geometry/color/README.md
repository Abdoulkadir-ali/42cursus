# Geometry Color

## Directory Structure

- `create.c`: build RGB vectors and integer color values.
- `get.c`: convert packed integer colors back into RGB vectors.
- `transform.c`: clamp, shift, and interpolate colors, including height palettes.

## How It Works

This folder centralizes color conversions used by geometry and rendering. Map
parsing can import packed hexadecimal colors, map styling derives palettes from
altitude, and tessellation reuses interpolation helpers when creating midpoint
colors.

## Developer Notes

- Height colors use a logarithmic ratio so large altitude ranges remain readable.
- Color helpers operate on `t_vec3` values to match the project's primitive types.
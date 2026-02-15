#!/usr/bin/env python3
"""Generate test OBJ files for mesh performance benchmarking."""
import math
import sys
import os

def gen_icosphere(subdivisions):
    """Generate an icosphere with the given number of subdivisions."""
    # Start with icosahedron
    t = (1.0 + math.sqrt(5.0)) / 2.0
    verts = [
        (-1,  t,  0), ( 1,  t,  0), (-1, -t,  0), ( 1, -t,  0),
        ( 0, -1,  t), ( 0,  1,  t), ( 0, -1, -t), ( 0,  1, -t),
        ( t,  0, -1), ( t,  0,  1), (-t,  0, -1), (-t,  0,  1),
    ]
    # Normalize
    verts = [normalize(v) for v in verts]
    faces = [
        (0,11,5),(0,5,1),(0,1,7),(0,7,10),(0,10,11),
        (1,5,9),(5,11,4),(11,10,2),(10,7,6),(7,1,8),
        (3,9,4),(3,4,2),(3,2,6),(3,6,8),(3,8,9),
        (4,9,5),(2,4,11),(6,2,10),(8,6,7),(9,8,1),
    ]
    midpoint_cache = {}
    for _ in range(subdivisions):
        new_faces = []
        for tri in faces:
            a = get_midpoint(verts, midpoint_cache, tri[0], tri[1])
            b = get_midpoint(verts, midpoint_cache, tri[1], tri[2])
            c = get_midpoint(verts, midpoint_cache, tri[2], tri[0])
            new_faces.extend([
                (tri[0], a, c), (tri[1], b, a),
                (tri[2], c, b), (a, b, c),
            ])
        faces = new_faces
    return verts, faces

def normalize(v):
    l = math.sqrt(v[0]**2 + v[1]**2 + v[2]**2)
    return (v[0]/l, v[1]/l, v[2]/l)

def get_midpoint(verts, cache, i1, i2):
    key = (min(i1,i2), max(i1,i2))
    if key in cache:
        return cache[key]
    v1, v2 = verts[i1], verts[i2]
    mid = normalize(((v1[0]+v2[0])/2, (v1[1]+v2[1])/2, (v1[2]+v2[2])/2))
    idx = len(verts)
    verts.append(mid)
    cache[key] = idx
    return idx

def write_obj(filename, verts, faces, with_normals=True):
    """Write OBJ file."""
    with open(filename, 'w') as f:
        f.write(f"# Generated test mesh: {len(verts)} verts, {len(faces)} tris\n")
        for v in verts:
            f.write(f"v {v[0]:.6f} {v[1]:.6f} {v[2]:.6f}\n")
        if with_normals:
            for v in verts:
                # For a sphere, normal = vertex position (normalized)
                f.write(f"vn {v[0]:.6f} {v[1]:.6f} {v[2]:.6f}\n")
            for face in faces:
                f.write(f"f {face[0]+1}//{face[0]+1} {face[1]+1}//{face[1]+1} {face[2]+1}//{face[2]+1}\n")
        else:
            for face in faces:
                f.write(f"f {face[0]+1} {face[1]+1} {face[2]+1}\n")
    print(f"  {filename}: {len(verts)} verts, {len(faces)} tris")

def gen_grid_plane(nx, nz):
    """Generate a subdivided plane (stress test for flat BVH)."""
    verts = []
    faces = []
    for iz in range(nz + 1):
        for ix in range(nx + 1):
            x = (ix / nx) * 2.0 - 1.0
            z = (iz / nz) * 2.0 - 1.0
            verts.append((x, 0.0, z))
    for iz in range(nz):
        for ix in range(nx):
            i = iz * (nx + 1) + ix
            faces.append((i, i + 1, i + nx + 1))
            faces.append((i + 1, i + nx + 2, i + nx + 1))
    return verts, faces

def main():
    outdir = os.path.join(os.path.dirname(os.path.dirname(__file__)), "maps", "obj")
    os.makedirs(outdir, exist_ok=True)
    
    print("Generating test OBJ files:")
    
    # Icospheres of increasing complexity
    for subdiv, name in [(1, "ico_80"), (2, "ico_320"), (3, "ico_1280"),
                          (4, "ico_5120"), (5, "ico_20480")]:
        verts, faces = gen_icosphere(subdiv)
        write_obj(os.path.join(outdir, f"{name}.obj"), verts, faces)
    
    # Grid planes (pathological for BVH — many coplanar triangles)
    for n, name in [(10, "grid_100"), (50, "grid_2500"), (100, "grid_10000")]:
        verts, faces = gen_grid_plane(n, n)
        write_obj(os.path.join(outdir, f"{name}.obj"), verts, faces, with_normals=False)
    
    print("\nDone!")

if __name__ == "__main__":
    main()

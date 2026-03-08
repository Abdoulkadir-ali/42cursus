# Shapes — Bug Fixes + New Primitives

---

## Issue 1 — Cone appears pitch-black under regular lighting

### Root cause

`fill_hit_record` in `srcs/rays/raytracing/intersection/cone/hit.c` computes:

```c
radial = vec3_sub(temp, vec3_scale(cone->transform.forward, h));
hit->normal = vec3_norm(radial);   // ← WRONG: pure radial, no axial component
```

The radial vector points straight perpendicular to the cone's axis.  For a
point light directly above the cone, `dot(N, L) ≈ 0` → zero diffuse → black.

### Correct cone surface normal

A cone with apex at `pos`, axis `forward`, half-angle `α` (where
`tan(α) = k = scale.x / scale.y`) has the outward surface normal:

```
N = normalize(radial_hat − k · forward)
```

Derivation: the tangent in the elevation direction is `T = forward + k·radial_hat`.
The normal perpendicular to T lying in the `(forward, radial_hat)` plane is
`radial_hat − k·forward`; verify: `dot(N,T) = k − k = 0`. ✓

### Fix — `srcs/rays/raytracing/intersection/cone/hit.c`

```c
// inside fill_hit_record, after radial is computed:
double  k = cone->transform.scale.x / cone->transform.scale.y;
t_vec3  radial_hat;

if (vec3_dot(radial, radial) < EPSILON * EPSILON)
    hit->normal = cone->transform.forward;
else
{
    radial_hat = vec3_norm(radial);
    hit->normal = vec3_norm(
        vec3_sub(radial_hat, vec3_scale(cone->transform.forward, k)));
}
```

**Scope**: 5 lines changed in one file.  No header or pipeline changes needed.

---

## Issue 2 — Physics: Cylinder and Cone have no collision simulation

### Current state

`generate_contacts` in `srcs/physics/contacts.c` iterates only
`scene->spheres[]` and dispatches to three functions:
- `collide_sphere_sphere`
- `collide_sphere_plane`
- `collide_sphere_mesh`

Cylinder and cone are never queried as dynamic bodies.

### Strategy — capsule approximation

Both shapes are approximated as **capsules** (line segment + radius) for
collision, matching the approach already used for mesh physics
(`COLLIDER_CAPSULE` in `mesh_apply_transform`).  This avoids implementing
full analytical cylinder/cylinder SAT which is expensive and rarely needed.

A capsule for a cylinder `cy`:
- Segment A = `pos + forward * h/2`, B = `pos − forward * h/2`
  (where h = `transform.scale.y / 2`)
- Radius = `transform.scale.x`

A capsule for a cone `co`:
- Segment A = apex (`pos`), B = base center (`pos + forward * scale.y`)
- Radius = `scale.x` (max base radius — conservative)

### Plan — 3 new functions in `srcs/physics/collide.c`

```c
// Returns closest approach between two segments, for capsule-capsule
static double segment_segment_sq(t_vec3 p0, t_vec3 p1,
                                 t_vec3 q0, t_vec3 q1, t_vec3 *out_cp);

bool    collide_cylinder_sphere(t_cylinder *cy, t_sphere *sp, t_contact *c);
bool    collide_cylinder_plane (t_cylinder *cy, t_plane *pl,  t_contact *c);
bool    collide_cylinder_cylinder(t_cylinder *a, t_cylinder *b, t_contact *c);
// Cone reuses cylinder functions by wrapping into a conservative cylinder
```

Declarations added to `includes/physics.h`.

### Plan — `srcs/physics/contacts.c` — `generate_contacts`

Add a new `query_cylinder` loop (mirrors `query_sphere`):

```c
static int  query_cylinder(t_scene *s, int idx, t_contact *c,
                            int count, int max)
{
    // skip if static
    // AABB broadphase via cylinder_aabb
    // narrow: collide_cylinder_sphere against all spheres
    // narrow: collide_cylinder_plane against all planes
    // narrow: collide_cylinder_cylinder against all later cylinders
}
```

Similarly, a `query_cone` that wraps the cone's base cylinder.

`integrate_bodies` in `srcs/physics/integrate.c` needs extension to read
`transform` from `t_cylinder` and `t_cone` and apply velocity integration
(same math as sphere, different struct pointer).

### Files touched

| File | Change |
|------|--------|
| `srcs/physics/collide.c` | 3 new `collide_cylinder_*` functions (~80 lines) |
| `srcs/physics/contacts.c` | `query_cylinder` + `query_cone` loops in `generate_contacts` |
| `srcs/physics/integrate.c` | extend `integrate_bodies` to iterate cylinders + cones |
| `includes/physics.h` | declare the 3 new collide functions |

No raytracing or BVH changes needed — collision uses AABBs internally.

---

## Feature 3 — New Shapes: Triangle, Rectangle, Pyramid

### A) Triangle (`tr`)

`intersect_triangle` and `t_triangle` **already exist** in the codebase.
The struct holds 3 vertex indices into a mesh — not standalone.
A standalone RT triangle needs its own scene-level struct.

#### New struct (add to `includes/objects.h`)

```c
struct s_tri_shape {          // distinct from s_triangle (mesh index helper)
    t_vec3  v[3];             // world-space vertices
    int     mat_id;
    t_vec3  temp_color;
    t_vec3  normal;           // precomputed face normal (cross + normalise)
};
typedef struct s_tri_shape  t_tri_shape;
```

#### RT format

```
tr  x0,y0,z0  x1,y1,z1  x2,y2,z2  r,g,b
```

Fields — same comma-separated style as all existing tokens:

| Field | Meaning |
|-------|---------|
| `x0,y0,z0` | vertex 0 (world space) |
| `x1,y1,z1` | vertex 1 |
| `x2,y2,z2` | vertex 2 |
| `r,g,b` | color (0–255 integers) |

**Examples:**
```
# flat triangle in the XY plane
tr  -2,0,5  2,0,5  0,3,5  255,80,60

# tilted triangle
tr  0,0,0  4,0,2  2,5,1  100,200,150
```

Parser (`srcs/objects/rt/polygons/triangle_shape.c`):

```c
t_parse_obj  parse_tri_shape(t_parser *p)
{
    t_parse_obj  res = {0};

    res.type = TYPE_NONE;
    if (!parse_vec3(p, &res.data.tri_shape.v[0])) return (res);
    if (!parse_vec3(p, &res.data.tri_shape.v[1])) return (res);
    if (!parse_vec3(p, &res.data.tri_shape.v[2])) return (res);
    t_vec3 rgb;
    if (!parse_vec3(p, &rgb))                     return (res);
    res.data.tri_shape.temp_color = rgb;
    res.data.tri_shape.mat_id = 0;
    // precompute face normal
    t_vec3 e1 = vec3_sub(res.data.tri_shape.v[1], res.data.tri_shape.v[0]);
    t_vec3 e2 = vec3_sub(res.data.tri_shape.v[2], res.data.tri_shape.v[0]);
    res.data.tri_shape.normal = vec3_norm(vec3_cross(e1, e2));
    res.type = TYPE_TRI;
    return (res);
}
```

Dispatcher hook in `dispatch_shapes` (`dispatch.c`):

```c
if (id[0] == 't' && id[1] == 'r')
    return (parse_tri_shape(p));
```

#### Pipeline touches

| Layer | File(s) | Work |
|-------|---------|------|
| RT parser | `dispatch.c` + new `polygons/triangle_shape.c` | token `"tr"`, parse 3 vecs → `TYPE_TRI` |
| Scene | `scene/add/shapes.c`, `scene/create.c` | `scene_add_tri`, `scene->tris[]`, `tri_count` |
| BVH | `bvh/bound/shapes/tri_shape.c` | `tri_shape_aabb` → tight AABB of 3 pts |
| BVH collect | `bvh/tree/collect.c` | emit one ref per `t_tri_shape` |
| Intersection | `intersection/tri_shape/intersect.c` | wrapper calling `intersect_triangle_fast` |
| Shading | `postprocess/shading/material.c` | `TYPE_TRI` branch → `tris[i].mat_id` |

---

### B) Rectangle (`rc`)

Defined as **two triangles** sharing a diagonal — no new intersection math.
Parser builds 2 `t_tri_shape` entries from 4 corner vertices.

#### RT format

```
rc  x0,y0,z0  x1,y1,z1  x2,y2,z2  x3,y3,z3  r,g,b
```

Vertices must be listed **in order** around the quad (either CW or CCW).
The parser splits `(v0,v1,v2)` and `(v0,v2,v3)` and calls `scene_add_tri` twice.

| Field | Meaning |
|-------|---------|
| `x0,y0,z0` … `x3,y3,z3` | four corners in winding order |
| `r,g,b` | color (0–255) |

**Examples:**
```
# axis-aligned rectangle on the XZ plane at Y=0
rc  -3,0,-2  3,0,-2  3,0,2  -3,0,2  180,120,60

# tilted rectangle
rc  0,0,0  4,0,0  4,2,1  0,2,1  200,200,80
```

Parser (`polygons/triangle_shape.c` — same file, second function):

```c
t_parse_obj  parse_rect_shape(t_parser *p)
{
    t_vec3   v[4];
    t_vec3   rgb;
    t_parse_obj res = {0};

    res.type = TYPE_NONE;
    for (int i = 0; i < 4; i++)
        if (!parse_vec3(p, &v[i])) return (res);
    if (!parse_vec3(p, &rgb))     return (res);
    // emit tri 0 (v0,v1,v2) and tri 1 (v0,v2,v3) via scene_add_tri
    // return TYPE_RECT as a sentinel — the scene handler adds two tris
    ...
    res.type = TYPE_RECT;
    return (res);
}
```

Dispatcher hook:

```c
if (id[0] == 'r' && id[1] == 'c')
    return (parse_rect_shape(p));
```

No new BVH/intersection layer needed — reuses the tri pipeline.

---

### C) Pyramid (`py`)

Defined as: 1 square base (`rc`) + 4 triangular side faces → 6 `t_tri_shape` total.

#### RT format — consistent with `cy` / `cn` style (pos, axis, size, height, color)

```
py  cx,cy,cz  nx,ny,nz  base_size  height  r,g,b
```

| Field | Meaning |
|-------|---------|
| `cx,cy,cz` | base center position |
| `nx,ny,nz` | up-axis (normalised) — same role as cylinder's axis |
| `base_size` | full side length of the square base |
| `height` | perpendicular distance from base to apex |
| `r,g,b` | color (0–255) |

**Examples:**
```
# upright pyramid, base at Y=0
py  0,0,0  0,1,0  4  3  100,200,50

# tilted pyramid
py  2,1,-5  0.57,0.57,0.57  2  4  255,140,30
```

Parser (`polygons/pyramid.c`):

```c
t_parse_obj  parse_pyramid(t_parser *p)
{
    t_vec3  center, up, rgb;
    double  base_size, height;
    // parse_vec3 x3, parse_double x2, parse_vec3 rgb
    // compute two arbitrary perpendicular base axes (right, fwd) from up
    // build 4 base corners, apex = center + up * height
    // call scene_add_tri 6 times (2 base + 4 sides)
    ...
    res.type = TYPE_PYRAMID;
    return (res);
}
```

Dispatcher hook:

```c
if (id[0] == 'p' && id[1] == 'y')
    return (parse_pyramid(p));
```

Parser generates 6 `t_tri_shape` entries:
- 2 for the base square (split along diagonal)
- 4 for the side triangles (each base edge → apex)

No new BVH/intersection layer needed — reuses the tri pipeline entirely.

No new rendering code needed.

---

## Implementation Order

```
Phase 1 — Cone normal fix (30 min, 1 file)
  └─ hit.c: replace vec3_norm(radial) with vec3_norm(radial_hat − k·forward)

Phase 2 — Triangle shape (half-day)
  ├─ objects.h: add t_tri_shape, TYPE_TRI enum value
  ├─ scene: tri array, scene_add_tri
  ├─ BVH: bound + collect
  ├─ intersection wrapper
  ├─ shading material.c branch
  └─ RT parser: "tr" token

Phase 3 — Rectangle (1 hr, built on Phase 2)
  └─ RT parser: "rc" token, call scene_add_tri twice

Phase 4 — Pyramid (1 hr, built on Phase 3)
  └─ RT parser: "py" token, compute 5 tris, call scene_add_tri×5

Phase 5 — Cylinder/Cone physics (half-day)
  ├─ collide.c: collide_cylinder_{sphere,plane,cylinder}
  ├─ contacts.c: query_cylinder + query_cone
  └─ integrate.c: extend integrate_bodies
```

Phases 2–4 are strictly additive (new enum value, new scene arrays, new dispatch
token) — zero risk of regression to existing sphere/plane/cylinder/cone rendering.

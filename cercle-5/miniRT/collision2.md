# Collision Extension Plan — Phase 2

## Status coming in

| Pair | Works |
|------|-------|
| Sphere ↔ Sphere | ✅ |
| Sphere ↔ Plane | ✅ |
| Sphere ↔ Box | ✅ |
| Sphere ↔ Capsule | ✅ |
| Box ↔ Box | ✅ |
| Box ↔ Capsule | ✅ |
| Capsule ↔ Capsule | ✅ |
| Sphere ↔ Mesh | ✅ |
| Everything ↔ Plane | ⚠️ partial — rect/tri/pyramid/cylinder dive through |

---

## Bug 1 — Rect / Tri / Pyramid / Cylinder dive through the floor

### Root cause

`collide_rect_plane`, `collide_tri_plane`, `collide_pyramid_plane`, and
`collide_cylinder_plane` all use the "single deepest vertex" pattern (first session's
box/capsule bug). When multiple vertices are below the plane, only the worst contact is
reported per frame. The solver pushes that corner up, a different corner becomes deepest
next frame, and the shape rocks/spins/sinks indefinitely.

**Fix (identical to the box/capsule fix already done):**
- Change all four functions to return `int` (count of contacts written).
- Write **every** penetrating vertex as a separate contact into the output array.
- Update their signatures in `physics.h`.
- Update callers in `contacts.c` to use `count +=`.

Additionally `pyramid_get_verts()` is extracted to a static helper so the vertex
computation can be reused by the new pyramid-vs-shape functions.

---

## Bug 2 — Cylinder collides only with planes

### Approach: cylinder as "fat capsule"

A cylinder's collision boundary is geometrically identical to a capsule minus the
hemispherical caps (which are never relevant for normal gameplay contact). Treating the
cylinder axis segment as a capsule segment with `radius = transform.scale.x` gives
correct results for smooth contacts.

| New function | Method |
|---|---|
| `collide_cylinder_sphere` | closest point on cylinder axis to sphere center — sphere test |
| `collide_cylinder_capsule` | seg-seg closest (Ericson §5.1.9) — same as capsule-capsule |
| `collide_cylinder_box` | 5-sample sweep along cylinder axis into OBB — same as box-capsule |

Wired into `query_cylinder` with AABB broadphase guard.

---

## Bug 3 — Rect / Tri / Pyramid do not collide with spheres / capsules

### Approach: vertex-push

Each vertex of the shape is a point. If a vertex falls inside a sphere (dist < radius) or
inside a capsule (dist to segment < radius), a contact is generated with the vertex as the
contact point and the push direction pointing outward. This correctly handles corners
jabbing into round bodies.

**New static helpers (in `collide.c`):**
- `vertex_vs_sphere(v, sp, pb, tr, c)` — point-inside-sphere test → contact
- `vertex_vs_capsule(v, cap, pb, tr, c)` — closest-point-on-segment test → contact

**New public multi-contact functions (int return):**
| Function | Vertices tested |
|---|---|
| `collide_rect_sphere` / `collide_rect_capsule` | 4 (stored in `rc->v[]`) |
| `collide_tri_sphere` / `collide_tri_capsule` | 3 (stored in `tr->v[]`) |
| `collide_pyramid_sphere` / `collide_pyramid_capsule` | 5 (via `pyramid_get_verts`) |

Wired into `query_rect`, `query_tri`, `query_pyramid` with AABB broadphase guard.

### What we skip (no vertex data / too complex)

- Rect/Tri/Pyramid vs Box — no OBB-vertex test implemented; low priority
- Cylinder vs Cylinder — would require additional seg-seg contact (not needed for now—
  cylinders are rare in contact with each other)
- Reverse: sphere/capsule hitting the *face* of a rect/tri — requires finite-plane
  bounded projection test; deferred

---

## Implementation checklist

| # | Change | File | Done |
|---|--------|------|------|
| 1 | `collide_rect_plane` → `int`, all 4 verts | collide.c | ⬜ |
| 2 | `collide_tri_plane` → `int`, all 3 verts | collide.c | ⬜ |
| 3 | Extract `pyramid_get_verts`, `collide_pyramid_plane` → `int` | collide.c | ⬜ |
| 4 | `collide_cylinder_plane` → `int`, both caps | collide.c | ⬜ |
| 5 | Add `vertex_vs_sphere` + `vertex_vs_capsule` static helpers | collide.c | ⬜ |
| 6 | Add `collide_rect_sphere/capsule` | collide.c | ⬜ |
| 7 | Add `collide_tri_sphere/capsule` | collide.c | ⬜ |
| 8 | Add `collide_pyramid_sphere/capsule` | collide.c | ⬜ |
| 9 | Add `collide_cylinder_sphere/capsule/box` | collide.c | ⬜ |
| 10 | Update 4 bool→int + add 12 new prototypes | physics.h | ⬜ |
| 11 | `query_rect/tri/pyramid` — `count +=` + sphere/capsule loops | contacts.c | ⬜ |
| 12 | `query_cylinder` — `count +=` + sphere/capsule/box loops | contacts.c | ⬜ |

---

## Final collision matrix (after this phase)

| A \ B | Plane | Sphere | Box | Capsule | Cylinder | Rect | Tri | Pyramid |
|-------|-------|--------|-----|---------|----------|------|-----|---------|
| Sphere | ✅ | ✅ | ✅ | ✅ | — | corner | corner | corner |
| Box | ✅ multi | — | ✅ | ✅ | — | — | — | — |
| Capsule | ✅ multi | — | ✅ | ✅ | — | corner | corner | corner |
| Cylinder | ✅ multi | ✅ | ✅ | ✅ | — | — | — | — |
| Rect | ✅ multi | corner | — | corner | — | — | — | — |
| Tri | ✅ multi | corner | — | corner | — | — | — | — |
| Pyramid | ✅ multi | corner | — | corner | — | — | — | — |

*corner = vertex-push only (shapes' corners push into round bodies; face hits from round
bodies onto flat shapes are not detected)*

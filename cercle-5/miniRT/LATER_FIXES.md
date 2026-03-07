# Later Fixes

Issues to address after the current implementation phase is complete.

---

## 1. Rotation display overflow in Transform panel

**File:** `srcs/gui/editor/transform_panel.c`  
**Function:** `draw_transform_panel`

**Problem:**  
`rotation.pitch`, `rotation.yaw`, and `rotation.roll` are stored in radians
with no clamping. When the camera is orbited repeatedly, the raw radian values
accumulate beyond the 2π boundary. Multiplying by `57.296` for display produces
values well above ±360°, which can eventually overflow `double` precision and
produce `nan`/`inf` in the printed string.

**Performance note:**  
`fmod` here is **not a performance concern**. This display code runs in the
overlay draw pass — completely outside the raytracing loop. It is called
exactly 3 times per visible frame, only when an object is selected. On modern
x86 CPUs, `fmod` compiles to a single `FPREM` instruction; it is essentially
free at this call frequency.

**Fix:**  
Inline the conversion + wrap in one expression per component, no helper needed:

```c
rot_deg.x = fmod(tr->rotation.pitch * 57.2957795, 360.0);
rot_deg.y = fmod(tr->rotation.yaw   * 57.2957795, 360.0);
rot_deg.z = fmod(tr->rotation.roll  * 57.2957795, 360.0);
if (rot_deg.x < 0.0) rot_deg.x += 360.0;
if (rot_deg.y < 0.0) rot_deg.y += 360.0;
if (rot_deg.z < 0.0) rot_deg.z += 360.0;
```

The `< 0` guards keep the value in `[0, 360)` when rotation is negative.
The underlying radian storage used by the renderer is never touched.

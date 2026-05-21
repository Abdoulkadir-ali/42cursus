/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 19:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/02 16:41:06 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "core.h"
#include <math.h>

static t_vec3 sample_object(const t_object *o, int seed)
{
    t_vec3 r;
    t_vec3 p;

    if (o->type == OBJ_SPHERE)
    {
        r.x = halton(seed, 2);
        r.y = halton(seed, 3);
        {
            float phi = 2.0f * (float)M_PI * r.x;
            float ct = 1.0f - 2.0f * r.y;
            float st = sqrtf(fmaxf(0.0f, 1.0f - ct * ct));
            p = v3(st * cosf(phi), st * sinf(phi), ct);
        }
        return (v3_add(o->u.sph.center, v3_mul(p, o->u.sph.radius)));
    }
    if (o->type == OBJ_BOX)
    {
        r.x = halton(seed, 2) * 2.0f - 1.0f;
        r.y = halton(seed, 3) * 2.0f - 1.0f;
        r.z = halton(seed, 5) * 2.0f - 1.0f;
        p = v3_add(o->u.box.center,
            v3_add(v3_mul(o->u.box.u, r.x * o->u.box.he.x),
            v3_add(v3_mul(o->u.box.v, r.y * o->u.box.he.y),
                   v3_mul(o->u.box.w, r.z * o->u.box.he.z))));
        return (p);
    }
    return (object_center(o));
}

static float specular_term(const t_hit *h, const t_vec3 ldir,
        const t_vec3 view)
{
    t_vec3 half;
    float spec;

    half = v3_norm(v3_add(ldir, view));
    spec = powf(fmaxf(0.0f, v3_dot(h->n, half)), h->mat->shininess);
    return (spec * h->mat->ks * (1.0f - h->mat->roughness * 0.5f));
}

static t_vec3 shade_emitter_sample(const t_app *app, const t_object *o,
        const t_hit *h, const t_vec3 albedo,
        size_t sample_idx, size_t n_samples)
{
    t_vec3 lpos;
    t_vec3 ldir;
    t_vec3 ec;
    t_vec3 sample_out;
    float ldist;
    float ndotl;
    float atten;
    float power;
    t_ray sh;

    power = 0.0f;
    if (app->set.rt.blackbody)
    {
        t_vec3 bb = emissive_color(&o->mat);
        power += bb.x + bb.y + bb.z;
    }
    if (o->mat.emit_power > 0.0f)
        power += o->mat.emit_power;
    if (power < 0.01f)
        return (v3(0, 0, 0));
    sample_out = v3(0, 0, 0);
    lpos = (n_samples > 1)
        ? sample_object(o, sample_idx + app->accum_samples)
        : object_center(o);
    ldir = v3_sub(lpos, h->p);
    ldist = v3_len(ldir);
    if (ldist < 1e-4f)
        return (v3(0, 0, 0));
    ldir = v3_mul(ldir, 1.0f / ldist);
    ndotl = v3_dot(h->n, ldir);
    if (ndotl <= 0.0f)
        return (v3(0, 0, 0));
    if (app->set.rt.shadows && power < app->set.rt.shadow_ray_gate)
    {
        sh.o = v3_add(h->p, v3_mul(h->n, EPSILON * 4.0f));
        sh.d = ldir;
        if (scene_occluded(app, &sh, ldist - EPSILON))
            return (v3(0, 0, 0));
    }
    atten = app->set.rt.emit_mult / (1.0f + 0.1f * ldist + 0.05f * ldist * ldist);
    if (app->set.rt.blackbody)
        ec = emissive_color(&o->mat);
    else
        ec = v3(0, 0, 0);
    if (o->mat.emit_power > 0.0f)
        ec = v3_add(ec, v3_mul(o->mat.emit_color, o->mat.emit_power));
    sample_out = v3_mul(ec, ndotl * atten);
    return (v3_hmul(albedo, v3_mul(sample_out, 1.0f / (float)n_samples)));
}

static t_vec3 phong_contribution(const t_app *app, const t_hit *h,
        const t_light *l, const t_vec3 albedo,
        const t_vec3 view)
{
    t_vec3 ldir;
    t_vec3 out;
    t_ray sh;
    float len;
    float ndotl;
    float s;

    ldir = v3_sub(l->pos, h->p);
    len = v3_len(ldir);
    if (len < 1e-6f)
        return (v3(0, 0, 0));
    ldir = v3_mul(ldir, 1.0f / len);
    ndotl = v3_dot(h->n, ldir);
    if (ndotl <= 0.0f)
        return (v3(0, 0, 0));
    if (app->set.rt.shadows)
    {
        sh.o = v3_add(h->p, v3_mul(h->n, EPSILON * 4.0f));
        sh.d = ldir;
        if (scene_occluded(app, &sh, len - EPSILON))
            return (v3(0, 0, 0));
    }
    out = v3_hmul(albedo, v3_mul(l->color, l->ratio * ndotl));
    s = specular_term(h, ldir, view);
    if (h->mat && h->mat->ks > 0.0f)
        out = v3_add(out, v3_mul(l->color, l->ratio * s));
    return (out);
}

t_vec3 phong_light(const t_app *app, const t_hit *h, t_vec3 albedo,
        const t_light *l, const t_vec3 view)
{
    return (phong_contribution(app, h, l, albedo, view));
}

t_vec3 emitter_lights(const t_app *app, const t_hit *h,
        t_vec3 albedo, t_vec3 view, int depth)
{
    t_vec3 out;
    const t_object *o;
    size_t idx;
    size_t n_samples;
    size_t k;

    (void)view;
    out = v3(0, 0, 0);
    if (!app->set.rt.emitters_as_lights || depth > 0 || app->scene.n_emit <= 0)
        return (out);
    n_samples = app->set.rt.soft_shadows ? app->set.rt.shadow_samples : 1;
    k = 0;
    while (k < app->scene.n_emit)
    {
        idx = app->scene.emit_idx[k++];
        if ((int)idx == h->obj_index || idx >= app->scene.n_bvh)
            continue ;
        o = &app->scene.bvh_objs[idx];
        out = v3_add(out, shade_emitter_sample(app, o, h, albedo, k * 100, n_samples));
    }
    return (out);
}

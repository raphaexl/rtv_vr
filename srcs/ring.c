/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ring.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 10:42:34 by ebatchas          #+#    #+#             */
/*   Updated: 2019/05/31 16:48:53 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt.h"

static float   ft_get_ring_caps(float t, t_ray *r, t_vec3 va, t_vec3 v);

static int		ft_min_ray(float t1, float t2, float *t)
{
	if (((t1 < t2 || t2 < 0.001) && t1 > 0.1) && (t1 < *t))
	{
		*t = t1;
		return (1);
	}
	else if (((t2 < t1 || t1 < 0.001) && t2 > 0.1) && (t2 < *t))
	{
		*t = t2;
		return (1);
	}
	else
		return (0);
}

t_object		*ft_ring_new(void)
{
	t_object	*new;

	if ((new = (t_object *)malloc(sizeof(*new))))
	{
		new->type = RING;
		new->name = "RING";
		new->pos = (t_vec3){0.0, 0.0, 0.0};
		new->translate = (t_vec3){0.0, 0.0, 0.0};
		new->rotate = (t_vec3){0.0, 0.0, 0.0};
		new->scale = (t_vec3){1.0f, 1.0f, 1.0f};
		new->material = (t_material){{ft_rand48(), ft_rand48(), ft_rand48()},
			{ft_rand48(), ft_rand48(), ft_rand48()}, 60.0, 0, 0, 0};
		new->e.ring.radius = 1.0;
		new->e.ring.radius2 = 1.0;
		new->e.ring.height = 1.0;
		new->e.ring.v = (t_vec3){0.0, 1.0, 0.0};
		new->next = NULL;
	}
	else
		ft_print_error("malloc error");
	return (new);
}

t_vec3			ft_normal_ring(t_ring *ring, t_vec3 p)
{
	p = ft_vec3_kmult(1.0 / ring->radius, p);
	return (ft_vec3(p.x, 0.001, p.z));
}

int				ft_ring_compute(t_object *p, t_intersect *in)
{
	t_ray	r;
	float	m;

	r = in->ray;
	r.start = ft_scale_vec3(r.start, p->scale, -1);
	r.start = ft_rotate_vec3(r.start, p->rotate, -1);
	r.start = ft_translate_vec3(r.start, p->translate, -1);
	r.dir = ft_scale_vec3(r.dir, p->scale, -1);
	r.dir = ft_rotate_vec3(r.dir, p->rotate, -1);
	if (!ft_ring_intersect(&p->e.ring, &r, &in->t))
		return (0);
	in->current = p;
	in->p = ft_vec3_sum(r.start, ft_vec3_kmult(in->t, r.dir));
	m = ft_vec3_dot(r.dir, p->e.ring.v) * in->t;
	m += ft_vec3_dot(r.start, p->e.ring.v);
	in->n = ft_vec3_sub(in->p, ft_vec3_kmult(m, p->e.ring.v));
	in->p = ft_translate_vec3(in->p, p->translate, 0);
	in->p = ft_rotate_vec3(in->p, p->rotate, 0);
	in->p = ft_scale_vec3(in->p, p->scale, 0);
	in->n = ft_rotate_vec3(in->n, p->rotate, 0);
	in->n = ft_scale_vec3(in->n, p->scale, -1);
	in->n = ft_vec3_normalized(in->n);
	return (1);
}


int				ft_ring_intersect(t_ring *c, t_ray *r, float *t)
{
	t_delta	d;
	t_vec3	dist;
	t_vec3  pa, va, alpha, beta;
float  t1, t2;

	pa = (t_vec3){0.0, 0.0, 0.0};
	va = ft_vec3_normalized(ft_vec3_sub(pa, c->v));
	dist = ft_vec3_sub(r->start, pa);
	alpha = ft_vec3_sub(r->dir, ft_vec3_kmult(ft_vec3_dot(r->dir, va), va));
	beta = ft_vec3_sub(dist, ft_vec3_kmult(ft_vec3_dot(dist, va), va));
	d.a = (alpha.x * alpha.x + alpha.y * alpha.y + alpha.z * alpha.z);
	d.b = 2.0 * (alpha.x * beta.x + alpha.y * beta.y + alpha.z * beta.z);
	d.c = (beta.x * beta.x + beta.y * beta.y + beta.z * beta.z) - c->radius2;
	d.delta = d.b * d.b - 4.0 * d.a * d.c;
	if (d.delta < 0.0)
		return (0);
	d.delta = sqrt(d.delta);
	t1 = ft_get_ring_caps((-d.b + d.delta) / (2.0 * d.a), r, va, c->v);
	t2 = ft_get_ring_caps((-d.b - d.delta) / (2.0 * d.a), r, va, c->v);		
	return (ft_min_ray(t1,
				t2, t));
}

float   ft_get_ring_caps(float t, t_ray *r, t_vec3 va, t_vec3 v)
{
t_vec3 q;
float	m1, m2;

if (t < 0)
return (INFINITY);
q = ft_vec3_sum(r->start, ft_vec3_kmult(t, r->dir));
m1 = ft_vec3_dot(va, q);
m2 = ft_vec3_dot(va, ft_vec3_sub(q, v));
if (m1 < 0.0 && m2 > 0)
return (t);
return (INFINITY);
}


int				ft_ring_intersect2(t_ring *c, t_ray *r, float *t)
{
	t_delta	d;
	t_vec3	x;
	float	m0;
	float	m1;
	float	t0;
	float	t1;
	
	x = r->start;
	d.a = ft_vec3_dot(r->dir, r->dir) - pow(ft_vec3_dot(r->dir, c->v), 2);
	d.b = 2.0 * (ft_vec3_dot(r->dir, x) - ft_vec3_dot(r->dir, c->v) * ft_vec3_dot(x, c->v));
	d.c = ft_vec3_dot(x, x) - pow(ft_vec3_dot(x, c->v), 2) - c->radius2;
	d.delta = d.b * d.b - 4.0 * d.a * d.c;
	if (d.delta < 0.0)
		return (0);
	d.delta = sqrt(d.delta);
	t0 = (-d.b + d.delta) / (2.0 * d.a);
	t1 = (-d.b - d.delta) / (2.0 * d.a);
	if (c->height <= 0)
		return (ft_min_ray(t0, t1, t));
	/*if (t0 > t1)
	{
		m0 = t0;
		t0 = t1;
		t1 = m0;
	}*/
	m0 = ft_vec3_dot(r->dir, c->v) * (t0);
	m0 += ft_vec3_dot(x, c->v);
	m1 = ft_vec3_dot(r->dir, c->v) * (t1);
	m1 += ft_vec3_dot(x, c->v);
	//if (m0 >= -c->height && m0 <= c->height)
	if (m0 > -c->height && m0 < c->height)
	{
		/*if (t0 < 1e-6 || t0 > *t)
			return (0);
		*t = t0;
		return (1);*/
		return (ft_min_ray(t0, t1, t));
	}
	else if (m1 > -c->height && m1 < c->height)
	{
		/*if (t0 > 1e-6 && t0 < *t)
		{
			*t = t0;
		return (1);
		}
			return (0);*/
		return (ft_min_ray(t1, t0, t));
	}
	return (0);
}



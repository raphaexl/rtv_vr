/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 15:50:51 by ebatchas          #+#    #+#             */
/*   Updated: 2019/09/23 11:26:32 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

t_ray	ft_transform_ray(t_object *p, t_ray *ro, int invert)
{
	t_ray	r;

	r.start = ft_scale_vec3(ro->start, p->scale, invert);
	r.start = ft_rotate_vec3(r.start, p->rotate, invert);
	r.start = ft_translate_vec3(r.start, p->translate, invert);
	r.dir = ft_scale_vec3(ro->dir, p->scale, invert);
	r.dir = ft_rotate_vec3(r.dir, p->rotate, invert);
	return (r);
}

int		ft_check_objects(t_object *p, t_hit *in)
{
	if (p->type == SPHERE && ft_sphere_compute(p, in))
		return (1);
	else if (p->type == CONE && ft_cone_compute(p, in))
		return (1);
	else if (p->type == CYLINDER && ft_cylindre_compute(p, in))
		return (1);
	else if (p->type == PLANE && ft_plane_compute(p, in))
		return (1);
	else if (p->type == DISK && ft_disk_compute(p, in))
		return (1);
	else if (p->type == BOX && ft_box_compute(p, in))
		return (1);
	else if (p->type == TORUS && ft_torus_compute(p, in))
		return (1);
	else if (p->type == CUBE && ft_cube_compute(p, in))
		return (1);
	else if (p->type == TRIANGLE && ft_triangle_compute(p, in))
		return (1);
	else if (p->type == PARALLELOGRAM && ft_parallelogram_compute(p, in))
		return (1);
	else if (p->type == RING && ft_ring_compute(p, in))
		return (1);
	else if (p->type == MESH && ft_mesh_compute(p, in))
		return (1);
	return (0);
}

int		ft_scene_intersect(t_scene *s, t_intersect *in)
{
	t_object	*p;
	t_ray		save;
	int			hit;

	hit = 0;
	p = s->obj;
	in->current = NULL;
	while (p)
	{
		save = in->ray;
		in->ray = ft_transform_ray(p, &save, -1);
		if (ft_check_objects(p, in))
			hit = 1;
		in->ray = save;
		p = p->next;
	}
	return (hit);
}

int		ft_check_shadows(t_object *p, t_ray r, t_hit *in)
{
	if (p->type == SPHERE && ft_sphere_intersect(&p->e.sphere, &r, &in->t))
		return (1);
	else if (p->type == CONE && ft_cone_intersect(&p->e.cone, &r, &in->t))
		return (1);
	else if (p->type == PLANE && ft_plane_intersect(&p->e.plane, &r,
				&in->t))
		return (1);
	else if (p->type == DISK && ft_disk_intersect(&p->e.disk, &r, &in->t))
		return (1);
	else if (p->type == CYLINDER && ft_cylindre_intersect(&p->e.cylinder, &r,
				&in->t))
		return (1);
	else if (p->type == BOX && ft_box_intersect(&p->e.box, &r, &in->t))
		return (1);
	else if (p->type == CUBE && ft_cube_intersect(&p->e.cube, &r, &in->t))
		return (1);
	else if (p->type == TORUS && ft_torus_intersect(&p->e.torus, &r, &in->t))
		return (1);
	else if (p->type == TRIANGLE && ft_triangle_intersect(&p->e.triangle, &r,
				&in->t))
		return (1);
	else if (p->type == PARALLELOGRAM && ft_parallelogram_intersect(&p->e.para,
				&r, &in->t))
		return (1);
	return (0);
}

int		ft_scene_intersectl(t_scene *s, t_intersect *in)
{
	t_object	*p;
	t_ray		r;
	int			i;

	i = 0;
	p = s->obj;
	while (p)
	{
		r = ft_transform_ray(p, &in->ray_light, 1);
		if (ft_check_shadows(p, r, in))
			return (1);
		else if (p->type == RING && ft_ring_intersect(&p->e.ring, &r, &in->t))
			return (1);
		else if (p->type == MESH)
		{
			i = -1;
			while (++i < p->e.mesh.size)
				if (ft_mesh_intersect(&p->e.mesh.triangles[i], &r, &in->t))
					return (1);
		}
		p = p->next;
	}
	return (0);
}

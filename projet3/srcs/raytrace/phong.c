/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 15:55:35 by ebatchas          #+#    #+#             */
/*   Updated: 2019/09/17 13:15:10 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

static t_col3	ft_ambient_light(t_col3 *diffuse, t_col3 *ambiant)
{
	t_col3		c;

	c.red = ambiant->red * diffuse->red;
	c.green = ambiant->green * diffuse->green;
	c.blue = ambiant->blue * diffuse->blue;
	return (c);
}

static t_col3	ft_diffuse_light(t_col3 *intens, t_col3 *diff, float lamb)
{
	t_col3	c;

	c.red = lamb * intens->red * diff->red * (1.0 / M_PI);
	c.green = lamb * intens->green * diff->green * (1.0 / M_PI);
	c.blue = lamb * intens->blue * diff->blue * (1.0 / M_PI);
	return (c);
}

static t_col3	ft_phong_shading(t_intersect *in, t_material *m, t_col3 *ints)
{
	float	reflect;
	t_vec3	tp;
	t_vec3	phong_dir;
	float	phong_term;

	reflect = 2.0f * ft_vec3_dot(in->ray_light.dir, in->n);
	tp = ft_vec3_kmult(reflect, in->n);
	phong_dir = ft_vec3_sub(in->ray_light.dir, tp);
	phong_term = fmax(ft_vec3_dot(phong_dir, in->ray.dir), 0.0f);
	phong_term = pow(phong_term, m->spec_pow) * m->albedo[1];
	return (ft_col3_mult(*ints, ft_col3_kmult(phong_term, m->specular)));
}

t_col3			ft_trace(t_intersect *in, t_material *m, t_light *l, t_col3 *a)
{
	t_col3	intensity;
	float	lambert;
	float	attenuation;
	t_col3	c;
	t_vec3	dist;

	c = (t_col3){0.0, 0.0, 0.0};
	intensity = l->diffuse;
	//printf("r = %.2f\tg = %.2f\tb = %.2f\n", intensity.red, intensity.green, intensity.blue);	
	attenuation = 1.0f; 
	c = ft_ambient_light(&m->diffuse, a);
	lambert = m->albedo[0] * ft_vec3_dot(in->n, in->ray_light.dir) ;/// M_PI;
	c = ft_col3_sum(c, ft_diffuse_light(&intensity, &m->diffuse, lambert));
	if (l->type == POINT_LIGHT)
	{
		dist = ft_vec3_sub(l->u.point.pos, in->p);
		attenuation =  1.0f / (l->u.point.constant + l->u.point.linear * in->t + l->u.point.quadratic * in->t * in->t);
	}
	else if (l->type == SPOT_LIGHT)
	{
		dist = ft_vec3_sub(l->u.spot.pos, in->p);
		attenuation =  1.0f / (l->u.spot.constant + l->u.spot.linear * in->t + l->u.spot.quadratic * in->t * in->t);
		float       theta   = ft_vec3_dot(ft_vec3_kmult(1.0 / in->t, dist), ft_vec3_normalized(ft_vec3_kmult(-1.0, l->u.spot.dir)));
		float       epsilon = l->u.spot.cut_off - l->u.spot.outer_cut_off;
		float       intensity = ft_clamp((theta - l->u.spot.outer_cut_off) / epsilon, 0.0f, 1.0f);
		attenuation =  attenuation * intensity;
	}
	return (ft_col3_kmult(attenuation, ft_col3_sum(c, ft_phong_shading(in, m, &intensity))));
}

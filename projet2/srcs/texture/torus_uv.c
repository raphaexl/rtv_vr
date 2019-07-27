/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   torus_uv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 12:24:39 by ebatchas          #+#    #+#             */
/*   Updated: 2019/07/20 12:26:40 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

void		ft_torus_uv(t_torus *t, t_vec3 n, t_vec3 p, t_uv *uv)
{
	(void)t;
	(void)n;
	uv->u = 0.5 + atan2(p.z, p.x) / (2.0 * M_PI);
	uv->v = 0.5 + atan2(p.y, sqrt(p.x * p.x + p.z * p.z) - t->radius1) / (2.0 * M_PI);
	//*v = 0.5 + atan2(p.y, sqrt(p.x * p.x + p.z * p.z) - t->radius1 / (2.0 * M_PI));
}

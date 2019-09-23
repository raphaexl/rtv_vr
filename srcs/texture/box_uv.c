/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box_uv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 13:10:10 by ebatchas          #+#    #+#             */
/*   Updated: 2019/09/21 18:24:43 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/rt.h"

void		ft_box_uv(t_box *b, t_vec3 n, t_vec3 p, t_uv *uv)
{
	(void)b;
	(void)n;
	if ((int)fabs(p.x) == 1)
	{
		uv->u = (p.z + 1.0) / 2.0;
		uv->v = (p.y + 1.0) / 2.0;
	}
	else if ((int)fabs(p.y) == 1)
	{
		uv->u = (p.x + 1.0) / 2.0;
		uv->v = (p.z + 1.0) / 2.0;
	}
	else
	{
		uv->u = (p.x + 1.0) / 2.0;
		uv->v = (p.y + 1.0) / 2.0;
	}
}

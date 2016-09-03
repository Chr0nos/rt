/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_default_triangle.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/24 17:35:21 by snicolet          #+#    #+#             */
/*   Updated: 2016/09/03 21:59:47 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"
#include "objects.h"
#include "mesh.h"

void	sda_default_triangle(t_rt *rt, t_obj *obj)
{
	t_triangle	*tri;

	(void)rt;
	tri = obj->content;
	if (!(obj->cfgbits & SDB_VERTEX0_UV))
		tri->v1.uv = (t_v2f){0.0f, 1.0f};
	if (!(obj->cfgbits & SDB_VERTEX1_UV))
		tri->v2.uv = (t_v2f){0.5f, 0.0f};
	if (!(obj->cfgbits & SDB_VERTEX2_UV))
		tri->v3.uv = (t_v2f){1.0f, 1.0f};
	if (!(obj->cfgbits & SDB_VERTEX0))
		tri->v1.pos = (t_v4d){0.0, 0.0, 0.0, 0.0};
	if (!(obj->cfgbits & SDB_VERTEX1))
		tri->v2.pos = (t_v4d){0.0, 0.0, 0.0, 0.0};
	if (!(obj->cfgbits & SDB_VERTEX2))
		tri->v3.pos = (t_v4d){0.0, 0.0, 0.0, 0.0};
}

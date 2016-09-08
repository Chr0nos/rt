/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_export_vertex.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/07 16:54:53 by snicolet          #+#    #+#             */
/*   Updated: 2016/09/08 22:27:00 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"
#include "mesh.h"
#include "libft.h"
#include "objects.h"

static void		sda_export_vertex_intern(t_vertex *v, char **str, t_obj *obj,
	const size_t uv_mask)
{
	str[0] = sda_double_short(ft_dtoa(v->pos.x, 6));
	str[1] = sda_double_short(ft_dtoa(v->pos.y, 6));
	str[2] = sda_double_short(ft_dtoa(v->pos.z, 6));
	if (obj->cfgbits & uv_mask)
	{
		str[3] = sda_double_short(ft_dtoa((double)v->uv.x, 6));
		str[4] = sda_double_short(ft_dtoa((double)v->uv.y, 6));
		str[5] = NULL;
	}
	else
		str[3] = NULL;
}

char			*sda_export_vertex0(t_obj *obj, t_sda_export *e)
{
	t_triangle	*tri;
	char		*str[6];
	char		*result;

	(void)e;
	if (obj->type != TRIANGLE)
		return (NULL);
	tri = obj->content;
	result = NULL;
	if (obj->cfgbits & SDB_VERTEX0)
	{
		sda_export_vertex_intern(&tri->v1, str, obj, SDB_VERTEX0_UV);
		result = ft_strunsplit((const char **)(size_t)str, ' ');
		ft_mfree(3, str[0], str[1], str[2]);
		if (obj->cfgbits & SDB_VERTEX0_UV)
			ft_mfree(2, str[3], str[4]);
	}
	return (result);
}

char			*sda_export_vertex1(t_obj *obj, t_sda_export *e)
{
	t_triangle	*tri;
	char		*str[6];
	char		*result;

	(void)e;
	if (obj->type != TRIANGLE)
		return (NULL);
	tri = obj->content;
	result = NULL;
	if (obj->cfgbits & SDB_VERTEX1)
	{
		sda_export_vertex_intern(&tri->v2, str, obj, SDB_VERTEX1_UV);
		result = ft_strunsplit((const char **)(size_t)str, ' ');
		ft_mfree(3, str[0], str[1], str[2]);
		if (obj->cfgbits & SDB_VERTEX1_UV)
			ft_mfree(2, str[3], str[4]);
	}
	return (result);
}

char			*sda_export_vertex2(t_obj *obj, t_sda_export *e)
{
	t_triangle	*tri;
	char		*str[6];
	char		*result;

	(void)e;
	if (obj->type != TRIANGLE)
		return (NULL);
	tri = obj->content;
	result = NULL;
	if (obj->cfgbits & SDB_VERTEX2)
	{
		sda_export_vertex_intern(&tri->v3, str, obj, SDB_VERTEX2_UV);
		result = ft_strunsplit((const char **)(size_t)str, ' ');
		ft_mfree(3, str[0], str[1], str[2]);
		if (obj->cfgbits & SDB_VERTEX2_UV)
			ft_mfree(2, str[3], str[4]);
	}
	return (result);
}

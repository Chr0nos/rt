/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_export_vertex.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/07 16:54:53 by snicolet          #+#    #+#             */
/*   Updated: 2016/08/07 17:16:40 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"
#include "mesh.h"
#include "libft.h"

static void	sda_export_vertex_intern(t_vertex *v, char **str, t_obj *obj)
{
	str[0] = ft_dtoa(v->pos.x, 6);
	str[1] = ft_dtoa(v->pos.y, 6);
	str[2] = ft_dtoa(v->pos.z, 6);
	str[3] = ft_dtoa(v->pos.w, 6);
	if (obj->cfgbits & SDB_VERTEX0_UV)
	{
		str[4] = ft_dtoa((double)v->uv.x, 6);
		str[5] = ft_dtoa((double)v->uv.y, 6);
	}
	else
		str[4] = NULL;
}

char	*sda_export_vertex0(t_obj *obj, t_sda_export *e)
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
		sda_export_vertex_intern(&tri->v1, str, obj);
		result = ft_strunsplit((const char **)(size_t)str, ' ');
		ft_mfree(4, str[0], str[1], str[2], str[3]);
		if (obj->cfgbits & SDB_VERTEX0_UV)
			ft_mfree(2, str[4], str[5]);
	}
	return (result);
}

char	*sda_export_vertex1(t_obj *obj, t_sda_export *e)
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
		sda_export_vertex_intern(&tri->v2, str, obj);
		result = ft_strunsplit((const char **)(size_t)str, ' ');
		ft_mfree(4, str[0], str[1], str[2], str[3]);
		if (obj->cfgbits & SDB_VERTEX1_UV)
			ft_mfree(2, str[4], str[5]);
	}
	return (result);
}

char	*sda_export_vertex2(t_obj *obj, t_sda_export *e)
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
		sda_export_vertex_intern(&tri->v3, str, obj);
		result = ft_strunsplit((const char **)(size_t)str, ' ');
		ft_mfree(4, str[0], str[1], str[2], str[3]);
		if (obj->cfgbits & SDB_VERTEX2_UV)
			ft_mfree(2, str[4], str[5]);
	}
	return (result);
}

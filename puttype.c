/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puttype.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/29 06:15:00 by snicolet          #+#    #+#             */
/*   Updated: 2016/08/14 18:25:20 by alhote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "libft.h"
#include "mesh.h"

t_type			rt_gettype(const char *str)
{
	const t_typecmp	types[] = {
		{CUBE, "CUBE"},
		{PLAN, "PLAN"},
		{SPHERE, "SPHERE"},
		{ROOT, "ROOT"},
		{SPOT, "SPOT"},
		{CAMERA, "CAMERA"},
		{POINTLIGHT, "POINTLIGHT"},
		{FACE, "FACE"},
		{EMPTY, "EMPTY"},
		{CONE, "CONE"},
		{CONE_INF, "CONE_INF"},
		{CYL, "CYL"},
		{SUNLIGHT, "SUNLIGHT"},
		{SETTING, "SETTING"},
		{TRIANGLE, "TRIANGLE"},
		{MESH, "MESH"}
	};
	int				p;

	p = 16;
	while ((p--) && (ft_strcmp(types[p].str, str)))
		;
	return ((p < 0) ? INVALID : types[p].type);
}

void			rt_puttype(int type, const int fd)
{
	const t_typecmp	types[] = {
		{CUBE, "CUBE"},
		{PLAN, "PLAN"},
		{SPHERE, "SPHERE"},
		{ROOT, "ROOT"},
		{SPOT, "SPOT"},
		{CAMERA, "CAMERA"},
		{POINTLIGHT, "POINTLIGHT"},
		{FACE, "FACE"},
		{EMPTY, "EMPTY"},
		{INVALID, "INVALID"},
		{CONE, "CONE"},
		{CONE_INF, "CONE_INF"},
		{CYL, "CYL"},
		{SUNLIGHT, "SUNLIGHT"},
		{SETTING, "SETTING"},
		{TRIANGLE, "TRIANGLE"},
		{MESH, "MESH"}
	};
	int				p;

	p = 17;
	while ((p--) && (types[p].type != type))
		;
	ft_putstr_fd((p < 0) ? "UNKNOW" : types[p].str, fd);
}

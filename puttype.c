/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puttype.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhote <alhote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/29 06:15:00 by snicolet          #+#    #+#             */
/*   Updated: 2016/08/16 17:43:02 by alhote           ###   ########.fr       */
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

char			*search_str_type(int type)
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
	if (p < 0)
		return (ft_strdup("UNKNOW"));
	else
		return (ft_strdup(types[p].str));
}

void			rt_puttype(int type, const int fd)
{
	char *str;

	str = search_str_type(type);
	ft_putstr_fd(str, fd);
	free(str);
}

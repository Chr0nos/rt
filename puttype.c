/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puttype.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/29 06:15:00 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/30 11:01:31 by dboudy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "libft.h"

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
		{SETTING, "SETTING"}
	};
	int				p;

	p = 14;
	while ((p--) && (ft_strcmp(types[p].str, str)))
		;
	return ((p < 0) ? INVALID : types[p].type);
}

void			rt_puttype(int type)
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
		{CYL, "CYLINDRE"},
		{SUNLIGHT, "SUNLIGHT"},
		{SETTING, "SETTING"}
	};
	int				p;

	p = 15;
	while ((p--) && (types[p].type != type))
		;
	ft_putstr((p < 0) ? "UNKNOW" : types[p].str);
}

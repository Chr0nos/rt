/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_setup_vertex.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/01 19:23:06 by snicolet          #+#    #+#             */
/*   Updated: 2016/08/24 20:10:22 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"
#include "objects.h"
#include "forms.h"
#include "mesh.h"
#include "libft.h"
#include "geo.h"

static void		*sda_vertex_x(t_obj *obj, unsigned char x)
{
	t_triangle	*tri;

	tri = obj->content;
	if (x == 0)
		return (&tri->v1);
	else if (x == 1)
		return (&tri->v2);
	else if (x == 2)
		return (&tri->v3);
	return (NULL);
}

static int		sda_setup_vertex(t_vertex *vertex, char **av, unsigned char n,
	t_obj *obj)
{
	const unsigned int ac = (unsigned int)ft_tabcount((void**)av);

	(void)n;
	if (!vertex)
		return (-1);
	vertex->pos = (t_v4d){ft_atod(av[0]), ft_atod(av[1]), ft_atod(av[2]), 0.0};
	if (ac >= 5)
	{
		vertex->uv = (t_v2f){
			geo_clamp((float)ft_atod(av[3]), 0.0f, 1.0f),
			geo_clamp((float)ft_atod(av[4]), 0.0f, 1.0f)};
		if (n == 0)
			obj->cfgbits |= SDB_VERTEX0_UV;
		else if (n == 1)
			obj->cfgbits |= SDB_VERTEX1_UV;
		else if (n == 2)
			obj->cfgbits |= SDB_VERTEX2_UV;
	}
	return (1);
}

int				sda_setup_vertex_0(t_sda *e, t_obj *obj, char **av)
{
	(void)e;
	return (sda_setup_vertex(sda_vertex_x(obj, 0), av, 0, obj));
}

int				sda_setup_vertex_1(t_sda *e, t_obj *obj, char **av)
{
	(void)e;
	return (sda_setup_vertex(sda_vertex_x(obj, 1), av, 1, obj));
}

int				sda_setup_vertex_2(t_sda *e, t_obj *obj, char **av)
{
	(void)e;
	return (sda_setup_vertex(sda_vertex_x(obj, 2), av, 2, obj));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_setup_vertex.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/01 19:23:06 by snicolet          #+#    #+#             */
/*   Updated: 2016/08/02 13:02:52 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"
#include "objects.h"
#include "forms.h"
#include "mesh.h"
#include "libft.h"

static void	*sda_vertex_x(t_obj *obj, unsigned char x)
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

static void	sda_setup_vertex(t_vertex *vertex, char **av)
{
	if (!vertex)
		return ;
	vertex->pos = (t_v4d){ft_atod(av[0]), ft_atod(av[1]), ft_atod(av[2]), 0.0};
}

int			sda_setup_vertex_0(t_sda *e, t_obj *obj, char **av)
{
	(void)e;
	sda_setup_vertex(sda_vertex_x(obj, 0), av);
	return (1);
}

int			sda_setup_vertex_1(t_sda *e, t_obj *obj, char **av)
{
	(void)e;
	sda_setup_vertex(sda_vertex_x(obj, 1), av);
	return (1);
}

int			sda_setup_vertex_2(t_sda *e, t_obj *obj, char **av)
{
	(void)e;
	sda_setup_vertex(sda_vertex_x(obj, 2), av);
	return (1);
}

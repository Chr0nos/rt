/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhote <alhote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/14 14:49:34 by alhote            #+#    #+#             */
/*   Updated: 2016/08/16 12:46:58 by alhote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "mesh.h"
#include <fcntl.h>
#include <unistd.h>
#include "sda.h"

t_vertex		*select_vertex_from_list(t_vertex_list *base, int id)
{
	while (--id && base)
		base = base->next;
	if (id)
		return (0);
	return (&base->vertex);
}

int				add_mesh_from_obj(t_obj *obj, const char *filepath)
{
	int				fd;
	char			*line;
	t_vertex_list	base;
	t_vertex_list	*select;
	char			**arg;
	t_obj			*t;

	if (!obj)
		return (1);
	if ((fd = open(filepath, O_RDONLY)) < 0)
		return (1);
	select = &base;
	while ((ft_get_next_line(fd, &line) > 0) && (line))
	{
		arg = ft_strsplit(line, ' ');
		if (line[0] == 'o')
			select = &base;
		if (line[0] == 'v')
		{
			select->vertex.pos = (t_v4d){ft_atod(arg[1]),
										ft_atod(arg[2]),
										ft_atod(arg[3]), 0.0};
			select->vertex.uv = (t_v2f){0.0, 0.0};
			if (!select->next)
				select->next = (t_vertex_list*)malloc(sizeof(t_vertex_list));
			select = select->next;
		}
		if (line[0] == 'f')
		{
			t = rt_factory_alloc(TRIANGLE, obj);
			((t_triangle*)(t->content))->v1 = *select_vertex_from_list(&base,
															ft_atoi(arg[1]));
			((t_triangle*)(t->content))->v2 = *select_vertex_from_list(&base,
															ft_atoi(arg[2]));
			((t_triangle*)(t->content))->v3 = *select_vertex_from_list(&base,
															ft_atoi(arg[3]));
		}
	}
	return (0);
}

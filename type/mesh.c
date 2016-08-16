/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhote <alhote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/14 14:49:34 by alhote            #+#    #+#             */
/*   Updated: 2016/08/16 18:44:39 by alhote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mesh.h"
#include <fcntl.h>
#include <unistd.h>
#include "sda.h"

int				add_mesh_from_obj(t_obj *obj, const char *filepath)
{
	int				fd;
	char			*line;
	char			**arg;
	t_obj			*t;
	t_vertex		*v;
	unsigned long	select_v;
	unsigned long	size_v;

	select_v = 0;
	size_v = 0;
	v = NULL;
	if (!obj)
		return (-1);
	if ((fd = open(filepath, O_RDONLY)) < 0)
		return (-2);
	obj = rt_factory_alloc(EMPTY, obj);
	obj->cfgbits |= SDB_NOEXPORT;
	while ((ft_get_next_line(fd, &line) > 0) && (line))
	{
		arg = ft_strsplit(line, ' ');
		if (line[0] == 'o')
			select_v = 0;
		if (line[0] == 'v')
		{
			if (select_v >= size_v || !v)
			{
				size_v += 3;
				v = (t_vertex*)ft_realloc(v,
					(unsigned int)(sizeof(t_vertex) * (size_v - 3)),
					(unsigned int)(sizeof(t_vertex) * size_v));
			}
			v[select_v].pos = (t_v4d){ft_atod(arg[1]),
										ft_atod(arg[2]),
										ft_atod(arg[3]), 0.0};
			v[select_v].uv = (t_v2f){0.0, 0.0};
			select_v++;
		}
		if (line[0] == 'f')
		{
			IFRET__(!(t = rt_factory_alloc(TRIANGLE, obj)), -3);
			((t_triangle*)(t->content))->v1 = v[ft_atoi(arg[1]) - 1];
			((t_triangle*)(t->content))->v2 = v[ft_atoi(arg[2]) - 1];
			((t_triangle*)(t->content))->v3 = v[ft_atoi(arg[3]) - 1];
			t->cfgbits |= (SDB_COLOR | SDB_VERTEX0 | SDB_VERTEX1 | SDB_VERTEX2);
			((t_triangle*)t->content)->color = 0xff0000;
			rt_box_update(t);
		}
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhote <alhote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/14 14:49:34 by alhote            #+#    #+#             */
/*   Updated: 2016/08/16 20:45:02 by snicolet         ###   ########.fr       */
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
	int 			ac;

	select_v = 0;
	size_v = 0;
	v = NULL;
	IFRET__(!obj, -1);
	IFRET__((fd = open(filepath, O_RDONLY)) < 0, -2);
	IFRET__(!(obj = rt_factory_alloc(EMPTY, obj)), -4);
	obj->cfgbits |= SDB_NOEXPORT;
	while ((ft_get_next_line(fd, &line) > 0) && (line))
	{
		sda_spliter(line, &arg, &ac);
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
		ft_free_tab(arg, (size_t)ac);
		ft_mfree(2, arg, line);
	}
	close(fd);
	return (0);
}

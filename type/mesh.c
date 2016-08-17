/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhote <alhote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/14 14:49:34 by alhote            #+#    #+#             */
/*   Updated: 2016/08/17 22:31:15 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mesh.h"
#include <fcntl.h>
#include <unistd.h>
#include "sda.h"

static unsigned int		clamp(int x, const unsigned int max)
{
	if (x < 1)
		return (1);
	return ((unsigned int)x > max) ? max : (unsigned int)x;
}

static int		parse_obj_f(t_sda_obj *s)
{
	t_obj			*t;
	const char		**arg = (const char **)(size_t)s->av;
	const int		x[3] = {ft_atoi(arg[1]), ft_atoi(arg[2]), ft_atoi(arg[3])};

	IFRET__(!(t = rt_factory_alloc(TRIANGLE, s->parent)), -3);
	((t_triangle*)(t->content))->v1 = s->v[clamp(x[0], (uint)s->size_v) - 1];
	((t_triangle*)(t->content))->v2 = s->v[clamp(x[1], (uint)s->size_v) - 1];
	((t_triangle*)(t->content))->v3 = s->v[clamp(x[2], (uint)s->size_v) - 1];
	t->cfgbits |= (SDB_COLOR | SDB_VERTEX0 | SDB_VERTEX1 | SDB_VERTEX2);
	((t_triangle*)t->content)->color = 0xff0000;
	//((t_triangle*)t->content)->reflect = 0xb0;
	//t->cfgbits |= SDB_REFLECT;
	rt_box_update(t);
	return (1);
}

static int		parse_obj_v(t_sda_obj *s)
{
	if ((s->select_v >= s->size_v) || (!s->v))
	{
		s->size_v += 3;
		s->v = (t_vertex*)ft_realloc(s->v,
			(unsigned int)(sizeof(t_vertex) * (s->size_v - 3)),
			(unsigned int)(sizeof(t_vertex) * s->size_v));
	}
	s->v[s->select_v].pos = (t_v4d){ft_atod(s->av[1]),
								ft_atod(s->av[2]),
								ft_atod(s->av[3]), 0.0};
	s->v[s->select_v].uv = (t_v2f){0.0, 0.0};
	s->select_v++;
	return (1);
}

inline static int	parse_obj(t_sda_obj *s, char *line)
{
	IFRET__(line[0] == '#', 0);
	IFRET__(!sda_spliter(line, &s->av, &s->ac), -2);
	if (!ft_strcmp(s->av[0], "o"))
		ft_printf("\t-Loading %s object..\n", s->av[1]);
	IFRET__(s->ac < 4, 1);
	IFRET__(!ft_strcmp(s->av[0], "v"), parse_obj_v(s));
	IFRET__(!ft_strcmp(s->av[0], "f"), parse_obj_f(s));
	return (1);
}

int				add_mesh_from_obj(t_obj *obj, const char *filepath)
{
	t_sda_obj		s;
	char			*line;
	int				fd;
	int				ret;

	IFRET__(!obj, -1);
	IFRET__((fd = open(filepath, O_RDONLY)) < 0, -2);
	IFRET__(!(obj = rt_factory_alloc(EMPTY, obj)), -4);
	s = (t_sda_obj){0, NULL, NULL, 0, 0, obj};
	obj->cfgbits |= SDB_NOEXPORT;
	ft_printf("Loading %s..\n", filepath);
	ret = 0;
	while ((ft_get_next_line(fd, &line) > 0) && (line))
	{
		if ((ret = parse_obj(&s, line)) < 0)
		{
			ft_putendl_fd("error: failed to parse .obj", 2);
			break ;
		}
		else if (ret != 0)
		{
			ft_free_tab(s.av, (size_t)s.ac);
			free(s.av);
		}
		free(line);
	}
	close(fd);
	return (ret);
}

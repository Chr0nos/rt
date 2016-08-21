/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhote <alhote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/14 14:49:34 by alhote            #+#    #+#             */
/*   Updated: 2016/08/21 17:37:44 by alhote           ###   ########.fr       */
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
	t_triangle		*c;
	const char		**arg = (const char **)(size_t)s->av;
	const char		*value[3];
	const int		v[3] = {ft_atoi(ft_strsplit(arg[1], '/')[0]),
	ft_atoi(ft_strsplit(arg[2], '/')[0]), ft_atoi(ft_strsplit(arg[3], '/')[0])};

	value[0] = ft_strsplit(arg[1], '/')[1];
	value[1] = ft_strsplit(arg[2], '/')[1];
	value[2] = ft_strsplit(arg[3], '/')[1];
	IFRET__(!(t = rt_factory_alloc(TRIANGLE, s->parent)), -3);
	c = t->content;
	c->v1.pos = s->v[clamp(v[0], (uint)s->size_v) - 1];
	c->v2.pos = s->v[clamp(v[1], (uint)s->size_v) - 1];
	c->v3.pos = s->v[clamp(v[2], (uint)s->size_v) - 1];
	if (value[0] && value[1] && value[2] && s->uv)
	{
		c->v1.uv = s->uv[clamp(ft_atoi(value[0]), (uint)s->size_uv) - 1];
		c->v2.uv = s->uv[clamp(ft_atoi(value[1]), (uint)s->size_uv) - 1];
		c->v3.uv = s->uv[clamp(ft_atoi(value[2]), (uint)s->size_uv) - 1];
		t->cfgbits |= SDB_VERTEX0_UV | SDB_VERTEX1_UV | SDB_VERTEX2_UV;
	}
	free(value);
	value[0] = ft_strsplit(arg[1], '/')[2];
	value[1] = ft_strsplit(arg[2], '/')[2];
	value[2] = ft_strsplit(arg[3], '/')[2];
	if (value[0] && value[1] && value[2] && s->n)
	{
		c->v1.normal = s->n[clamp(ft_atoi(value[0]), (uint)s->size_n) - 1];
		c->v2.normal = s->n[clamp(ft_atoi(value[1]), (uint)s->size_n) - 1];
		c->v3.normal = s->n[clamp(ft_atoi(value[2]), (uint)s->size_n) - 1];
	}
	free(value);
	t->cfgbits |= (SDB_COLOR | SDB_VERTEX0 | SDB_VERTEX1 | SDB_VERTEX2 |
		SDB_REFLECT);
	c->color = s->mesh->color;
	if ((c->texture = s->mesh->texture))
		t->cfgbits |= SDB_TEXTURE;
	if ((c->normal = s->mesh->normal))
		t->cfgbits |= SDB_NORMAL;
	c->reflect = s->mesh->reflect;
	rt_box_update(t);
	return (1);
}

static int		parse_obj_n(t_sda_obj *s)
{
	if ((s->select_n >= s->size_n) || (!s->n))
	{
		s->size_n += 3;
		s->n = (t_v4d*)ft_realloc(s->n,
			(unsigned int)(sizeof(t_v4d) * (s->size_n - 3)),
			(unsigned int)(sizeof(t_v4d) * s->size_n));
	}
	s->n[s->select_n] = (t_v4d){ft_atod(s->av[1]),
								ft_atod(s->av[2]),
								ft_atod(s->av[3]), 0.0};
	s->select_n++;
	return (1);
}

static int		parse_obj_uv(t_sda_obj *s)
{
	if ((s->select_uv >= s->size_uv) || (!s->uv))
	{
		s->size_uv += 3;
		s->uv = (t_v2f*)ft_realloc(s->uv,
			(unsigned int)(sizeof(t_v2f) * (s->size_uv - 3)),
			(unsigned int)(sizeof(t_v2f) * s->size_uv));
	}
	s->uv[s->select_uv] = (t_v2f){(float)ft_atod(s->av[1]),
								(float)ft_atod(s->av[2])};
	s->select_uv++;
	return (1);
}

static int		parse_obj_v(t_sda_obj *s)
{
	if ((s->select_v >= s->size_v) || (!s->v))
	{
		s->size_v += 3;
		s->v = (t_v4d*)ft_realloc(s->v,
			(unsigned int)(sizeof(t_v4d) * (s->size_v - 3)),
			(unsigned int)(sizeof(t_v4d) * s->size_v));
	}
	s->v[s->select_v] = (t_v4d){ft_atod(s->av[1]),
								ft_atod(s->av[2]),
								ft_atod(s->av[3]), 0.0};
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
	IFRET__(!ft_strcmp(s->av[0], "vn"), parse_obj_n(s));
	IFRET__(!ft_strcmp(s->av[0], "vt"), parse_obj_uv(s));
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
	s = (t_sda_obj){0, NULL, NULL, NULL, NULL, 0, 0, 0, 0, 0, 0, NULL,
		obj->content};
	IFRET__(!(obj = rt_factory_alloc(EMPTY, obj)), -4);
	s.parent = obj;
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
	if (s.v)
		free(s.v);
	if (s.uv)
		free(s.uv);
	if (s.v)
		free(s.n);
	close(fd);
	return (ret);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhote <alhote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/14 14:49:34 by alhote            #+#    #+#             */
/*   Updated: 2016/09/11 21:09:57 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mesh.h"
#include <fcntl.h>
#include <unistd.h>
#include "sda.h"
#include "parser.h"

static void				parse_obj_f_setuv(t_obj *t, t_sda_obj *s, t_triangle *c)
{
	char		**split[3];

	if (!s->uv)
		return ;
	split[0] = ft_strsplit(s->av[1], '/');
	split[1] = ft_strsplit(s->av[2], '/');
	split[2] = ft_strsplit(s->av[3], '/');
	if (parse_obj_checksplit(split, 2) < 0)
		return ;
	if ((split[0][1]) && (split[1][1]) && (split[2][1]))
	{
		c->v1.uv = s->uv[obj_max(ft_atoi(split[0][1]), (uint)s->size_uv) - 1];
		c->v2.uv = s->uv[obj_max(ft_atoi(split[1][1]), (uint)s->size_uv) - 1];
		c->v3.uv = s->uv[obj_max(ft_atoi(split[2][1]), (uint)s->size_uv) - 1];
		t->cfgbits |= SDB_VERTEX0_UV | SDB_VERTEX1_UV | SDB_VERTEX2_UV;
	}
	ft_freesplit_multi(split, 3);
}

static void				parse_obj_f_normal(t_sda_obj *s, t_triangle *c)
{
	char		**split[3];

	if (!s->n)
		return ;
	split[0] = ft_strsplit(s->av[1], '/');
	split[1] = ft_strsplit(s->av[2], '/');
	split[2] = ft_strsplit(s->av[3], '/');
	if (parse_obj_checksplit(split, 3) < 0)
		return ;
	if ((split[0][2]) && (split[1][2]) && (split[2][2]))
	{
		c->v1.normal = s->n[obj_max(ft_atoi(split[0][2]), (uint)s->size_n) - 1];
		c->v2.normal = s->n[obj_max(ft_atoi(split[1][2]), (uint)s->size_n) - 1];
		c->v3.normal = s->n[obj_max(ft_atoi(split[2][2]), (uint)s->size_n) - 1];
	}
	ft_freesplit_multi(split, 3);
}

/*
** this function will be called on all lines starting with "f"
*/

int						parse_obj_f(t_sda_obj *s)
{
	t_obj			*t;
	t_triangle		*c;
	char			**split[3];
	int				v[3];

	split[0] = ft_strsplit(s->av[1], '/');
	split[1] = ft_strsplit(s->av[2], '/');
	split[2] = ft_strsplit(s->av[3], '/');
	if (parse_obj_checksplit(split, 1) < 0)
		return (-1);
	v[0] = ft_atoi(split[0][0]);
	v[1] = ft_atoi(split[1][0]);
	v[2] = ft_atoi(split[2][0]);
	ft_freesplit_multi(split, 3);
	IFRET__(!(t = rt_factory_alloc(TRIANGLE, s->parent)), -3);
	c = t->content;
	c->v1.pos = s->v[obj_max(v[0], (uint)s->size_v) - 1];
	c->v2.pos = s->v[obj_max(v[1], (uint)s->size_v) - 1];
	c->v3.pos = s->v[obj_max(v[2], (uint)s->size_v) - 1];
	parse_obj_f_setuv(t, s, c);
	parse_obj_f_normal(s, c);
	parse_obj_setcfgbits(t, s, c);
	rt_box_update(t);
	return (1);
}

/*
** return: < 0 in case of error, else 1
*/

static int				parse_obj_init(t_sda_obj *s, t_obj *obj,
	const char *filepath, int *fd)
{
	IFRET__(!obj, -1);
	IFRET__((*fd = open(filepath, O_RDONLY)) < 0, -2);
	*s = (t_sda_obj){0, NULL, NULL, NULL, NULL, 0, 0, 0, 0, 0, 0, NULL,
		obj->content, obj};
	if (!(obj = rt_factory_alloc(EMPTY, obj)))
	{
		close(*fd);
		return (-4);
	}
	obj->cfgbits |= SDB_NOEXPORT;
	s->parent = obj;
	sda_default_texture(NULL, s->mesh_obj);
	if (!(s->mesh_obj->cfgbits & SDB_NORMAL))
		s->mesh->normal = NULL;
	return (1);
}

int						parse_obj(t_obj *obj, const char *filepath)
{
	t_sda_obj		s;
	char			*line;
	int				fd;
	int				ret;

	IFRET__(parse_obj_init(&s, obj, filepath, &fd) < 0, -1);
	ret = 0;
	while ((ft_get_next_line(fd, &line) > 0) && (line))
	{
		if ((ret = parse_obj_dispatch(&s, line)) < 0)
		{
			ft_putendl_fd("error: failed to parse .obj", 2);
			break ;
		}
		else if (ret != 0)
			ft_freesplit(s.av);
		free(line);
	}
	free(line);
	ft_mfree(3, s.v, s.uv, s.n);
	close(fd);
	return (ret);
}

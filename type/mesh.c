/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhote <alhote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/14 14:49:34 by alhote            #+#    #+#             */
/*   Updated: 2016/08/15 14:16:41 by alhote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "mesh.h"
#include <fcntl.h>
#include <unistd.h>

int				rt_mesh_inter(t_obj *obj, t_ray *r, t_v4d *i)
{
	t_mesh		*m;
	t_v4d		to_keep;
	int			touched;
	double		dist;
	t_obj		objtri;

	touched = 0;
	to_keep = *i;
	dist = (double)INFINITY;
	m = obj->content;
	while(m)
	{
		objtri.content = m->triangle;
		if (m->triangle && rt_triangle_inter(&objtri, r, i) &&
			geo_distv4(r->start, *i) < dist)
		{
			touched = 1;
			dist = geo_distv4(r->start, *i);
			((t_mesh*)(obj->content))->normal = rt_triangle_normale(&objtri, i);
		}
		m = m->next;
	}
	r->lenght = dist;
	*i = to_keep;
	return (touched);
}

t_v4d			rt_mesh_normale(t_obj *obj, t_v4d *v)
{
	(void)v;
	return (((t_mesh*)(obj->content))->normal);
}

t_vertex		*select_vertex_from_list(t_vertex_list *base, int id)
{
	while(--id && base)
		base = base->next;
	if (id)
		return (0);
	return (&base->vertex);
}

int				obj_file_to_mesh(t_v4d pos, t_mesh *mesh, const char *filepath)
{
	int				fd;
	char			*line;
	t_vertex_list	base;
	t_vertex_list	*select;
	char			**arg;

	if (!mesh)
		return (1);
	if ((fd = open(filepath, O_RDONLY)) < 0)
		return (1);
	select = &base;
	mesh->triangle = (t_triangle*)malloc(sizeof(t_triangle));
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
			select->next = (t_vertex_list*)malloc(sizeof(t_vertex_list));
			select = select->next;
		}
		if (line[0] == 'f')
		{
			mesh->triangle->v1 = *select_vertex_from_list(&base, ft_atoi(arg[1]));
			mesh->triangle->v2 = *select_vertex_from_list(&base, ft_atoi(arg[2]));
			mesh->triangle->v3 = *select_vertex_from_list(&base, ft_atoi(arg[3]));
			mesh->triangle->v1.pos = geo_addv4(pos, mesh->triangle->v1.pos);
			mesh->triangle->v2.pos = geo_addv4(pos, mesh->triangle->v2.pos);
			mesh->triangle->v3.pos = geo_addv4(pos, mesh->triangle->v3.pos);
			mesh->next = (t_mesh*)malloc(sizeof(t_mesh));
			mesh = mesh->next;
			mesh->triangle = (t_triangle*)malloc(sizeof(t_triangle));
			mesh->next = NULL;
		}
	}
	return (0);
}

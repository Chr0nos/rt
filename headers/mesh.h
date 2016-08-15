/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhote <alhote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/01 17:51:04 by alhote            #+#    #+#             */
/*   Updated: 2016/08/15 14:16:49 by alhote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESH_H
# define MESH_H
# include "t_v4.h"
# include "texture.h"

typedef struct			s_vertex
{
	t_v4d				pos;
	t_v2f				uv;
}						t_vertex;

typedef struct			s_triangle
{
	unsigned int		color;
	t_vertex			v1;
	t_vertex			v2;
	t_vertex			v3;
	t_texture			*texture;
	t_texture			*normal;
}						t_triangle;

typedef struct			s_vertex_list
{
	t_vertex					vertex;
	struct s_vertex_list		*next;
}						t_vertex_list;

typedef struct			s_mesh
{
	t_triangle			*triangle;
	t_v4d				normal;
	struct s_mesh		*next;
}						t_mesh;

int						obj_file_to_mesh(t_v4d pos, t_mesh *mesh, const char *filepath);
t_vertex				*select_vertex_from_list(t_vertex_list *base, int id);
#endif

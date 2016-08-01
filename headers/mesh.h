/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhote <alhote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/01 17:51:04 by alhote            #+#    #+#             */
/*   Updated: 2016/08/01 18:07:08 by alhote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESH_H
# define MESH_H

typedef struct			s_vertex
{
	t_v4d				pos;
}						t_vertex;

typedef struct			s_triangle
{
	unsigned int		color;
	t_vertex			v1;
	t_vertex			v2;
	t_vertex			v3;
}						t_triangle;

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hantlowt <hantlowt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/01 17:51:04 by hantlowt          #+#    #+#             */
/*   Updated: 2016/08/01 17:56:18 by hantlowt         ###   ########.fr       */
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
	t_vertex			v1;
	t_vertex			v2;
	t_vertex			v3;
	unsigned int		color;
}						t_v2d;

#endif

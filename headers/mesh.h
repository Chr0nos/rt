/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhote <alhote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/01 17:51:04 by alhote            #+#    #+#             */
/*   Updated: 2016/08/01 19:22:28 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESH_H
# define MESH_H
# include "t_v4.h"

typedef struct			s_vertex
{
	t_v4d				pos;
}						t_vertex;

typedef struct			s_triangle
{
	unsigned int		color;
	t_v4d				v1;
	t_v4d				v2;
	t_v4d				v3;
}						t_triangle;

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forms.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 22:01:52 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/21 19:59:55 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORMS_H
# define FORMS_H
# include "draw.h"

typedef unsigned int	t_uint;
typedef t_vector		t_v3f;
typedef t_matrix		t_mattf;

typedef enum			e_type
{
	ROOT = 0,
	CUBE = 1,
	PLAN = 2,
	SPHERE = 3,
	CAMERA = 4,
	EMPTY = 5
}						t_type;

typedef struct			s_cube
{
	unsigned int		color;
	float				size;
}						t_cube;

typedef struct			s_plan
{
	unsigned int		color;
}						t_plan;

typedef struct			s_sphere
{
	unsigned int		color;
	float				radius;
}						t_sphere;

typedef struct			s_camera
{
	t_mattf				rtrans;
}						t_camera;

typedef struct			s_obj
{
	t_type				type;
	t_uint				id;
	t_mattf				trans;
	t_v3f				bounds[6];
	struct s_obj		*parent;
	struct s_obj		*childs;
	struct s_obj		*next;
	void				*content;
}						t_obj;

#endif

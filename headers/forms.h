/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forms.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qloubier <qloubier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 22:01:52 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/05 00:25:20 by qloubier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORMS_H
# define FORMS_H
# include "draw.h"

typedef unsigned int	t_uint;
typedef t_point			t_v2i;
typedef t_vector		t_v3f;
typedef t_m4			t_mattf;

typedef enum			e_type
{
	ROOT = 1,
	CUBE = 1 << 1,
	PLAN = 1 << 2,
	SPHERE = 1 << 3,
	CAMERA = 1 << 4,
	EMPTY = 1 << 5,
	SPOT = 1 << 6,
	POINTLIGHT = 1 << 7,
	RADIUS = SPHERE | CUBE
}						t_type;

enum					e_stop
{
	OK = 0,
	STOP_NODE = 1,
	STOP_ALL = 1 << 1
};

typedef struct			s_v2d
{
	double				x;
	double				y;
}						t_v2d;

typedef struct			s_typesize
{
	t_type				type;
	size_t				size;
}						t_typesize;

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
	t_v2d				steppx;
	t_v4d				rayfix;
	t_v4d				rayreset;
	t_v4d				raypos;
	t_v4d				mdirx;
	t_v4d				mdiry;
	float				fov;
	float				fovy;
}						t_camera;

typedef struct			s_ray
{
	t_v4d				start;
	t_v4d				dir;
	double				limit;
	unsigned int		color;
}						t_ray;

typedef struct			s_box
{
	float				xmin;
	float				xmax;
	float				ymin;
	float				ymax;
	float				zmin;
	float				zmax;
}						t_box;

typedef struct			s_obj
{
	t_type				type;
	t_uint				id;
	t_mattf				trans;
	t_v4d				rotation;
	t_box				bounds;
	t_box				hitbox;
	struct s_obj		*parent;
	struct s_obj		*childs;
	struct s_obj		*next;
	void				*content;
}						t_obj;

#endif

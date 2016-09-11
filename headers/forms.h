/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forms.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhote <alhote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/30 18:19:03 by alhote            #+#    #+#             */
/*   Updated: 2016/09/11 18:02:14 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORMS_H
# define FORMS_H
# include "draw.h"
# include "texture.h"
# include "forms_bits.h"

typedef unsigned int	t_uint;
typedef t_m4			t_mattf;

enum					e_stop
{
	OK = 0,
	STOP_NODE = 1,
	STOP_ALL = 1 << 1
};

typedef struct			s_typecmp
{
	t_type				type;
	const char			*str;
}						t_typecmp;

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
	t_uint				color;
	float				size;
	t_texture			*texture;
	t_texture			*normal;
	unsigned char		reflect;
}						t_cube;

typedef struct			s_plan
{
	t_uint				color;
	t_texture			*texture;
	t_texture			*normal;
	t_texture			*heightmap;
	unsigned char		reflect;
}						t_plan;

typedef struct			s_cone
{
	t_uint				color;
	float				size;
	t_v4d				angle;
	unsigned char		reflect;
	t_texture			*texture;
	t_texture			*normal;
}						t_cone;

typedef struct			s_cone_inf
{
	t_uint				color;
	float				size;
	unsigned char		reflect;
}						t_cone_inf;

typedef struct			s_cyl
{
	t_uint				color;
	float				radius;
	unsigned char		reflect;
}						t_cyl;

typedef struct			s_tore
{
	t_uint				color;
	float				radius;
	float				radius_2;
	unsigned char		reflect;
}						t_tore;

typedef struct			s_sphere
{
	t_uint				color;
	float				radius;
	t_texture			*texture;
	t_texture			*normal;
	unsigned char		reflect;
}						t_sphere;

typedef struct			s_plight
{
	t_uint				color;
	double				intensity;
}						t_plight;

typedef struct			s_camera
{
	t_mattf				rtrans;
	t_v2d				steppx;
	t_v4d				rayfix;
	t_v4d				rayreset;
	t_v4d				raypos;
	t_v4d				mdirx;
	t_v4d				mdiry;
	t_v4d				origin_rot;
	t_m4				origin;
	double				fov;
	double				fovx;
}						t_camera;

typedef struct			s_intersect
{
	double				len_in;
	double				len_out;
	t_v4d				in;
	t_v4d				out;
	char				flags;
}						t_intersect;

typedef struct			s_ray
{
	t_v4d				start;
	t_v4d				dir;
	double				limit;
	double				lenght;
	t_uint				color;
	int					count;
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

typedef struct			s_setting
{
	unsigned int		color;
	float				size;
	t_texture			*skybox;
	unsigned char		reflect;
	double				al;
	unsigned int		bgcolor;
}						t_setting;

typedef enum			e_limit_type
{
	LIM_X = 1,
	LIM_Y = 1 << 1,
	LIM_Z = 1 << 2,
	NEGATE = 1 << 3
}						t_limtyp;

typedef struct			s_limiter
{
	int					axe;
	t_v3d				limit;
	struct s_limiter	*next;
}						t_limit;

#endif

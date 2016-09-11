/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shaders.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhote <alhote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/21 14:34:04 by alhote            #+#    #+#             */
/*   Updated: 2016/09/07 01:23:26 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHADERS_H
# define SHADERS_H
# include "rt.h"
# include "render.h"
# include "blend.h"
# define SHT t_shatyp
# define SHF t_shafnc

/*
** used in rt_render_ray
*/

# define MAX_SHADERS 16

typedef struct s_render	t_render;

typedef enum		e_shader_type
{
	NO_SHADER = 0,
	LIGHT_SHADER = 1,
	INTERSECT_SHADER = 1 << 1,
	SCREEN_SHADER = 1 << 2
}					t_shatyp;

typedef enum		e_shader_func
{
	NONE = 0,
	EXEC = 1,
	BLEND = 2,
	INTERSECT = 3,
}					t_shafnc;

typedef struct		s_shader
{
	void			*(*sh_get)(struct s_shader *, SHT, SHF);
	int				enabled;
	unsigned int	color_render;
	unsigned int	color_base;
	void			*content;
	unsigned int	(*blend)(unsigned int a, unsigned int b);
	void			(*exec)(struct s_shader *s,
					t_render *r, t_obj *o, unsigned int *color);
	struct s_shader	*next;
}					t_shader;

typedef struct		s_shaders
{
	int				(*vertex_shader)(t_render *r, t_obj *o);
	t_shader		*shader;
}					t_shaders;

typedef struct		s_shader_uvfunc
{
	t_type			type;
	t_v2f			(*uv)(const t_render *);
}					t_shader_uvfunc;

void				*shader_get(t_shader *s, SHT t, SHF f);
t_shaders			*shaders_init(void);
t_shader			*shader_init(t_shaders *shaders,
	void (*shader)(t_shader *s, t_render *r,
	t_obj *o, unsigned int *color), unsigned int color,
	unsigned int (*blend)(unsigned int a, unsigned int b));
int					shaders_exec(t_shaders *s, t_render *r, t_obj *o,
					unsigned int *colors_renders);
unsigned int		shaders_compute_color(t_shaders *s, unsigned int color
										, unsigned int *colors_renders);
void				shaders_disable_nexts(t_shader *s);
double				rt_reflection(t_render *r, t_obj *light);
void				rt_light_pow(t_shader *s, t_render *r, t_obj *light,
								unsigned int *color_render);
void				rt_specular_pow(t_shader *s, t_render *r, t_obj *light,
								unsigned int *color_render);
void				shader_shadow(t_shader *s, t_render *r, t_obj *light,
								unsigned int *color_render);
void				shader_texture(t_shader *s, t_render *r, t_obj *light,
								unsigned int *color_render);
void				shader_normalmap(t_shader *s, t_render *r, t_obj *light,
								unsigned int *color_render);
void				shader_reflection(t_shader *s, t_render *r, t_obj *light,
								unsigned int *color_render);
void				shader_damier(t_shader *s, t_render *r, t_obj *light,
								unsigned int *color_render);
unsigned int		shader_color_texture_intersection(const t_render *r);
unsigned int		shader_color_normal_intersection(const t_render *r);
void				shaders_activate_only(t_shaders *s, unsigned int n);
void				shaders_activate_all(t_shaders *s);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shaders.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhote <alhote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/21 14:34:04 by alhote            #+#    #+#             */
/*   Updated: 2016/07/13 15:06:24 by alhote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHADERS_H
# define SHADERS_H
# include "rt.h"
# include "render.h"
# define A(C) ((C & 0xFF000000) >> 24)
# define R(C) ((C & 0x00FF0000) >> 16)
# define G(C) ((C & 0x0000FF00) >> 8)
# define B(C) (C & 0x000000FF)

typedef struct		s_shader
{
	int				enabled;
	unsigned int	color_render;
	unsigned int	color_base;
	void			*content;
	unsigned int	(*blend)(unsigned int a, unsigned int b);
	void			(*exec)(struct s_shader *s,
					t_render *r, t_obj *o);
	struct s_shader	*next;
}					t_shader;

typedef struct		s_shaders
{
	int				(*vertex_shader)(t_render *r, t_obj *o);
	t_shader		*shader;
}					t_shaders;

t_shaders			*init_shaders(void);
t_shader			*init_shader(t_shaders *shaders,
	void (*shader)(t_shader *s, t_render *r,
	t_obj *o), void *data, unsigned int color, unsigned int
	(*blend)(unsigned int a, unsigned int b));
int					exec_fshaders(t_shaders *s, t_render *r, t_obj *o);
unsigned int		compute_color_shaders(t_shaders *s);
void			disable_nexts(t_shader *s);
double				rt_reflection(t_render *r, t_obj *light);
void				rt_light_pow(t_shader *s, t_render *r, t_obj *light);
void				rt_specular_pow(t_shader *s, t_render *r, t_obj *light);
void				shader_damier(t_shader *s, t_render *r, t_obj *light);
void				shader_ambiant(t_shader *s, t_render *r, t_obj *light);
void				shader_shadow(t_shader *s, t_render *r, t_obj *light);
unsigned int		blend_normal(unsigned int a, unsigned int b);
unsigned int		blend_add(unsigned int a, unsigned int b);
unsigned int		blend_sub(unsigned int a, unsigned int b);
unsigned int		blend_multiply(unsigned int a, unsigned int b);
unsigned int		blend_lighten(unsigned int a, unsigned int b);
unsigned int		blend_darken(unsigned int a, unsigned int b);
unsigned int		blend_overlay(unsigned int a, unsigned int b);
void				shaders_activate_only(t_shaders *s, unsigned int n);
void				shaders_activate_all(t_shaders *s);
unsigned int		to_rgb(unsigned int a, unsigned int r, unsigned int g, unsigned int b);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shaders.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhote <alhote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/21 14:34:04 by alhote            #+#    #+#             */
/*   Updated: 2016/07/17 21:28:53 by snicolet         ###   ########.fr       */
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

t_shaders			*shaders_init(void);
t_shader			*shader_init(t_shaders *shaders,
	void (*shader)(t_shader *s, t_render *r,
	t_obj *o), unsigned int color, unsigned int
	(*blend)(unsigned int a, unsigned int b));
int					shaders_exec(t_shaders *s, t_render *r, t_obj *o);
unsigned int		shaders_compute_color(t_shaders *s, unsigned int color);
void				shaders_disable_nexts(t_shader *s);
double				rt_reflection(t_render *r, t_obj *light);
void				rt_light_pow(t_shader *s, t_render *r, t_obj *light);
void				rt_specular_pow(t_shader *s, t_render *r, t_obj *light);
void				shader_damier(t_shader *s, t_render *r, t_obj *light);
void				shader_ambiant(t_shader *s, t_render *r, t_obj *light);
void				shader_shadow(t_shader *s, t_render *r, t_obj *light);
void				shader_texture(t_shader *s, t_render *r, t_obj *light);
void				shader_normalmap(t_shader *s, t_render *r, t_obj *light);
void				shader_reflection(t_shader *s, t_render *r, t_obj *light);
unsigned int		shader_color_texture_intersection(const t_render *r);
unsigned int		shader_color_normal_intersection(const t_render *r);
unsigned int		blend_normal(unsigned int a, unsigned int b);
unsigned int		blend_add(unsigned int a, unsigned int b);
unsigned int		blend_sub(unsigned int a, unsigned int b);
unsigned int		blend_multiply(unsigned int a, unsigned int b);
unsigned int		blend_lighten(unsigned int a, unsigned int b);
unsigned int		blend_darken(unsigned int a, unsigned int b);
unsigned int		blend_overlay(unsigned int a, unsigned int b);
void				shaders_activate_only(t_shaders *s, unsigned int n);
void				shaders_activate_all(t_shaders *s);
unsigned int		to_rgb(unsigned int a, unsigned int r, unsigned int g,
unsigned int b);

#endif

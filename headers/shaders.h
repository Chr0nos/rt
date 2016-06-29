/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shaders.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhote <alhote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/21 14:34:04 by alhote            #+#    #+#             */
/*   Updated: 2016/06/29 19:07:41 by alhote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHADERS_H
# define SHADERS_H
# include "rt.h"
# include "render.h"

typedef struct		s_shader
{
	unsigned int	color_render;
	unsigned int	color_base;
	char			operator;
	void			(*exec)(struct s_shader *s,
					t_render *r, t_obj *o);
}					t_shader;

typedef struct		s_shaders
{
	unsigned int	nbr_fshaders;
	int				(*vertex_shader)(t_render *r, t_obj *o);
	t_shader		**shader;
}					t_shaders;

t_shaders			*init_shaders(unsigned int nbr_fshaders);
t_shader			*init_shader(void (*shader)(t_shader *s, t_render *r,
t_obj *o), unsigned int color, char operator);
int					exec_fshaders(t_shaders *s, t_render *r, t_obj *o);
unsigned int		compute_color_shaders(t_shaders *s);
double				rt_reflection(t_render *r, t_obj *light);
void				rt_light_pow(t_shader *s, t_render *r, t_obj *light);
void				rt_specular_pow(t_shader *s, t_render *r, t_obj *light);
void				shader_damier(t_render *r, t_obj *light);
void				shader_ambiant(t_shader *s, t_render *r, t_obj *light);

#endif

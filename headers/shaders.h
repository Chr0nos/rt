/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shaders.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhote <alhote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/21 14:34:04 by alhote            #+#    #+#             */
/*   Updated: 2016/06/21 15:35:36 by alhote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHADERS_H
# define SHADERS_H
# include "render.h"

typedef struct		s_shaders
{
	unsigned int	nbr_fshaders;
	int				(*vertex_shader)(t_render *r);
	int				(**fragment_shader)(t_render *r);
}					t_shaders;
t_shaders			*init_shader(unsigned int nbr_fshaders);
int					exec_fshaders(t_shaders *s, t_render *r);
#endif

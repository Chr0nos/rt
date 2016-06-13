/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/08 00:08:43 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/13 12:17:32 by dboudy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H
# include "forms.h"

typedef struct 	s_render
{
	t_ray		*ray;
	t_obj		*root;
	t_obj		*obj_intersect;
	double		lowest_lenght;
	double		light_lenght;
	t_v4d		intersection;
}				t_render;

#endif

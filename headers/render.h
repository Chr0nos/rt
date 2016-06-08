/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/08 00:08:43 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/08 00:19:25 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H
# include "forms.h"

typedef struct 	s_render
{
	t_ray		*ray;
	double		lowest_lenght;
}				t_render;

#endif

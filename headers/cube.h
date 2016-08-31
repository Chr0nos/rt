/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/31 01:54:01 by snicolet          #+#    #+#             */
/*   Updated: 2016/08/31 02:54:48 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

typedef struct		s_cube_cmp
{
	float			*box;
	float			max;
	float			dir_axis;
}					t_cube_cmp;

int					cube_check(float *box, float start, float dir, double *tb);

#endif

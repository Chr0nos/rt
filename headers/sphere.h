/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/08 16:55:51 by snicolet          #+#    #+#             */
/*   Updated: 2016/08/30 03:20:52 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHERE_H
# define SPHERE_H

typedef struct	s_sphere_inter
{
	double		a;
	double		b;
	double		c;
	double		delta;
	double		sol1;
	double		sol2;
	double		delta_sqrt;
	double		sol;
}				t_sphere_inter;

#endif

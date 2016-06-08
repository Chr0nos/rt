/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/08 16:55:51 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/08 17:22:03 by snicolet         ###   ########.fr       */
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
}				t_sphere_inter;

#endif

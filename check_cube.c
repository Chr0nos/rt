/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cube.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/21 20:29:11 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/21 20:39:36 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	check_between(float a, float min, float max)
{
	return ((a >= min) && (a <= max));
}

int			check_cube(t_box *a, t_box *b)
{
	if (((check_between(a->zmin, b->zmin, b->zmax)) &&
		(check_between(a->xmin, b->xmin, b->xmax)) &&
		(check_between(a->ymin, b->ymin, b->ymax))) ||
		((check_between(a->zmax, b->zmin, b->zmax)) &&
		(check_between(a->xmax, b->xmin, b->xmax)) &&
		(check_between(a->ymax, b->ymin, b->ymax))))
		return (1);
	return (0);
}

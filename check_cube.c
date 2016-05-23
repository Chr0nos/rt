/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cube.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/21 20:29:11 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/23 20:10:52 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	check_between(float a, float min, float max)
{
	return ((a >= min) && (a <= max));
}

int			check_cube(const t_box *a, const t_box *b)
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

/*
** this function extens the box a to be able to contain the box b
*/

void		update_cube(t_box *a, const t_box *b)
{
	if (a->xmin > b->xmin)
		a->xmin = b->xmin;
	if (a->ymin > b->ymin)
		a->ymin = b->ymin;
	if (a->zmin > b->zmin)
		a->zmin = b->zmin;
	if (a->xmax < b->xmax)
		a->xmax = b->xmax;
	if (a->ymax < b->ymax)
		a->ymax = b->ymax;
	if (a->zmax < b->zmax)
		a->zmax = b->zmax;
}

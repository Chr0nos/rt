/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rad2deg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/04 22:10:25 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/04 22:13:06 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <math.h>

double	rad2deg(double rad)
{
	return (rad * 180.0 / M_PI);
}

float	rad2degf(float rad)
{
	return ((float)((double)rad * 180.0 / M_PI));
}

double	deg2rad(double deg)
{
	return (deg / 180.0 * M_PI);
}

float	deg2radf(float deg)
{
	return ((float)((double)deg / 180.0 * M_PI));
}

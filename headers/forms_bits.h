/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forms_bits.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/03 21:45:18 by snicolet          #+#    #+#             */
/*   Updated: 2016/09/03 21:45:48 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORMS_BITS_H
# define FORMS_BITS_H

typedef enum			e_type
{
	ROOT = 1,
	CUBE = 1 << 1,
	PLAN = 1 << 2,
	SPHERE = 1 << 3,
	CAMERA = 1 << 4,
	EMPTY = 1 << 5,
	SPOT = 1 << 6,
	POINTLIGHT = 1 << 7,
	FACE = 1 << 8,
	INVALID = 1 << 9,
	CONE = 1 << 10,
	CYL = 1 << 11,
	SUNLIGHT = 1 << 12,
	SETTING = 1 << 13,
	CONE_INF = 1 << 14,
	NOSHADER = 1 << 28,
	TRIANGLE = 1 << 29,
	MESH = 1 << 30,
	RADIUS = SPHERE | CUBE | CYL | CONE | CONE_INF,
	VISIBLE = CUBE | PLAN | SPHERE | FACE | CONE | CYL | CONE_INF |
	TRIANGLE | MESH,
	NOCHECKBOX = PLAN | CYL | CONE_INF,
	BOUNDED = CUBE | SPHERE | FACE | CONE | CYL | CONE_INF | TRIANGLE |
	EMPTY,
	LIGHTTYPE = SPOT | POINTLIGHT | SUNLIGHT,
}						t_type;

#endif

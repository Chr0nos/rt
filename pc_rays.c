/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pc_rays.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelangh <edelangh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/01 18:45:07 by edelangh          #+#    #+#             */
/*   Updated: 2016/09/01 18:45:16 by edelangh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

char			rt_rays_pc(const t_v2i *geometry, const t_v2i *px)
{
	float		endx;
	float		posx;
	float		endy;
	float		posy;

	endy = (float)(geometry->y);
	endx = (float)(geometry->x);
	posy = (float)(px->y);
	posx = (float)(px->x);
	return ((char)(
		((1.0f - (posx / endx)) + ((1.0f - (posy / endy)) / endx)) * 100.0f));
}

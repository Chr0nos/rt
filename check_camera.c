/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/30 19:55:28 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/30 19:56:25 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		rt_checkcamera(t_rt *rt)
{
	if (!rt)
		return (0);
	if (!rt->root)
		return (0);
	if (!rt->root->content)
		return (0);
	if (((t_obj*)rt->root->content)->type != CAMERA)
		return (0);
	return (1);
}

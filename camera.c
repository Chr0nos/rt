/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/28 18:08:25 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/28 19:16:32 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "libft.h"

t_obj	*rt_obj_getcamera(t_obj *obj)
{
	t_obj	*x;
	t_obj	*z;

	if (obj->type == CAMERA)
		return (obj);
	else if (obj)
	{
		x = obj->childs;
		while (x)
		{
			if (x->type == CAMERA)
				return (x);
			else if ((z = rt_obj_getcamera(x)))
				return (z);
			x = x->next;
		}
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_export_reflect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/16 00:51:49 by snicolet          #+#    #+#             */
/*   Updated: 2016/07/17 18:44:13 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"
#include "libft.h"

char	*sda_export_reflect(t_obj *obj, t_sda_export *e)
{
	(void)e;
	if (obj->type == SETTING)
	{
		if (!(obj->cfgbits & SDA_REFLECT))
			return (NULL);
		return (ft_itoa((int)((t_setting*)obj->content)->reflect));
	}
	return (ft_itoa(rt_obj_get_reflect(obj)));
}

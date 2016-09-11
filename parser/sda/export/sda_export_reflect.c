/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_export_reflect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/16 00:51:49 by snicolet          #+#    #+#             */
/*   Updated: 2016/09/03 21:56:56 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"
#include "libft.h"
#include "objects.h"

char	*sda_export_reflect(t_obj *obj, t_sda_export *e)
{
	unsigned char	reflect;

	if (obj->type == SETTING)
	{
		if (!(obj->cfgbits & SDA_REFLECT))
			return (NULL);
		return (ft_itoa((int)((t_setting*)obj->content)->reflect));
	}
	reflect = rt_obj_get_reflect(obj);
	if ((e) && (e->setting->reflect == reflect))
		return (NULL);
	return (ft_itoa(reflect));
}

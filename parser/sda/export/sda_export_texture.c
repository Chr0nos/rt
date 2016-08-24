/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_export_texture.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/15 23:49:46 by snicolet          #+#    #+#             */
/*   Updated: 2016/07/19 21:18:44 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"
#include "libft.h"

char	*sda_export_texture(t_obj *obj, t_sda_export *e)
{
	(void)e;
	if (!(obj->cfgbits & SDB_TEXTURE))
		return (NULL);
	return (ft_strdup(rt_obj_get_texture(obj)->filepath));
}

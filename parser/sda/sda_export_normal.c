/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_export_normal.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhote <alhote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/16 17:47:52 by alhote            #+#    #+#             */
/*   Updated: 2016/07/16 18:15:04 by alhote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"
#include "libft.h"

char	*sda_export_normal(t_obj *obj)
{
	t_texture	*tex;

	if (!(obj->cfgbits & SDB_TEXTURE))
		return (NULL);
	tex = rt_obj_get_normal(obj);
	if ((!tex) || (!tex->filepath))
		return (NULL);
	return (ft_strdup(tex->filepath));
}

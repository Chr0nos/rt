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
	if (!(obj->cfgbits & SDB_TEXTURE))
		return (NULL);
	return (ft_strdup(rt_obj_get_normal(obj)->filepath));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_export_name.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/16 00:40:09 by snicolet          #+#    #+#             */
/*   Updated: 2016/07/16 00:40:51 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"
#include "libft.h"

char	*sda_export_name(t_obj *obj)
{
	if (!(obj->cfgbits & SDB_NAME))
		return (NULL);
	return (ft_strdup(obj->name));
}

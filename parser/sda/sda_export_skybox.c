/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_export_skybox.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/17 13:51:18 by snicolet          #+#    #+#             */
/*   Updated: 2016/07/17 17:06:28 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"
#include "libft.h"

char		*sda_export_skybox(t_obj *obj)
{
	if (!(obj->cfgbits & SDB_SKYBOX))
		return (NULL);
	return (ft_strdup(((t_setting*)obj->content)->skybox->filepath));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_export_reflect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/16 00:51:49 by snicolet          #+#    #+#             */
/*   Updated: 2016/07/16 00:53:40 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"
#include "libft.h"

char	*sda_export_reflect(t_obj *obj)
{
	return (ft_itoa(rt_obj_get_reflect(obj)));
}

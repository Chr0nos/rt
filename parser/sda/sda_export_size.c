/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_export_size.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/15 23:40:43 by snicolet          #+#    #+#             */
/*   Updated: 2016/07/17 13:20:55 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"
#include "libft.h"
#include <stdlib.h>

char	*sda_export_size(t_obj *obj)
{
	return (sda_double_short(
		ft_dtoa((double)(((t_cube*)obj->content)->size), 6)));
}

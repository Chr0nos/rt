/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_export_pos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/15 14:24:34 by snicolet          #+#    #+#             */
/*   Updated: 2016/07/15 14:56:53 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"
#include "libft.h"

char	*sda_export_pos(t_v4d *v)
{
	char	*tab[3];
	char	*buff;

	tab[0] = ft_dtoa(v->x, 6);
	tab[1] = ft_dtoa(v->y, 6);
	tab[2] = ft_dtoa(v->z, 6);
	buff = ft_strmjoin(5, tab[0], " ", tab[1], " ", tab[2]);
	ft_mfree(3, tab[0], tab[1], tab[2]);
	return (buff);
}

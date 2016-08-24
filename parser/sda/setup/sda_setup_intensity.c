/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_setup_intensity.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/29 20:31:01 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/30 15:24:52 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"
#include "libft.h"

int			sda_setup_intensity(t_sda *e, t_obj *obj, char **av)
{
	(void)e;
	((t_plight *)obj->content)->intensity = ft_atod(av[0]);
	return (1);
}

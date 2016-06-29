/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_setup_intensity.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/29 20:31:01 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/29 20:36:12 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"
#include "libft.h"

int			sda_setup_intensity(t_rt *rt, t_obj *obj, char **av)
{
	(void)rt;
	((t_plight *)obj->content)->intensity = ft_atod(av[0]);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_setup_refract.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhote <alhote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/30 02:31:46 by snicolet          #+#    #+#             */
/*   Updated: 2016/09/11 17:49:23 by alhote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"
#include "libft.h"
#include "rt.h"

int			sda_setup_refract(t_sda *e, t_obj *obj, char **av)
{
	const double	value = ft_atod(av[0]);

	(void)e;
	if (value == 0.0)
		return (-1);
	obj->refractive_index = value;
	return (1);
}

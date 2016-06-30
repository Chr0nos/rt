/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_setup_refract.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/30 02:31:46 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/30 18:02:36 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"
#include "libft.h"
#include "rt.h"

int			sda_setup_refract(t_sda *e, t_obj *obj, char **av)
{
	(void)e;
	obj->refractive_index = ft_atod(av[0]);
	return (1);
}

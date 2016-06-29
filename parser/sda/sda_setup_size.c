/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_setup_size.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/29 18:57:31 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/29 18:59:37 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"
#include "libft.h"

int			sda_setup_size(t_rt *rt, t_obj *obj, char **av)
{
	(void)rt;
	((t_cube*)obj->content)->size = (float)ft_atod(av[0]);
	return (1);
}

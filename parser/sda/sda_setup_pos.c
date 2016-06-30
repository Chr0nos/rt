/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_setup_pos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/29 17:15:18 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/30 15:25:02 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"
#include "libft.h"

int			sda_setup_pos(t_sda *e, t_obj *obj, char **av)
{
	(void)e;
	obj->trans.w = (t_v4d){
		ft_atod(av[0]),
		ft_atod(av[1]),
		ft_atod(av[2]),
		1.0
	};
	return (1);
}

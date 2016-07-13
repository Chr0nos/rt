/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_setup_name.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/13 16:19:26 by snicolet          #+#    #+#             */
/*   Updated: 2016/07/13 16:21:09 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"
#include "libft.h"

int			sda_setup_name(t_sda *e, t_obj *obj, char **av)
{
	(void)e;
	obj->name = ft_strunsplit((const char **)(unsigned long)av, ' ');
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_setup_include.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/30 13:57:04 by snicolet          #+#    #+#             */
/*   Updated: 2016/09/11 20:18:25 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"
#include "libft.h"
#include <stdlib.h>

int		sda_setup_include(t_sda *e, t_obj *obj, char **av)
{
	char	*filepath;

	(void)obj;
	filepath = ft_strunsplit((const char **)(unsigned long)&av[0], ' ');
	if (!sda_parse_rawtree(filepath, e->rt, obj, e->last_lvl + 1))
	{
		ft_putstr_fd("error: failed to include file: ", 2);
		ft_putstr_fd(filepath, 2);
		free(filepath);
		return (-1);
	}
	free(filepath);
	return (1);
}

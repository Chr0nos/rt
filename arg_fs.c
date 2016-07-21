/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_fs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/21 19:04:02 by snicolet          #+#    #+#             */
/*   Updated: 2016/07/21 19:09:37 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "arguments.h"

int			arg_fs(t_rt *rt, int ac, char **av)
{
	(void)ac;
	(void)av;
	rt->settings.cfgbits |= RT_CFGB_FULLSCREEN;
	return (0);
}

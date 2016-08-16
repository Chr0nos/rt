/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_norefresh.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/21 19:59:09 by snicolet          #+#    #+#             */
/*   Updated: 2016/07/21 20:00:46 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "arguments.h"

int			arg_norefresh(t_rt *rt, int ac, char **av)
{
	(void)ac;
	(void)av;
	rt->settings.cfgbits |= RT_CFGB_NOREFRESHX;
	return (0);
}

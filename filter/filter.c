/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dboudy <dboudy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/23 11:12:46 by dboudy            #+#    #+#             */
/*   Updated: 2016/06/23 16:35:05 by dboudy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filter.h"
#include "rt.h"
#include "keyboard.h"

t_uint		filter(int keyboard, t_uint c)
{
	int					p;
	const t_filter_cfg	cfg[] = {
		(t_filter_cfg){FILTER_RED, &filter_red},
		(t_filter_cfg){FILTER_GREEN, &filter_green},
		(t_filter_cfg){FILTER_BLUE, &filter_blue},
		(t_filter_cfg){FILTER_MAGENTA, &filter_magenta},
		(t_filter_cfg){FILTER_YELLOW, &filter_yellow},
		(t_filter_cfg){FILTER_CYAN, &filter_cyan}
	};

	p = 6;
	while (p--)
		if (keyboard & cfg[p].bit)
			return (cfg[p].filter(c));
	return (c);
}

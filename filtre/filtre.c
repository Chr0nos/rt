/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filtre.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dboudy <dboudy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/23 11:12:46 by dboudy            #+#    #+#             */
/*   Updated: 2016/06/23 14:45:42 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filtre.h"
#include "rt.h"
#include "keyboard.h"

t_uint		filtre(int keyboard, t_uint c)
{
	int					p;
	const t_filter_cfg	cfg[] = {
		(t_filter_cfg){FILTER_RED, &filtre_red},
		(t_filter_cfg){FILTER_GREEN, &filtre_green},
		(t_filter_cfg){FILTER_BLUE, &filtre_blue}
	};

	p = 3;
	while (p--)
		if (keyboard & cfg[p].bit)
			return (cfg[p].filter(c));
	return (c);
}

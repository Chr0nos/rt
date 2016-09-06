/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interf_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/07 00:50:39 by snicolet          #+#    #+#             */
/*   Updated: 2016/09/07 00:55:58 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"

/*
** this function search the N item corresponding to mask in his flags
** for the first use N = 0
** if no occurence is found: NULL will be returned
** note: the search is done from the end of the list to the start
*/

t_interface_cfg		*interf_getflag(t_interf *me, int mask, int n)
{
	int		p;

	p = INTERF_ITEMS;
	while (p--)
	{
		if ((me->cfg[p].flags & mask) && (n-- == 0))
			return (&me->cfg[p]);
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_obj_checksplit.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/25 23:16:04 by snicolet          #+#    #+#             */
/*   Updated: 2016/08/25 23:29:20 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"
#include "libft.h"

static int	checksplit_clean(char ***split, int ret)
{
	ft_freesplit_multi(split, 3);
	return (ret);
}

int			parse_obj_checksplit(char ***split, int min)
{
	int		p;
	int		size;

	p = 3;
	if (ft_tabcount((void**)(unsigned long)split) < 3)
		return (checksplit_clean(split, -1));
	while (p--)
	{
		size = (int)ft_tabcount((void**)(unsigned long)split[p]);
		if (size < min)
			return (checksplit_clean(split, -2));
	}
	return (1);
}

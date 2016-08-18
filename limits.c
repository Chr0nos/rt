/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   limits.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qloubier <qloubier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/18 18:11:16 by qloubier          #+#    #+#             */
/*   Updated: 2016/08/18 18:32:34 by qloubier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "rt.h"

t_limit			*rt_create_limit(t_limtyp axe, t_v3d point, t_limit *next)
{
	t_limit		*ret;

	IFRET__(!(ret = malloc(sizeof(t_limit))), NULL);
	ret->axe = axe;
	ret->limit = point;
	ret->next = next;
	return (ret);
}

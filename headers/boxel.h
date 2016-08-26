/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boxel.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qloubier <qloubier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/20 20:30:01 by qloubier          #+#    #+#             */
/*   Updated: 2016/08/26 03:49:53 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOXEL_H
# define BOXEL_H
# include "rt.h"

typedef enum		e_boxtype
{
	VOXEL8_BOX,
	VOXEL16_BOX,
	VOXEL32_BOX,
	VOXEL64_BOX,
	OCTO_BOX
}					t_bxty;

typedef struct		s_boxtree
{
	t_bxty			type;
	void			*data;
}					t_boxtree;

#endif

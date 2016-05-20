/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forms.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 22:01:52 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/20 22:02:30 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORMS_H
# define FORMS_H
# include "draw.h"

typedef t_vector	t_v3f;
typedef t_matrix	t_mattf;

typedef struct		s_cube
{
	unsigned int	color;
	t_mattf			trans;
	float			size;
}					t_cube;

typedef struct		s_plan
{
	unsigned int	color;
	t_mattf			trans;
}					t_plan;

typedef struct		s_sphere
{
	unsigned int	color;
	t_mattf			trans;
	float			radius;
}					t_sphere;

typedef struct		s_obj
{
	int				type;
	int				id;
	struct t_obj	*parent;
	struct t_obj	*childs;
	struct t_obj	*next;
	void			*content;
}					t_obj;

#endif

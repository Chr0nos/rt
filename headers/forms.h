/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forms.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 22:01:52 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/20 23:53:53 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORMS_H
# define FORMS_H
# include "draw.h"

typedef t_vector	t_v3f;
typedef t_matrix	t_mattf;

enum				e_type
{
	ROOT = 0,
	CUBE = 1,
	PLAN = 2,
	SPHERE = 3
};

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
	unsigned int	id;
	struct s_obj	*parent;
	struct s_obj	*childs;
	struct s_obj	*next;
	void			*content;
}					t_obj;

#endif

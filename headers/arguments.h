/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/20 14:16:45 by snicolet          #+#    #+#             */
/*   Updated: 2016/09/09 00:29:34 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARGUMENTS_H
# define ARGUMENTS_H
# include "rt.h"
# define PARSE_ARG_STOP 1 << 30
# define PARSE_ARG_ERROR 1 << 29
# define PARSE_ARG_STOPALL 1 << 28

typedef struct		s_argument
{
	const char		*name;
	const int		params_mins;
	int				(*f)(t_rt *, int, char **);

}					t_argument;

t_v2i				arg_getgeo(const char *s);
int					arg_parse(t_rt *rt, int ac, char **av);
int					arg_geometry(t_rt *rt, int ac, char **av);
int					arg_fs(t_rt *rt, int ac, char **av);
int					arg_display_help(t_rt *rt, int ac, char **av);

#endif

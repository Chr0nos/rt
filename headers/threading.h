/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelangh <edelangh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/31 19:42:31 by edelangh          #+#    #+#             */
/*   Updated: 2016/08/31 20:05:34 by edelangh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREADING_H
# define THREADING_H

# include <pthread.h>
# define THREAD_COUNT 4

typedef struct	s_thread_args
{
	t_rt			*rt;
	unsigned int	*pixels;
	t_m4			m;
	int				index;
	int				thread_count;
	int				x_start;
	int				x_end;
}				t_thread_args;

#endif

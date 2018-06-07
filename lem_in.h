/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 11:52:38 by ydeineha          #+#    #+#             */
/*   Updated: 2018/06/07 11:52:41 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include "./libft/libft.h"
# define START 1
# define END 2

typedef struct	s_coord
{
	int			i;
	int			j;
}				t_coord;

typedef struct	s_lem_in
{
	int			ants;
	int			room_num;
	int			start;
	int			end;
	t_matrix	*rooms;
}				t_lem_in;

typedef struct	s_matrix
{
	char		*name;
	t_coord		pt;
	int			type;
	t_lst		*links;
}				t_matrix;

typedef struct	s_lst
{
	t_matrix	*room;
	int			dst;
}

#endif

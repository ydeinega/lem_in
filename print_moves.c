/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_moves.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 15:01:09 by ydeineha          #+#    #+#             */
/*   Updated: 2018/06/26 15:01:12 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_moves(t_lem_in *game, t_bug *ant, int ants, char *finish)
{
	int first;
	int i;

	first = 0;
	i = -1;
	while (++i < ants)
	{
		if (ant[i].room != game->start && finish[i] != FINISHED)
		{
			if (first)
				ft_printf(" ");
			ft_printf("L%i-%s", ant[i].num, game->room[ant[i].room].name);
			first++;
			if (ant[i].room == game->end)
				finish[i] = FINISHED;
		}
	}
	ft_printf("\n");
}

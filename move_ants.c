/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 19:26:47 by ydeineha          #+#    #+#             */
/*   Updated: 2018/06/15 19:26:49 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	choose_way(t_route *way, t_bug *ant, int *ants, int end)
{
	t_route	*head;
	t_way	*tmp;
	int		div;
	int		mod;

	head = way;
	tmp = NULL;
	div = 0;
	mod = 0;
	while (head)
	{
		tmp = head->room->next;
		div = head->steps / way->steps;
		mod = head->steps % way->steps;
		if (tmp->ant == 0 && ((div == 1 && mod == 0) || *ants > div))
		{
			ant->room = tmp->num;
			ant->turn = tmp;
			if (tmp->num != end)
				tmp->ant = ant->num;
			*ants = *ants - 1;
			break ;
		}
		head = head->next;
	}
}

void	move_futher(t_bug *ant)
{
	if (ant->turn)
	{
		ant->turn->ant = 0;
		ant->turn = ant->turn->next;
		ant->room = ant->turn->num;
		ant->turn->ant = ant->num;
	}
}

t_bug	*create_ants(t_lem_in *game)
{
	t_bug	*ant;
	int		i;

	i = -1;
	ant = (t_bug *)malloc(sizeof(t_bug) * game->ants);
	while (++i < game->ants)
	{
		ant[i].room = game->start;
		ant[i].num = i + 1;
		ant[i].turn = NULL;
	}
	return (ant);
}

void	clean_way(t_route *way)
{
	t_route	*tmp;

	tmp = NULL;
	while (way)
	{
		tmp = way;
		clean_room_inway(way->room);
		way = way->next;
		free(tmp);
	}
}

void	move_ants(t_lem_in *game, t_route *way)
{
	int		i;
	int		n_ants;
	t_bug	*ant;
	char	*finish;

	i = -1;
	n_ants = game->ants;
	ant = create_ants(game);
	finish = ft_strnew(game->ants);
	finish = ft_memset(finish, NOT_FINISHED, game->ants);
	while (ft_strchr(finish, NOT_FINISHED))
	{
		while (++i < game->ants)
		{
			if (ant[i].room == game->start)
				choose_way(way, &ant[i], &n_ants, game->end);
			else if (ant[i].room != game->end)
				move_futher(&ant[i]);
		}
		print_moves(game, ant, game->ants, finish);
		i = -1;
	}
	free(ant);
	clean_way(way);
	ft_strdel(&finish);
}

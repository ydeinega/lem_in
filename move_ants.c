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

// t_route	*make_way_array(t_route *way, int nways)
// {
// 	t_route	*array;
// 	t_route	*tmp;
// 	int		i;

// 	i = -1;
// 	tmp = NULL;
// 	array = (t_route *)malloc(sizeof(t_route) * nways);
// 	while (++i < nways)
// 	{
// 		array[i].steps = way->steps;
// 		array[i].room = way->room;
// 		array[i].next = NULL;
// 		tmp = way;
// 		way = way->next;
// 		free(tmp);
// 	}
// }

int		check_rooms(t_bug *ant, int n, int end)//ok
{
	int i;

	i = -1;
	while (++i < n)
	{
		if (ant[i].room != end)
			return (0);
	}
	return (1);
}

void	choose_way(t_route *way, t_bug *ant, int *ants)// ok
{
	t_route	*head;
	t_way	*tmp;
	int		div;
	int		mod;

	head = way;
	tmp = NULL;
	div = 0;
	mod = 0;
	//ft_printf("I'm here\n");
	while (head)
	{
		tmp = head->room->next;
		div = head->steps / way->steps;
		mod = head->steps % way->steps;
		if (tmp->ant == 0 && ((div == 1 && mod == 0) || *ants > div))
		{
			//ft_printf("I'm also here\n");
			ant->room = tmp->num;
			ant->turn = tmp;
			tmp->ant = ant->num;
			*ants = *ants - 1;
			break ;
		}
		head = head->next;
	}
	//ft_printf("Good bye\n");
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

t_bug	*create_ants(t_lem_in *game)//ok
{
	t_bug	*ant;
	int		i;

	i = -1;
	ant = (t_bug *)malloc(sizeof(t_bug) * game->ants);
	while (++i < game->ants)
	{
		ant[i].room = game->start;
		ant[i].num = i + 1;
		//ant[i].way = -1;
		ant[i].turn = NULL;
	}
	return (ant);
}

void	move_ants(t_lem_in *game, t_route *way)
{
	int		i;
	int		n_ants;
	t_bug	*ant;
	char	*finish;
	int		first;

	i = -1;
	first = 0;
	n_ants = game->ants;
	//way = make_way_array(way, nways);
	ant = create_ants(game);
	finish = ft_strnew(game->ants);
	finish = ft_memset(finish, NOT_FINISHED, game->ants);
	ft_lstprint(&(game->info));
	while (ft_strchr(finish, NOT_FINISHED))//check_rooms(ant, game->ants, game->end) == 0)//
	{
		while (++i < game->ants)
		{
			if (ant[i].room == game->start)
			{
				choose_way(way, &ant[i], &n_ants);
				// ft_printf("\nCHOOSE ROOM\n");
				// ft_printf("ant = %i room = %s ", ant[i].num, game->room[ant[i].room].name);
				// if (ant[i].turn)
				// 	ft_printf("ant_in_room = %i\n", ant[i].turn->ant);
				// else
				// 	ft_printf("\n");
			}
			else if (ant[i].room != game->end)
			{
				move_futher(&ant[i]);
				// ft_printf("\nMOVE FURTHER\n");
				// ft_printf("ant = %i room = %s ", ant[i].num, game->room[ant[i].room].name);
				// if (ant[i].turn)
				// 	ft_printf("ant_in_room = %i\n", ant[i].turn->ant);
				// else
				// 	ft_printf("\n");
			}
		}
		!first ? ft_printf("\n") : 0;
		first++;
		print_moves(game, ant, game->ants, finish);
		i = -1;
	}
	//free(ant);
}
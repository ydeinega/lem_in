/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_ways.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 15:27:50 by ydeineha          #+#    #+#             */
/*   Updated: 2018/06/15 15:27:52 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_way	*create_room(t_lem_in *game, int num, char *visit)
{
	t_way	*room;

	room = NULL;
	if (visit[num] == VISITED)
		return (NULL);
	room = (t_way *)malloc(sizeof(t_way));
	room->num = num;
	room->ant = 0;
	room->next = NULL;
	if (num != game->start && num != game->end)
		visit[num] = VISITED;
	return (room);
}

void	add_to_room(t_way *room)
{
	static t_way	*head = NULL;

	if (room)
	{
		room->next = head;
		head = room;
	}
}

t_way	*extract_way(t_lem_in *game, int num, char *visit, int *steps)
{
	t_way	*room;
	t_lst	*tmp;

	tmp = NULL;
	room = create_room(game, game->end, visit);
	add_to_room(room);
	while (num >= 0)
	{
		room = create_room(game, num, visit);
		if (room)
		{
			add_to_room(room);
			*steps = *steps + 1;
		}	
		tmp = game->room[num].ways;
		num = tmp ? tmp->num : -1;
	}
	return (room);
}

void	add_to_way(t_route **way, t_way *room, int steps)
{
	static t_route	*last = NULL;
	t_route			*turn;

	turn = (t_route *)malloc(sizeof(t_route));
	turn->steps = steps;
	turn->room = room;
	turn->next = NULL;
	if (*way == NULL)
		*way = turn;
	if (last)
		last->next = turn;
	last = turn;
}

int		find_ways(t_lem_in *game, char *visit)
{
	int		nways;
	int		steps;
	t_lst	*tmp;
	t_route	*way;
	t_way	*room;
	

	nways = 0;
	steps = 0;
	tmp = game->room[game->end].ways;
	way = NULL;
	room = NULL;
	while (tmp)
	{
		room = extract_way(game, tmp->num, visit, &steps);
		if (room)
		{
			add_to_way(&way, room, steps);
			nways++;
		}
		tmp = tmp->next;
		steps = 0;
	}
	t_route *t;
	t_way *head;
	t = way;
	while (t)
	{
		ft_printf("\nsteps = %i\n", t->steps);
		head = t->room;
		while (head)
		{
			ft_printf("ROOMS\n");
			ft_printf("room = %i, ant = %i ", head->num, head->ant);
			head = head->next;
		}
		ft_printf("\n");
		t = t->next;
	}
	//move_ants(game, way);
	return (nways);
}

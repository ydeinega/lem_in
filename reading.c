/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 11:54:05 by ydeineha          #+#    #+#             */
/*   Updated: 2018/06/07 11:54:08 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			reading_lem_in(char *line, t_lem_in *game, int *type)
{
	char	*ptr;

	ptr = ft_strtrim(line);
	if (ptr[0] != '#')
	{
		if (ft_strchr(ptr, ' '))
		{
			if (!room_valid(ptr, game, type))
				return (0);
		}
		else if (ft_strchr(ptr, '-'))
		{
			if (!link_valid(ptr, game, type))
				return (0);
		}
		else if (!ants_valid(ptr, game, type))
			return (0);
	}
	else if (!command_valid(ptr, game, type))
		return (0);
	add_info(game, ptr);
	if (ptr)
		ft_strdel (&ptr);
	return (1);
}

void		add_info(t_lem_in *game, char *ptr)
{
	t_list	*tmp;

	tmp = ft_lstnew(ptr, ft_strlen(ptr) + 1);
	if (game->info)
		ft_lstaddb(&(game->info), tmp);
	else
		game->info = tmp;
}

t_lem_in	*create_game(void)
{
	t_lem_in	*game;

	game = (t_lem_in *)malloc(sizeof(t_lem_in) * 1);
	if (!game)
		return (NULL);
	game->ants = 0;
	game->room_num = 0;
	game->start = 0;
	game->end = 0;
	game->node = NULL;
	game->room = NULL;
	game->info = NULL;
	return (game);
}

int			main(void)
{
	char		*line;
	t_lem_in	*game;
	int			type;
	int			ret;

	if (!(game = create_game()))
	{
		ft_printf("ERROR\n");
		return (0);
	}
	type = ANTS;
	while ((ret = get_next_line(0, &line)) > 0)//проверка на вход папки!!! что возвращает гнл при ошибке?
	{
		if (!reading_lem_in(line, game, &type))
		{
			ft_printf("ERROR\n");
			clean_game(game);
			ft_strdel(&line);
			return (0);
		}
		ft_strdel(&line);
	}
	if (ret < 0 || type != LINK)
	{
		ft_printf("ERROR\n");
		clean_game(game);
		return (0);
	}
	//ft_lstprint(&(game->info));//check the func if it checks null as argument moved it to the function move ants
	if (!lem_in(game))
		ft_printf("ERROR\n");
	/*
	int i = 0;
	t_lst *tmp;
		while (i < game->room_num)
		{
			ft_printf("\ni = %i name = %s pt = (%i, %i)\n", i, game->room[i].name, game->room[i].pt.i, game->room[i].pt.j);
			if (game->room[i].links)
			{
				ft_printf("LINKS\n");
				tmp = game->room[i].links;
				while (tmp)
				{
					ft_printf("%s ", game->room[tmp->num].name);
					tmp = tmp->next;
				}
				ft_printf("\n");
				ft_printf("MAPS\n");
				tmp = game->room[i].ways;
				while (tmp)
				{
					ft_printf("%s ", game->room[tmp->num].name);
					tmp = tmp->next;
				}
				ft_printf("\n");
			}
			i++;
		}
		ft_printf("start = %i end = %i\n", game->start, game->end);
	*/
	//перед запуском а алоритма необходимо проверить есть ли линки в старте и на энде. если линков нет, нет смысла запускать алгоритм
	clean_game(game);
	//while (1);
}
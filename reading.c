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

void	reading(char *line, t_lem_in *game)
{
	
}

int		main(void)
{
	char		*line;
	t_lem_in	*game;

	game = (t_lem_in *)malloc(sizeof(t_lem_in) * 1);
	while (get_next_line(0, &line))
	{
		reading(line, game);
	}
	//clean_game(&game);
}
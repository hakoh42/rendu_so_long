/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakoh <hakoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 21:03:35 by hakoh             #+#    #+#             */
/*   Updated: 2021/10/17 16:29:02 by hakoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
** Start point
*/
int	main(int ac, char **av)
{
	t_env	data;

	parsing_handler(&data, ac, av);
	engine_handler(&data);
	final_free(&data);
	return (0);
}

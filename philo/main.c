/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfiochi- <bfiochi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:29:39 by bfiochi-          #+#    #+#             */
/*   Updated: 2025/08/10 16:14:54 by bfiochi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	table;

	if ((argc == 5) || (argc == 6))
	{
		if (parse_input(&table, argv) != 0)
			return (1);
		init_data(&table);
		init_dinner(&table);
		clean(&table);
	}
	else
	{
		return (print_error("Invalid input!\n"));
	}
	return (0);
}

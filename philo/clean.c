/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfiochi- <bfiochi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 21:03:40 by bfiochi-          #+#    #+#             */
/*   Updated: 2025/08/17 14:29:11 by bfiochi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean(t_table *table)
{
	t_philo	*philo;
	int		i;

	i = -1;
	while (++i < table->number_of_philosophers)
	{
		philo = table->philos + i;
		handle_mutex(&philo->philo_mutex, DESTROY);
	}
	handle_mutex(&table->write_mutex, DESTROY);
	handle_mutex(&table->table_mutex, DESTROY);
	free(table->forks);
	free(table->philos);
}

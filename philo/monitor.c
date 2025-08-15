/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfiochi- <bfiochi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 20:18:54 by bfiochi-          #+#    #+#             */
/*   Updated: 2025/08/15 15:36:48 by bfiochi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	philo_died(t_philo *philo)
{
	long	elapsed;
	long	t_to_die;

	if (get_bool(&philo->mutex, &philo->full))
		return (false);
	elapsed = get_time(MILLESECOND)
		- get_long(&philo->mutex, &philo->last_meal_time);
	t_to_die = philo->table->time_to_die / 1000;
	if (elapsed > t_to_die)
		return (true);
	return (false);
}

void	*monitor(void *data)
{
	int		i;
	t_table	*table;

	table = (t_table *)data;
	while (!threads_running(&table->table_mutex, &table->threads_running_nbr,
			table->number_of_philosophers))
			;
	while (!simulation_finish(table))
	{
		i = -1;
		while (++i < table->number_of_philosophers)
		{
			if (philo_died(table->philos + i) && !simulation_finish(table))
			{
				handle_mutex(&table->write_mutex, LOCK);
				handle_mutex(&table->table_mutex, LOCK);
				printf("%-6ld %d died\n", (get_time(MILLESECOND)
						- table->start_of_dinner), table->philos[i].id);
				table->end_dinner = true;
				handle_mutex(&table->table_mutex, UNLOCK);
				handle_mutex(&table->write_mutex, UNLOCK);
			}
		}
	}
	return (NULL);
}

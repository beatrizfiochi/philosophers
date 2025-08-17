/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfiochi- <bfiochi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 20:18:54 by bfiochi-          #+#    #+#             */
/*   Updated: 2025/08/17 16:03:19 by bfiochi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	philo_died(t_philo *philo)
{
	long long	elapsed;
	long		t_to_die;

	if (get_bool(&philo->philo_mutex, &philo->full))
		return (false);
	elapsed = get_time(MILLESECOND)
		- get_long(&philo->philo_mutex, &philo->last_meal_time);
	t_to_die = philo->table->time_to_die / 1000;
	if (elapsed > t_to_die)
		return (true);
	return (false);
}

void	*monitor_dinner(void *data)
{
	int		i;
	t_table	*table;

	table = (t_table *)data;
	while (!threads_running(&table->table_mutex, &table->threads_running_nbr,
			table->number_of_philosophers))
			my_usleep(500, table);
	while (!simulation_finish(table))
	{
		i = -1;
		while (++i < table->number_of_philosophers)
		{
			if (philo_died(table->philos + i) && !simulation_finish(table))
			{
				set_bool(&table->table_mutex, &table->end_dinner, true);
				write_philo_status(DIED, table->philos + i);
			}
		}
	}
	return (NULL);
}

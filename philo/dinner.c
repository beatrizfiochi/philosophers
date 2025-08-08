/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfiochi- <bfiochi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 10:40:21 by bfiochi-          #+#    #+#             */
/*   Updated: 2025/08/08 18:04:41 by bfiochi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eat(t_philo *philo)
{
	
}

void	*dinner_simulation(void *data)
{
	t_philo *philo;

	philo = (t_philo *)data;
	wait_threads(philo->table);
	while (!simulation_finished(philo->table))
	{
		//TODO
		//if (philo->full)
		//	break ;
		//eat(philo);
		//sleep(philo);
		write_philo_status(SLEEPING, philo);
		my_usleep(philo->table->time_to_sleep, philo->table);
		//think(philo);
	}
}

void	init_dinner(t_table *table)
{
	int	i;

	i = -1;
	if (table->number_of_times_each_philosopher_must_eat == 0)
		return ;
	// TODO
	//else if (table->number_of_philosophers == 1)
	else
	{
		while (++i < table->number_of_philosophers)
			handle_thread(&table->philos[i].thread_id, dinner_simulation,
				&table->philos[i], CREATE);
	}
	table->start_of_dinner = get_time(MILLESECOND);
	set_bool(&table->table_mutex, &table->threads_ready, true);
	i = -1;
	while (++i < table->number_of_philosophers)
		handle_thread(&table->philos[i].thread_id, NULL, NULL, JOIN);

}

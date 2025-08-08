/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfiochi- <bfiochi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 10:40:21 by bfiochi-          #+#    #+#             */
/*   Updated: 2025/08/08 20:05:10 by bfiochi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	think(t_philo *philo)
{
	write_philo_status(THINKING, philo);
}

static void	eat(t_philo *philo)
{
	set_long(&philo->mutex, &philo->last_meal_time, get_time(MILLESECOND));
	handle_mutex(&philo->mutex, LOCK);
	philo->meals++;
	write_philo_status(EATING, philo);
	handle_mutex(&philo->mutex, UNLOCK);
	my_usleep(philo->table->time_to_eat, philo->table);
	handle_mutex(&philo->table->waiter_mutex, LOCK);
	handle_mutex(&philo->left_fork->fork, UNLOCK);
	handle_mutex(&philo->right_fork->fork, UNLOCK);
	set_fork_is_taken(philo, false);
	handle_mutex(&philo->table->waiter_mutex, UNLOCK);
	handle_mutex(&philo->mutex, LOCK);
	if (philo->table->number_of_times_each_philosopher_must_eat > 0 &&
		philo->meals == philo->table->number_of_times_each_philosopher_must_eat)
		set_bool(&philo->mutex, &philo->full, true);
	handle_mutex(&philo->mutex, UNLOCK);
}

void	*dinner_simulation(void *data)
{
	t_philo *philo;

	philo = (t_philo *)data;
	wait_threads(philo->table);
	while (!simulation_finished(philo->table))
	{
		if (philo->full)
			break ;
		ask_waiter(philo, philo->table);
		eat(philo);
		write_philo_status(SLEEPING, philo);
		my_usleep(philo->table->time_to_sleep, philo->table);
		think(philo);
	}
	return (NULL);
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

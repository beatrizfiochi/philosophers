/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfiochi- <bfiochi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 10:40:21 by bfiochi-          #+#    #+#             */
/*   Updated: 2025/08/10 18:18:42 by bfiochi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	think(t_philo *philo, bool pre_simulation)
{
	long	t_eat;
	long	t_sleep;
	long	t_think;

	if (simulation_finished(philo->table))
		return ;
	if (!pre_simulation)
		write_philo_status(THINKING, philo);
	if (philo->table->number_of_philosophers % 2 == 0)
		return ;
	t_eat = philo->table->time_to_eat;
	t_sleep = philo->table->time_to_sleep;
	t_think = (t_eat * 2) - t_sleep;
	if (t_think < 0)
		t_think = 0;
	my_usleep(t_think * 0.42, philo->table);
}

void	*lone_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_threads(philo->table);
	set_long(&philo->mutex, &philo->last_meal_time, get_time(MILLESECOND));
	increase_long(&philo->table->table_mutex,
		&philo->table->threads_running_nbr);
	while (!simulation_finished(philo->table))
		usleep(200);
	return (NULL);
}

static void	eat(t_philo *philo)
{
	if (simulation_finished(philo->table))
		return ;
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
	if (philo->table->number_of_times_each_philosopher_must_eat > 0
		&& philo->meals
		== philo->table->number_of_times_each_philosopher_must_eat)
		set_bool(&philo->mutex, &philo->full, true);
}

void	*dinner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_threads(philo->table);
	set_long(&philo->mutex, &philo->last_meal_time, get_time(MILLESECOND));
	increase_long(&philo->table->table_mutex,
		&philo->table->threads_running_nbr);
	de_synchronize(philo);
	while (!simulation_finished(philo->table))
	{
		if (philo->full)
			break ;
		ask_waiter(philo, philo->table);
		eat(philo);
		write_philo_status(SLEEPING, philo);
		my_usleep(philo->table->time_to_sleep, philo->table);
		think(philo, false);
	}
	return (NULL);
}

void	init_dinner(t_table *table)
{
	int	i;

	i = -1;
	if (table->number_of_times_each_philosopher_must_eat == 0)
		return ;
	else if (table->number_of_philosophers == 1)
		handle_thread(&table->philos[0].thread_id,
			lone_philo, &table->philos[0], CREATE);
	else
	{
		while (++i < table->number_of_philosophers)
			handle_thread(&table->philos[i].thread_id, dinner_simulation,
				&table->philos[i], CREATE);
	}
	handle_thread(&table->monitor, monitor, table, CREATE);
	table->start_of_dinner = get_time(MILLESECOND);
	set_bool(&table->table_mutex, &table->threads_ready, true);
	i = -1;
	while (++i < table->number_of_philosophers)
		handle_thread(&table->philos[i].thread_id, NULL, NULL, JOIN);
	set_bool(&table->table_mutex, &table->end_dinner, true);
	handle_thread(&table->monitor, NULL, NULL, JOIN);
}

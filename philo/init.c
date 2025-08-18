/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfiochi- <bfiochi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 16:42:51 by bfiochi-          #+#    #+#             */
/*   Updated: 2025/08/18 11:12:21 by bfiochi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	assign_forks(t_philo *philo, t_fork *forks, int philo_position)
{
	int	philo_nbr;

	philo_nbr = philo->table->number_of_philosophers;
	philo->first_fork = &forks[((philo_position + 1) % philo_nbr)];
	philo->second_fork = &forks[philo_position];
	if (philo->id % 2 == 0)
	{
		philo->first_fork = &forks[philo_position];
		philo->second_fork = &forks[((philo_position + 1) % philo_nbr)];
	}
}

static void	init_philo(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < table->number_of_philosophers)
	{
		philo = table->philos + i;
		philo->id = i + 1;
		philo->full = false;
		philo->meals = 0;
		philo->table = table;
		handle_mutex(&philo->philo_mutex, INIT);
		assign_forks(philo, table->forks, i);
		i++;
	}
}

void	init_data(t_table *table)
{
	int	i;

	i = 0;
	table->end_dinner = false;
	table->threads_ready = false;
	table->threads_running_nbr = 0;
	table->philos = handle_malloc(sizeof(t_philo)
			* table->number_of_philosophers);
	handle_mutex(&table->table_mutex, INIT);
	handle_mutex(&table->write_mutex, INIT);
	table->forks = handle_malloc(sizeof(t_fork)
			* table->number_of_philosophers);
	while (i < table->number_of_philosophers)
	{
		handle_mutex(&table->forks[i].fork, INIT);
		table->forks[i].fork_id = i;
		i++;
	}
	init_philo(table);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfiochi- <bfiochi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:29:47 by bfiochi-          #+#    #+#             */
/*   Updated: 2025/08/07 17:29:55 by bfiochi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h> //printf
# include <stdlib.h> //malloc and free
# include <unistd.h> //write and usleep
# include <stdbool.h> //bool
# include <pthread.h> //mutex (init, destroy, lock and unlock) and
////////////////////////threads (create, join and detach)
# include <sys/time.h> //gettimeofday
# include <limits.h> //INT_MAX
# include <errno.h>

typedef enum e_opcode
{
	INIT,
	DESTROY,
	LOCK,
	UNLOCK,
	CREATE,
	JOIN,
	DETACH,
}	t_opcode;

typedef pthread_mutex_t	t_mutex;

typedef struct s_table	t_table;

typedef struct s_fork
{
	t_mutex	fork;
	int		fork_id;
}	t_fork;

typedef struct s_philo
{
	int			id;
	long		meals;
	bool		full;
	long		last_meal_time;
	t_fork		*left_fork;
	t_fork		*right_fork;
	pthread_t	thread_id;
	t_table		*table;
}	t_philo;

typedef struct s_table
{
	long		number_of_philosophers;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		number_of_times_each_philosopher_must_eat;
	long		start_of_dinner;
	bool		end_dinner;
	t_fork		*forks;
	t_philo		*philos;
}	t_table;

int				print_error(const char *error_message);
int				parse_input(t_table *table, char **argv);

char			*str_error_return(const char *error_message);

void			*handle_malloc(size_t bytes);
void			handle_mutex(t_mutex *mutex, t_opcode opcode);
void			handle_thread(pthread_t *thread, void *(*foo)(void *),
					void *data, t_opcode opcode);

#endif

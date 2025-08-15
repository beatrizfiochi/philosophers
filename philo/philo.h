/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfiochi- <bfiochi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:29:47 by bfiochi-          #+#    #+#             */
/*   Updated: 2025/08/15 17:51:52 by bfiochi-         ###   ########.fr       */
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

typedef enum e_philo_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_RIGTH_FORK,
	TAKE_LEFT_FORK,
	DIED,
}	t_philo_status;

typedef enum e_timecode
{
	SECOND,
	MILLESECOND,
	MICROSECOND,
}	t_timecode;

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
	bool	is_taken;
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
	t_mutex		mutex;
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
	bool		threads_ready;
	long		threads_running_nbr;
	pthread_t	monitor;
	t_mutex		table_mutex;
	t_mutex		write_mutex;
	t_fork		*forks;
	t_philo		*philos;
}	t_table;

//utils.c
int				print_error(const char *error_message);
char			*str_error_return(const char *error_message);
long			get_time(t_timecode time_code);
void			my_usleep(long usec, t_table *table);

//safe_functions.c
void			*handle_malloc(size_t bytes);
void			handle_mutex(t_mutex *mutex, t_opcode opcode);
void			handle_thread(pthread_t *thread, void *(*foo)(void *),
					void *data, t_opcode opcode);

//init.c
void			init_data(t_table *table);

//mutex_utils.c
void			set_bool(t_mutex *mutex, bool *dest, bool value);
void			set_long(t_mutex *mutex, long *dest, long value);
bool			get_bool(t_mutex *mutex, bool *value);
long			get_long(t_mutex *mutex, long *value);
bool			simulation_finish(t_table *table);

//synchronize.c
void			wait_threads(t_table *table);
bool			threads_running(t_mutex *mutex, long *threads, long philo_nbr);
void			increase_long(t_mutex *mutex, long *value);
void			de_synchronize(t_philo *philo);

//dinner.c
void			*dinner_simulation(void *data);
void			init_dinner(t_table *table);
void			think(t_philo *philo, bool pre_simulation);

//parser.c
int				parse_input(t_table *table, char **argv);

//write.c
void			write_philo_status(t_philo_status status, t_philo *philo);

//dinner_utils.c
void			acess_forks(t_philo *philo);

//monitor.c
void			*monitor(void *data);

//clean.c
void			clean(t_table *table);

#endif

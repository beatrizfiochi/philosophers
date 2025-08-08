/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfiochi- <bfiochi-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 16:50:10 by bfiochi-          #+#    #+#             */
/*   Updated: 2025/08/08 19:25:41 by bfiochi-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*handle_malloc(size_t bytes)
{
	void	*ret;

	ret = malloc(bytes);
	if (ret == NULL)
	{
		print_error("Error with malloc\n");
		return (NULL);
	}
	return (ret);
}

static void	handle_mutex_error(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	if ((status == EINVAL) && (opcode ==  LOCK || opcode == UNLOCK
		|| opcode == DESTROY))
		print_error("The value specified by mutex is invalid.\n");
	else if ((status == EINVAL) && (opcode ==  INIT))
		print_error("The value specified by attr is invalid.\n");
	else if (status == EDEADLK)
		print_error("A deadlock would occur if the thread blocked\
			 waiting for mutex.\n");
	else if (status == EPERM)
		print_error("The current thread does not hold a lock on mutex.\n");
	else if (status == ENOMEM)
		print_error("The process cannot allocate enough memory to create\
			 another mutex.\n");
	else if (status == EBUSY)
		print_error("Mutex is locked.\n");
}

void	handle_mutex(t_mutex *mutex, t_opcode opcode)
{
	if (opcode == INIT)
		handle_mutex_error(pthread_mutex_init(mutex, NULL), opcode);
	else if (opcode == DESTROY)
		handle_mutex_error(pthread_mutex_destroy(mutex), opcode);
	else if (opcode == LOCK)
		handle_mutex_error(pthread_mutex_lock(mutex), opcode);
	else if (opcode == UNLOCK)
		handle_mutex_error(pthread_mutex_unlock(mutex), opcode);
	else
		print_error("Wrong opcode for handle mutex\n");
}

static void	handle_thread_error(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	if (status == EAGAIN)
		print_error("No resources to create another thread.\n");
	else if (status == EPERM)
		print_error("The caller does not have appropriate permission.\n");
	else if ((status == EINVAL) && (opcode ==  CREATE))
		print_error("The value specified by attr is invalid.\n");
	else if ((status == EINVAL) && (opcode == JOIN || opcode == DETACH))
		print_error("The value specified by thread is not joinable.\n");
	if (status == ESRCH)
		print_error("No thread could be found corresponding to that\
			 specified by yhe given thread ID, thread.\n");
	else if (status == EDEADLK)
		print_error("A deadlock was detected or the value of thread specifies\
			 the calling thread.\n");
}

void	handle_thread(pthread_t *thread, void *(*foo)(void *),
			void *data, t_opcode opcode)
{
	if (opcode == CREATE)
		handle_thread_error(pthread_create(thread, NULL, foo, data), opcode);
	else if (opcode == JOIN)
		handle_thread_error(pthread_join(*thread, NULL), opcode);
	else if (opcode == DETACH)
		handle_thread_error(pthread_detach(*thread), opcode);
	else
		print_error("Wrong opcode for handle thread\n");
}

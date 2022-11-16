/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   protected_threads.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-tol <jvan-tol@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/02 16:04:13 by jvan-tol      #+#    #+#                 */
/*   Updated: 2022/10/21 17:42:27 by jvan-tol      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	p_mutex_init(t_table *table, pthread_mutex_t *mutex)
{
	if (!mutex)
		return ;
	if (pthread_mutex_init(mutex, NULL) != 0)
		ft_error(table, "unable to initialize mutex");
}

void	p_mutex_lock(t_table *table, pthread_mutex_t *mutex)
{
	if (!mutex)
		return ;
	if (pthread_mutex_lock(mutex) != 0)
		ft_error(table, "unable to lock mutex");
}

void	p_mutex_unlock(t_table *table, pthread_mutex_t *mutex)
{
	if (!mutex)
		return ;
	if (pthread_mutex_unlock(mutex) != 0)
		ft_error(table, "unable to unlock mutex");
}

void	p_mutex_destroy(pthread_mutex_t *mutex)
{
	if (!mutex)
		return ;
	if (pthread_mutex_destroy(mutex) != 0)
		exit(EXIT_FAILURE);
}

void	p_join(pthread_t thread)
{
	if (!thread)
		return ;
	if (pthread_join(thread, NULL) != 0)
		exit(EXIT_FAILURE);
}

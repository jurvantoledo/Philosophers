/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-tol <jvan-tol@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/01 11:37:23 by jvan-tol      #+#    #+#                 */
/*   Updated: 2022/10/21 17:44:15 by jvan-tol      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_error(t_table *table, char *reason)
{
	table->active = 0;
	write(STDERR_FILENO, "error: ", 7);
	write(STDERR_FILENO, reason, ft_strlen(reason));
	wait_threads(table);
	cleanup(table);
	exit(EXIT_FAILURE);
}

void	print_action(t_table *table, t_philosophers *philosophers, \
					char *string_action, int force_print)
{
	pthread_mutex_lock(&table->mutex[table->args->number_of_philosphers]);
	if (table->active || force_print)
		printf("%lu %d %s\n", ft_current_time(), philosophers->id, \
								string_action);
	pthread_mutex_unlock(&table->mutex[table->args->number_of_philosphers]);
}

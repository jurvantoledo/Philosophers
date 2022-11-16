/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-tol <jvan-tol@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/06 15:48:12 by jvan-tol      #+#    #+#                 */
/*   Updated: 2022/10/21 17:45:12 by jvan-tol      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

t_uint64	ft_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	*seat_philosopher(t_table *table)
{
	t_int32	i;

	i = 0;
	table->philosophers[i].left_fork = \
					&table->mutex[table->args->number_of_philosphers - 1];
	while (i < table->args->number_of_philosphers)
	{
		table->philosophers[i].right_fork = &table->mutex[i];
		if (i)
			table->philosophers[i].left_fork = &table->mutex[i - 1];
		i++;
	}
	return (0);
}

void	ft_sleep(t_uint64 ms)
{
	t_uint64	cur;

	cur = ft_current_time();
	while (ft_current_time() - cur < ms)
		usleep(100);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	num;
	int	x;

	i = 0;
	num = 0;
	x = 1;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			x = -1;
		i++;
	}
	while ((str[i] >= '0' && str[i] <= '9') && str[i] != '\0')
	{
		num = num * 10 + str[i] - '0';
		i++;
	}
	return (num * x);
}

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

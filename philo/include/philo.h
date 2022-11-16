/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jvan-tol <jvan-tol@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/06 15:38:31 by jvan-tol      #+#    #+#                 */
/*   Updated: 2022/10/21 17:46:50 by jvan-tol      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <limits.h>
# include <sys/time.h>

typedef int				t_int32;
typedef unsigned int	t_uint32;
typedef long			t_int64;
typedef unsigned long	t_uint64;

# define PHILO_H

typedef struct s_philosophers {
	t_int32			id;
	t_int32			servings;
	t_int64			last_meal;
	pthread_t		thread;
	void			*right_fork;
	void			*left_fork;
}	t_philosophers;

typedef struct s_args {
	t_int32	number_of_philosphers;
	t_int32	time_to_die;
	t_int32	time_to_eat;
	t_int32	time_to_sleep;
	t_int32	amount_of_servings;
}	t_args;

typedef struct s_table {
	t_int32			active;
	pthread_mutex_t	*mutex;
	t_args			*args;
	t_philosophers	*philosophers;
}	t_table;

typedef struct s_structs
{
	t_table			*table;
	t_philosophers	*philosophers;
}	t_structs;

// Libft
int			ft_atoi(const char *str);

// Philosophers
void		*ft_philosopher(void *arg);
void		*seat_philosopher(t_table *table);
void		wait_threads(t_table *table);
void		create_thread(t_table *table);
void		monitoring_threads(t_table *table);
void		cleanup(t_table *table);

// timeval
t_uint64	ft_current_time(void);
void		ft_sleep(t_uint64 ms);

// print
void		ft_error(t_table *table, char *reason);
void		print_action(t_table *table, t_philosophers *philosophers, \
					char *string_action, int force_print);

// Protected threads
void		p_mutex_init(t_table *table, pthread_mutex_t *mutex);
void		p_mutex_lock(t_table *table, pthread_mutex_t *mutex);
void		p_mutex_unlock(t_table *table, pthread_mutex_t *mutex);
void		p_mutex_destroy(pthread_mutex_t *mutex);
void		p_join(pthread_t thread);

// Utils
size_t		ft_strlen(char *str);

#endif
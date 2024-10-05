/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingchen <jingchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 11:31:38 by jingchen          #+#    #+#             */
/*   Updated: 2024/01/21 16:37:35 by jingchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <pthread.h>

typedef struct t_table
{
	int						i;
	int						bdead;
	int						philo;
	int						die_time;
	int						eat_time;
	int						sleep_time;
	int						must_eat;
	int						status;
	struct t_philo			*philo_dt;
	pthread_t				dead_thread;
	pthread_mutex_t			mutex_dead;

}	t_table;

typedef struct t_philo
{
	struct t_table	*table;
	pthread_t		thread;
	int				id;
	int				state;
	int				eat;
	int				last_eat;
	int				bphilo;
	long int		st_time;
	pthread_mutex_t	fork;
	struct timeval	start_time;
	struct timeval	end_time;

}	t_philo;

void		ft_check_arguments(int argc, char **argv, int bmode);
void		ft_init_table(t_table	*table, char **argv);
void		ft_init_threads(t_table	*table);
void		ft_eat_and_sleep(t_philo	*philo_dt);
void		ft_join_threads(t_table	*table);
void		*ft_threads(void *arg);
void		*ft_check_dead(void *arg);
long long	time_stamp(void);
void		ft_usleep(int time_ms);
int			ft_atoi(const char *str);
void		ft_free_all(t_table	*table);
void		ft_left_fork(t_philo	*philo_dt);
void		ft_right_forks(t_philo	*philo_dt);
void		ft_print_dead(t_table *table);
void		ft_print_philo(t_philo	*philo_dt, int routine);

#endif
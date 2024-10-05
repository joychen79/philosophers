/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingchen <jingchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 11:55:44 by jingchen          #+#    #+#             */
/*   Updated: 2024/01/21 15:09:17 by jingchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_eat_and_sleep(t_philo	*philo_dt)
{
	pthread_mutex_lock(&(philo_dt->table->mutex_dead));
	philo_dt->last_eat = time_stamp() - philo_dt->st_time;
	if (philo_dt->table->bdead != 1)
		ft_print_philo(philo_dt, 1);
	philo_dt->eat++;
	pthread_mutex_unlock(&(philo_dt->table->mutex_dead));
	ft_usleep(philo_dt->table->eat_time);
	pthread_mutex_unlock(&(philo_dt->table->philo_dt[philo_dt->id - 1].fork));
	if (philo_dt->id + 1 <= philo_dt->table->philo)
		pthread_mutex_unlock(&(philo_dt->table->philo_dt[philo_dt->id].fork));
	else
		pthread_mutex_unlock(&(philo_dt->table->philo_dt[0].fork));
	pthread_mutex_lock(&(philo_dt->table->mutex_dead));
	if (philo_dt->table->bdead != 1)
		ft_print_philo(philo_dt, 2);
	pthread_mutex_unlock(&(philo_dt->table->mutex_dead));
	ft_usleep(philo_dt->table->sleep_time);
	pthread_mutex_lock(&(philo_dt->table->mutex_dead));
	if (philo_dt->table->bdead != 1)
		ft_print_philo(philo_dt, 3);
	pthread_mutex_unlock(&(philo_dt->table->mutex_dead));
}

void	ft_right_forks(t_philo	*philo_dt)
{
	if (philo_dt->bphilo == 1)
		return ;
	if (philo_dt->id + 1 <= philo_dt->table->philo)
	{
		pthread_mutex_lock(&(philo_dt->table->philo_dt[philo_dt->id].fork));
		pthread_mutex_lock(&(philo_dt->table->mutex_dead));
		if (philo_dt->table->bdead != 1)
			ft_print_philo(philo_dt, 0);
		pthread_mutex_unlock(&(philo_dt->table->mutex_dead));
	}
	else if (!(philo_dt->id + 1 <= philo_dt->table->philo))
	{
		pthread_mutex_lock(&(philo_dt->table->philo_dt[0].fork));
		pthread_mutex_lock(&(philo_dt->table->mutex_dead));
		if (philo_dt->table->bdead != 1)
			ft_print_philo(philo_dt, 0);
		pthread_mutex_unlock(&(philo_dt->table->mutex_dead));
	}
	ft_eat_and_sleep(philo_dt);
}

void	ft_left_fork(t_philo	*philo_dt)
{
	if (philo_dt->table->philo == 1)
	{
		philo_dt->bphilo = 1;
		return ;
	}
	pthread_mutex_lock(&(philo_dt->table->philo_dt[philo_dt->id - 1].fork));
	pthread_mutex_lock(&(philo_dt->table->mutex_dead));
	if (philo_dt->table->bdead != 1)
	{
		printf("%lldms philosopher %d has taken a fork\n",
			time_stamp() - philo_dt->st_time, philo_dt->id);
	}
	pthread_mutex_unlock(&(philo_dt->table->mutex_dead));
}

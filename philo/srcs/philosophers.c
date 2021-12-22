/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcorenti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 04:11:56 by rcorenti          #+#    #+#             */
/*   Updated: 2021/12/22 04:18:11 by rcorenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_exit(t_data *data, t_philo *philo, pthread_t *thread)
{
	int	i;

	i = 0;
	while (i < data->nbr)
	{
		pthread_mutex_destroy(&(data->forks[i]));
		i++;
	}
	pthread_mutex_destroy(&(data->write));
	free(philo);
	free(thread);
	free(data->forks);
}

void	check_dead(t_data *data, t_philo *philo)
{
	int	i;

	while (data->all_eat == -1)
	{
		i = 0;
		while (data->dead == -1 && i < data->nbr)
		{
			if (set_time(data) - philo[i].last_eat
				> (unsigned long)data->time_die)
			{
				data->dead = 1;
				print_state(data, i, "died");
			}
			i++;
		}
		if (data->dead != -1 || data->error != -1)
			break ;
		i = 0;
		while (i < data->nbr && philo[i].eat >= data->eat && data->eat != -1)
			i++;
		if (data->nbr == i)
			data->all_eat = 1;
	}
}

static int	ft_eat(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&(data->forks[philo->fork_left]));
	if (data->dead == 1 || data->all_eat == 1)
		return (1);
	print_state(data, philo->nbr, "has taken a fork");
	if (data->nbr == 1)
		return (1);
	pthread_mutex_lock(&(data->forks[philo->fork_right]));
	if (data->dead == 1 || data->all_eat == 1)
		return (1);
	print_state(data, philo->nbr, "has taken a fork");
	print_state(data, philo->nbr, "is eating");
	philo->last_eat = set_time(data);
	ft_usleep(data->time_eat, data);
	philo->eat++;
	pthread_mutex_unlock(&(data->forks[philo->fork_left]));
	pthread_mutex_unlock(&(data->forks[philo->fork_right]));
	return (0);
}

static void	*ft_thread(void	*philo)
{
	t_philo	*ptr;
	t_data	*data;

	ptr = (t_philo *)philo;
	data = ptr->data;
	if (ptr->nbr % 2 && data->dead == -1)
	{
		if (ft_shift(data, ptr))
			return (NULL);
	}
	while (data->dead == -1 && data->all_eat == -1 && data->error == -1)
	{
		if (ft_eat(ptr))
			break ;
		if (data->dead == 1 || data->all_eat == 1)
			break ;
		print_state(data, ptr->nbr, "is sleeping");
		ft_usleep(data->time_sleep, data);
		if (data->dead == 1 || data->all_eat == 1)
			break ;
		print_state(data, ptr->nbr, "is thinking");
	}
	return (NULL);
}

int	start_philos(t_data *data, t_philo *philo, pthread_t *thread)
{
	int	i;

	i = 0;
	while (i < data->nbr)
	{
		ft_philo(&philo[i], i, data->nbr);
		philo[i].data = data;
		if (pthread_create(&thread[i], NULL, ft_thread, &philo[i]))
		{
			printf("Error\nMalloc error\n");
			return (1);
		}
		philo[i].last_eat = set_time(data);
		i++;
	}
	return (0);
}

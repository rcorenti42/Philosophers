/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcorenti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 04:21:00 by rcorenti          #+#    #+#             */
/*   Updated: 2021/12/22 04:10:45 by rcorenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_state(t_data *data, int nbr, char *str)
{
	pthread_mutex_lock(&(data->write));
	printf("%ld %i %s\n", set_time(data) - data->time, nbr + 1, str);
	pthread_mutex_unlock(&(data->write));
}

int	ft_shift(t_data *data, t_philo *philo)
{
	print_state(data, philo->nbr, "is sleeping");
	ft_usleep(data->time_sleep, data);
	if (data->dead == 1 || data->all_eat == 1)
		return (1);
	print_state(data, philo->nbr, "is thinking");
	return (0);
}

long long	ft_atoi(char *str)
{
	int			i;
	int			neg;
	long long	ret;

	i = 0;
	neg = 0;
	ret = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg++;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		ret = ret * 10 + str[i] - '0';
		i++;
	}
	if (neg)
		ret = -ret;
	return (ret);
}

unsigned long int	set_time(t_data *data)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
	{
		printf("Error\nGettimeofday error\n");
		data->error = 1;
	}
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_usleep(unsigned long int time, t_data *data)
{
	unsigned long int	i;

	i = set_time(data);
	while (data->dead == -1)
	{
		if ((set_time(data) - i) >= time)
			break ;
		usleep(50);
	}
}

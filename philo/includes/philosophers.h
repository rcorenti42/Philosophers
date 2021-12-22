/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcorenti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 05:08:09 by rcorenti          #+#    #+#             */
/*   Updated: 2021/12/22 04:25:29 by rcorenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_data
{
	int					nbr;
	int					dead;
	int					time_eat;
	int					time_sleep;
	int					time_die;
	int					eat;
	int					all_eat;
	int					error;
	unsigned long int	time;
	pthread_mutex_t		*forks;
	pthread_mutex_t		write;
}				t_data;

typedef struct s_philo
{
	int					nbr;
	int					eat;
	int					fork_left;
	int					fork_right;
	t_data				*data;
	unsigned long int	last_eat;
}				t_philo;

void				check_dead(t_data *data, t_philo *philo);
void				ft_exit(t_data *data, t_philo *philo, pthread_t *thread);
void				ft_philo(t_philo *philo, int nbr, int max);
void				ft_init(t_data *data, char **argv);
int					start_philos(t_data *data,
						t_philo *philo, pthread_t *thread);
void				print_state(t_data *data, int nbr, char *str);
int					ft_shift(t_data *data, t_philo *philo);
long long			ft_atoi(char *str);
void				ft_usleep(unsigned long int time, t_data *data);
unsigned long int	set_time(t_data *data);

#endif

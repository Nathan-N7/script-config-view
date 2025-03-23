#include "philo.h"

void    take_fork(t_philo *philo)
{
    if (philo->id % 2)
    {
        pthread_mutex_lock(philo->left_fork);
        pthread_mutex_lock(&philo->table->print);
        printf("%ld %d has taken a fork\n", now() - philo->table->tm_start, philo->id);
        pthread_mutex_unlock(&philo->table->print);
        pthread_mutex_lock(philo->right_fork);
        pthread_mutex_lock(&philo->table->print);
        printf("%ld %d has taken a fork\n", now() - philo->table->tm_start, philo->id);
        pthread_mutex_unlock(&philo->table->print);
    }
    else
    {
        pthread_mutex_lock(philo->right_fork);
        pthread_mutex_lock(&philo->table->print);
        printf("%ld %d has taken a fork\n", now() - philo->table->tm_start, philo->id);
        pthread_mutex_unlock(&philo->table->print);
        pthread_mutex_lock(philo->left_fork);
        pthread_mutex_lock(&philo->table->print);
        printf("%ld %d has taken a fork\n", now() - philo->table->tm_start, philo->id); 
        pthread_mutex_unlock(&philo->table->print);
    }
}

void    eat(t_philo *philo)
{
    pthread_mutex_lock(&philo->meal);
    philo->meals += 1;
    pthread_mutex_unlock(&philo->meal);
    pthread_mutex_lock(&philo->table->print);
    printf("%ld %d is eating\n", now() - philo->table->tm_start, philo->id);
    pthread_mutex_unlock(&philo->table->print);
    pthread_mutex_lock(&philo->lock);
    philo->last_meal = now();
    pthread_mutex_unlock(&philo->lock);
    usleep(philo->table->time_eats * 1000); /*mcs for mls*/
    pthread_mutex_unlock(philo->right_fork);
    pthread_mutex_unlock(philo->left_fork);
}

void    philo_sleep(t_philo *philo)
{
    if  (!has_dead(philo->table))
    {
        pthread_mutex_lock(&philo->table->print);
        printf("%ld %d is sleeping\n", now() - philo->table->tm_start, philo->id);
        pthread_mutex_unlock(&philo->table->print);
        usleep(philo->table->tm_sleep * 1000); /*mcs for mls*/
    }
}

void    think(t_philo *philo)
{
    if (!has_dead(philo->table))
    {
        pthread_mutex_lock(&philo->table->print);
        printf("%ld %d is thinking\n", now() - philo->table->tm_start, philo->id);
        pthread_mutex_unlock(&philo->table->print);
        if (philo->table->time_die - (philo->table->time_eats + philo->table->tm_sleep) > 10)
            usleep(((philo->table->time_die - (philo->table->time_eats + philo->table->tm_sleep)) * 1000) - 10000);
    }
}
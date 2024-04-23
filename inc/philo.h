/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rprocopi <mailto:rprocopi@student.42lis    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:17:53 by rprocopi          #+#    #+#             */
/*   Updated: 2024/04/18 13:17:53 by rprocopi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <limits.h>
# include <errno.h>
# include <limits.h>
# include <stdbool.h>

/*#define DI(...) fprintf(stderr, "File: %s, Function: %s, \
		Line: %d ", __FILE__, __func__, __LINE__); \
                         fprintf(stderr, __VA_ARGS__); \
                         fprintf(stderr, "\n")
*/
/*
 * PHILO MAX
 * by default 200
*/
# ifndef PHILO_MAX
#  define PHILO_MAX 200 
# endif

typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}		t_opcode;

/*
** ANSI Escape Sequences for Bold Text Colors
** Usage: 
**     printf(R "This is red text." RST);
**     printf(B "This is blue text." RST);
** Remember to use RST to reset the color after setting it.
*/

# define RST    "\033[0m"      /* Reset to default color */
# define RED	"\033[1;31m"   /* Bold Red */
# define G      "\033[1;32m"   /* Bold Green */
# define Y      "\033[1;33m"   /* Bold Yellow */
# define B      "\033[1;34m"   /* Bold Blue */
# define M      "\033[1;35m"   /* Bold Magenta */
# define C      "\033[1;36m"   /* Bold Cyan */
# define W      "\033[1;37m"   /* Bold White */

typedef pthread_mutex_t	t_mtx;
typedef struct s_table	t_table;

typedef struct s_fork
{
	int			id;
	t_mtx		mtx;
}	t_fork;

typedef struct s_philo
{
	int			id;
	long long	last_meal;
	int			n_meals;
	int			is_dead;
	t_fork		*left_fork;
	t_fork		*right_fork;
	pthread_t	philo;
	t_table		*table;
}	t_philo;

typedef struct s_table
{
	int			n_philos;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			max_meals;
	bool		end;
	long long	dinner_start;
	t_philo		*philos;
	t_fork		*forks;
	t_mtx		mtx;
	t_mtx		log;
}	t_table;

// *** Parse ***
int			is_valid_input(char *str);
int			ft_atol(char *str);
void		parse_input(t_table *table, char **av);

// *** Init ***
void		init_table(t_table *table);
void		init_philos(t_table *table);
void		init_forks(t_table *table);
void		init_threads(t_table *table);

// *** Dinner ***
int			philo_eat(t_philo *philo);
int			philo_think(t_philo *philo);
int			philo_sleep(t_philo *philo);
void		*philosopher_routine(void *arg);
void		*one_philo(void *arg);

// *** Forks ***
void		take_fork(t_philo *philo, t_fork *taken_fork);
void		take_forks(t_philo *philo);
void		drop_forks(t_philo *philo);

// *** Cleanup ***
void		join_threads(t_table *table);
void		destroy_mutexes(t_table *table);
void		destroy_structures(t_table *table);
void		end_simulation(t_table *table);
void		clean(t_table *table);

// *** Time ***
long long	current_time_ms(void);
long long	elapsed_time_ms(long long start_time);
int			custom_wait(int wait_ms, t_philo *philo, int action);
int			has_philo_died(t_philo *philo);

// *** Utils ***
int			is_digit(char ch);
int			is_space(char ch);
void		increase_meal_counter(t_philo *philo);
void		write_text(char *text, t_philo *philo);
void		mutex_handle(t_mtx *mutex, t_opcode opcode);

//*** safe functions ***
void		safe_thread_handle(pthread_t *thread, void *(*foo)(void *),
				void *data, t_opcode opcode);
void		safe_mutex_handle(t_mtx *mutex, t_opcode opcode);
void		*safe_malloc(size_t bytes);
void		error_exit(const char *error);

#endif
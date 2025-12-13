/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 19:33:44 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/13 01:17:23 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# ifndef DEBUG
#  define DEBUG 0
# endif

# ifndef ASCENDING
#  define ASCENDING 1
# endif

# include "libft.h"
# include <limits.h>
# include <stddef.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_node_meta
{
	int				index;
	int				push_cost;
	int				above_median;
	struct s_nodes	*target;
	int				is_cheapest;
}					t_node_meta;

// NODES - Wrapper combining list node with metadata
typedef struct s_nodes
{
	int				v;
	t_node_meta		meta;
	struct s_nodes	*next;
}					t_nodes;

typedef struct s_stacks
{
	t_nodes			*a;
	t_nodes			*b;
	int				verbose;
}					t_stacks;

// COST - Context struct for cost calculation
typedef struct s_cost_ctx
{
	t_node_meta		*meta_a;
	t_node_meta		*meta_b;
	int				cost_a;
	int				cost_b;
	int				len_src;
	int				len_tgt;
}					t_cost_ctx;

// COST_TEST - Context struct for cost test visualizer
typedef struct s_cost_test_ctx
{
	int				len_a;
	int				len_b;
	int				i;
	t_nodes			*curr;
}					t_cost_test_ctx;

// SORT_THREE - Context struct for 3-element sorting
typedef struct s_sort_three_ctx
{
	int				v1;
	int				v2;
	int				v3;
}					t_sort_three_ctx;

// MOVES - Context struct for move execution
typedef struct s_moves_ctx
{
	t_node_meta		*meta_cheap;
	t_node_meta		*meta_target;
}					t_moves_ctx;

// TARGET - Context struct for target finding
typedef struct s_target_ctx
{
	t_nodes			*stack_b;
	t_nodes			*target;
	int				best_match;
	int				size;
	t_nodes			*curr_b;
}					t_target_ctx;

// SET_B_TARGETS - Context struct for setting b targets
typedef struct s_set_b_targets_ctx
{
	t_nodes			*stack_a;
	t_nodes			*stack_b;
	t_nodes			*curr_a;
	t_nodes			*curr_b;
	t_nodes			*target;
	int				best_match;
	int				size_a;
	int				size_b;
}					t_set_b_targets_ctx;

// PUSH_SWAP - Context struct for push_swap function
typedef struct s_push_swap_ctx
{
	t_nodes			*cheap;
	t_nodes			*min_node;
	int				len_a;
	int				len_b;
	int				size;
}					t_push_swap_ctx;

// SET_CHEAPEST - Context struct for finding cheapest node
typedef struct s_set_cheapest_ctx
{
	t_nodes			*curr;
	t_nodes			*cheapest;
	int				cheapest_cost;
	int				size;
	int				len_b;
}					t_set_cheapest_ctx;

// OPERATIONS
void				sa(t_stacks *s);
void				sb(t_stacks *s);
void				ss(t_stacks *s);
void				pa(t_stacks *s);
void				pb(t_stacks *s);
void				ra(t_stacks *s);
void				rb(t_stacks *s);
void				rr(t_stacks *s);
void				rra(t_stacks *s);
void				rrb(t_stacks *s);
void				rrr(t_stacks *s);

// INIT
int					ft_isnum(char *str);
void				free_stacks(t_stacks stacks);
void				init_stacks(t_stacks *stacks, char **strs);
int					has_duplicates(t_nodes *stack);
int					is_duplicate(t_nodes *stack, int value);
int					parse_number(char **p, int *value);

// DISPLAY
void				print_stack(t_nodes *stack, char *name);
void				debug_stacks(t_stacks s);
void				debug_line_stacks(t_stacks s, char *line,
						char *instruction);
int					ft_puterr(char *str);

// TEST HELPERS
t_nodes				*get_node_by_index(t_nodes *stack, int index);
void				display_specific_target(t_stacks *stacks, int index);
void				display_targets(t_stacks *stacks);

// HELPER
long				parse_int(const char *str, int *error);

// NODES - Custom list functions for t_nodes
t_nodes				*ft_new(int value);
void				ft_add_back(t_nodes **lst, t_nodes *new);
void				ft_add_front(t_nodes **lst, t_nodes *new);
int					ft_size(t_nodes *lst);
t_nodes				*ft_last(t_nodes *lst);
void				ft_delone(t_nodes *node);
void				ft_clear(t_nodes **lst);

// TARGET - Find insertion point for nodes
void				find_target(t_stacks *s, t_nodes *node_a);
void				set_target_nodes(t_stacks *s);
void				set_b_targets(t_stacks *s);
t_nodes				*find_extreme(t_nodes *stack);
void				init_target_ctx(t_target_ctx *ctx, t_nodes *stack_b);
t_nodes				*find_max_node(t_nodes *stack_b);
void				search_best_target(t_target_ctx *ctx, t_nodes *node_a);
void				init_b_targets_ctx(t_set_b_targets_ctx *ctx, t_stacks *s);
void				find_target_for_b(t_set_b_targets_ctx *ctx);
void				init_extreme_search(int *extreme_val,
						t_nodes **extreme_node, t_nodes *stack);
void				search_extreme_node(t_nodes *stack, int *extreme_val,
						t_nodes **extreme_node);

// COST - Calculate and find minimum cost node
void				calculate_cost(t_stacks *s, t_node_meta *meta_a, int to_b);
void				set_cheapest_node(t_nodes *stack);
void				init_indices(t_nodes *stack, int len);
int					max_val(int a, int b);
void				init_cost_ctx(t_cost_ctx *ctx, t_node_meta *meta_a,
						int len_src, int len_tgt);
void				compute_push_cost(t_cost_ctx *ctx);

// MOVES - Execute the optimal move sequence
void				execute_moves(t_stacks *stacks, t_nodes *cheapest_node);

// SORT - Main sorting algorithm
void				push_swap(t_stacks *s);
void				turk_algorithm(t_stacks *s);
void				sort_three(t_stacks *s);
int					is_sorted(t_nodes *stack);
int					cmp(int a, int b);
void				process_a_to_b(t_stacks *s);
void				move_a_to_b(t_stacks *s, t_nodes *cheap);
t_nodes				*find_cheapest(t_nodes *stack);

// CHECKER
int					execute_instruction(t_stacks *s, char *line);

#endif

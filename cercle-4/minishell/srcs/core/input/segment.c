/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 03:55:31 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/13 03:55:34 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

int try_handle_assignment_public(t_nodes *segment, char ***envp, int *exit_code)
{
    t_token *first_tok = (t_token *)segment->content;
    if (!first_tok || first_tok->type != TOKEN_WORD)
        return (0);
    char *eq = ft_strchr(first_tok->value, '=');
    if (!eq || eq == first_tok->value)
        return (0);
    int valid = 1;
    char *k = first_tok->value;
    if (!ft_isalpha((unsigned char)k[0]) && k[0] != '_')
        valid = 0;
    for (char *p = k; *p && *p != '=' && valid; p++)
    {
        if (!ft_isalnum((unsigned char)*p) && *p != '_')
            valid = 0;
    }
    if (!valid || segment->next)
        return (0);
    char *key = ft_substr(first_tok->value, 0, eq - first_tok->value);
    char *val = ft_strdup(eq + 1);
    ft_set_env(key, val, envp);
    free(key);
    free(val);
    *exit_code = 0;
    ft_lstclear(&segment, del_token);
    return (1);
}

int process_segment_public(t_nodes *segment, char ***envp, int *exit_code)
{
    expand_tokens(&segment, *envp, *exit_code);
    if (g_expansion_error)
    {
        *exit_code = g_exit_code;
        ft_lstclear(&segment, del_token);
        g_expansion_error = 0;
        return (1);
    }
    t_nodes *ast = ast_builder(segment);
    if (!scan_heredocs(ast))
        *exit_code = exec_tree(ast, envp);
    else
    {
        if (g_last_signal == 130)
            *exit_code = 130;
        else
            *exit_code = 1;
    }
    free_ast(ast);
    return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_innit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 23:45:21 by adi-nata          #+#    #+#             */
/*   Updated: 2023/07/11 16:46:17 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer	*lex_lstnew(int i, char *s)
{
	t_lexer	*new;

	new = (t_lexer *)malloc(sizeof(t_lexer) * 1);
	if (new == NULL)
		return (NULL);
	new->id = i + 1;
	new->token = s;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_lexer	*lex_lstlast(t_lexer *lexer)
{
	t_lexer	*next;

	if (lexer != NULL)
	{
		next = lexer;
		while (1)
		{
			if (next->next == NULL)
				return (next);
			next = next->next;
		}
	}
	return (NULL);
}

void	lex_lstadd_back(t_lexer **lexer, t_lexer *new)
{
	t_lexer	*last;

	if (!lexer)
		return ;
	if (*lexer == NULL)
		*lexer = new;
	else
	{
		last = lex_lstlast(*lexer);
		if (last != NULL)
		{
			last->next = new;
			new->prev = last;
		}
	}
}

void	lex_innit(t_shell *shell, t_lexer **lexer)
{
	int	i;

	i = -1;
	while (shell->inputs[++i])
		lex_lstadd_back(lexer, lex_lstnew(i, shell->inputs[i]));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 16:44:45 by adi-nata          #+#    #+#             */
/*   Updated: 2023/07/19 20:12:31 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "parser.h"
# include "../libft/include/libft.h"
# include "../libft/include/ft_printf.h"

# include <stdbool.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <readline/readline.h>
# include <readline/history.h>

# define HEREPATH	"./.heredoc"

# define CLR_RMV	"\033[0m"
# define RED		"\033[1;31m"
# define GREEN		"\033[1;32m"
# define YELLOW		"\033[1;33m"
# define BLUE		"\033[1;34m"
# define PURPLE		"\033[1;35m"
# define CYAN		"\033[1;36m"

typedef struct	s_shell
{
	char	*prompt;
	char	*input;
	char	**inputs;
	char	**env;
	char	**path;

	int		in;
	int		out;
	int		status;

	int		exit;
	bool	history;

	pid_t	pid;

}	t_shell;


void		shell_innit(t_shell *shell);
void		shell_loop(t_shell *shell, char **env);
void		shell_exit(t_shell *shell);

void		shell_env(char **env, t_shell *shell);

//	Tools
void		ft_error(int n);
int			ft_isvalid(char *s);
int			check_builtins(char *s);
int			strchr_index(char *s, char c);

char		**pipe_split(const char *s, char pipe);
void		pipe_splitta(const char *s, char pipe, char **split, size_t n);
size_t		pipe_numstr(const char *s, char pipe);


//	Lexer
void		shell_lexer(t_shell *shell);
void		lex_free_inputs(char **inputs);
void		lex_tokenizer(char *input, t_tok **token);

void		state_normal(char c, t_lex *lex, t_tok **token);
void		state_normal_space(char c, t_lex *lex, t_tok **token);
void		state_normal_dquote(t_lex *lex);
void		state_normal_squote(t_lex *lex);
void		state_quotes(char c, t_lex *lex);
void		state_dollar(char c, t_lex *lex);
void		state_dollarquotes(char c, t_lex *lex);


/* void		lex_start(t_shell *shell, t_tok **lexer);
// 2
int			quotes_end(char *s, int i, char quote);
int			lex_wordscount(char *s);
int			lex_type(char *s);
// 1
void		state_dollar(char c, t_lex *lex); */

void		lex_lstadd(t_tok **token, t_lex *lexer);
void		lex_lstadd_back(t_tok **token, t_tok *new);
void		lex_remove(t_tok *end, t_tok *start);
void		lex_free(t_lex *lexer);
t_tok		*lex_lstlast(t_tok *token);
t_tok		*lex_lstnew(int i, t_lex *lexer);
void		tok_free(t_tok *token);

//	Parser
void		shell_parser(t_shell *shell, t_pars **parser);
void		pars_commander(t_tok *start, t_tok *end, t_pars **parser);

void		pars_lstadd(t_pars **parser, char *s);
void		pars_lstadd_back(t_pars **parser, t_pars *new);
void		pars_free(t_pars *parser);
t_pars		*pars_lstlast(t_pars *parser);
t_pars		*pars_lstnew(char *s, int id);

//	Environment
void		env_freepaths(char **paths);


//	Executer
void		ft_exec(t_shell *shell, t_pars *parser, char **env);
int			exec_check(t_shell *shell, t_pars **parser, char **env);
char		*exec_path(char *cmd, char **env);

#endif
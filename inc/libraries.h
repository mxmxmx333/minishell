/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libraries.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbonengl <mbonengl@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 15:22:19 by mbonengl          #+#    #+#             */
/*   Updated: 2024/10/24 16:22:29 by mbonengl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* 
**This header will contain all the external libraries used in the minishell
**project. This will help to avoid including the same libraries in all the 
**other headers.
*/

#ifndef LIBRARIES_H
# define LIBRARIES_H

/*----------------------------> system libraries <----------------------------*/
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <signal.h>
# include <sys/wait.h>
# include <stdbool.h>

/*----------------------------> custom libraries <----------------------------*/
# include "minishell.h"
# include "libft.h"
# include "structures.h"
# include "lexer.h"
# include "initialize.h"
# include "console.h"
# include "expander.h"
# include "errors.h"
# include "memory.h"
# include "execution.h"
# include "colors.h"
# include "sig.h"
# include "parser.h"
# include "printing.h"
# include "builtins.h"

#endif
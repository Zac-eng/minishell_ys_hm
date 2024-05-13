#include "minishell.h"

bool	check_word(char	*line)
{
	return (*line && !strchr("|&;()\t\n",*line));
}

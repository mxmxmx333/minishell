
#include "minishell.h"

void	test_pathfinder(char *arg)
{
	t_msh	*msh;

	msh = initialize_minishell(NULL);
	prepare_execution(msh);
	pathfinder(msh, arg);
	printf("The path has been set to: %s\n", msh->exe_path);
	finished_execution(msh);	
}
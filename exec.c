#include "shell.h"
int execute(char *filepath, char **arg_tokens, int *exit_status, char **env)
{
	pid_t my_pid;
	pid_t child_pid;
	int status;

	if (filepath)
	{
		my_pid = fork();
		if (my_pid == 0)
		{
			if ((execve(filepath, arg_tokens, env) == -1))
				return (0);
		}
		else if (my_pid == -1)
		{
			return (0);
		}
		else
		{
			child_pid = waitpid(my_pid, &status, 0);
			if (child_pid == -1)
				return (0);
			if (WIFEXITED(status))
				*exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				*exit_status = WTERMSIG(status);
		}
		return (*exit_status);
	}
	return (1);
}
/*
int execute(char *filepath, char **arg, int exit_status, char **env)
{
	pid_t pid = getpid();

	if (pid == 0)
	{
		execve(filepath, arg, env);
	}
	wait(NULL);
	return (0);
}*/

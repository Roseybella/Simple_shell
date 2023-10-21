#include "main.h"

/**
 * change_dir - functions that change dir and fix errors
 * @state: The state of our shell
 * @dir: The directory
 * Return: eachtime. (0) on success, -1 if fail
 */

int change_dir(state_t *state, const char *dir)
{
	int ret;
	char buffer[1024];

	do {
		ret = chdir(dir);
		if (ret == -1)
		{
			issue_error(state, "can't cd to ");
			write(2, dir, strlen(dir));
			write(2, "\n", 1);
			state->status = 2;
		} else
		{
			_kitenv(state, "OLDPWD", _getenv(state, "PWD"));
			_kitenv(state, "PWD", getcwd(buffer, 1024));
			state->status = 0;
		}
	} while (ret == -1);

	return (ret);
}

/**
 * handle_dash_arg - functions that manage case when argument is "-"
 * @state: The state of our program (shell)
 * @old_str: old dir
 * @cwd_str: current working dir
 */

void handle_dash_arg(state_t *state, char *old_str, char *cwd_str)

{
	if (!old_str)
	{
		write(1, cwd_str, strlen(cwd_str));
		write(1, "\n", 1);
		state->status = 1;
	}
	else
	{
		write(1, old_str, strlen(old_str));
		write(1, "\n", 1);
		change_dir(state, old_str ? old_str : "/");
	}
}


/**
 * wr_cd - fucntion that changes current dir
 * @state: The state of our program (shell)
 * Return: eachtime, (0)
 */

int wr_cd(state_t *state)
{
	char *dir, buffer[1024];
	char *old_str = _getenv(state, "OLDPWD");

	if (!state->argv[1])
	{
		dir = _getenv(state, "HOME");
		if (!dir)
			dir = _getenv(state, "PWD") ? _getenv(state, "PWD") : "/";
		change_dir(state, dir);
	}
	else if (strcmp(state->argv[1], "-") == 0)
	{
		handle_dash_arg(state, old_str, getcwd(buffer, 1024));
	}
	else
	{
		change_dir(state, state->argv[1]);
	}

	return (0);
}


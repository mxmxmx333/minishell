#include "test.h"


t_exec *test_echo() {
    // Create a dummy t_exec struct for testing the echo command
    t_exec *echo_exec = malloc(sizeof(t_exec));

    // Set up the echo command
    echo_exec->cmd = strdup("echo");
    echo_exec->builtin = strdup("echo");
    
    // Allocate memory for arguments (e.g., "Hello, World!")
    echo_exec->args = malloc(3 * sizeof(char *));
    echo_exec->args[0] = strdup("Hello,");
    echo_exec->args[1] = strdup("World!");
    echo_exec->args[2] = NULL; // Null-terminated array

    // Initialize redirections (if any)
    echo_exec->redirections = NULL; // No redirections for this test

    // Set up out_pipe (assuming no piping in this test)
    echo_exec->out_pipe[0] = -1;
    echo_exec->out_pipe[1] = -1;

    // Set next and prev to NULL since this is a standalone test
    echo_exec->next = NULL;
    echo_exec->prev = NULL;
	return (echo_exec);
}
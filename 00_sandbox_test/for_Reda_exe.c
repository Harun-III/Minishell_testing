/*
** Read this if you want to understand the execution part
** of the program.
*/

void	setup_child_process(int prev_pipe, int *pipefd, t_cmd *cmd)
{
    // Check if the previous pipe is not the standard input.
    // This will be true for all commands in the pipeline except the first one.
    if (prev_pipe != STDIN_FILENO)
    {
        // Duplicate the previous pipe to the standard input.
        // This means the current command will read its input from the previous command's output.
        dup2(prev_pipe, STDIN_FILENO);

        // Close the original file descriptor for the previous pipe.
        // We don't need it anymore since we've duplicated it to STDIN_FILENO.
        close(prev_pipe);
    }

    // Check if there's a next command in the pipeline.
    // This will be true for all commands except the last one.
    if (cmd->next)
    {
        // Duplicate the write end of the current pipe to the standard output.
        // This means the current command's output will be written to the pipe.
        dup2(pipefd[1], STDOUT_FILENO);

        // Close the read end of the current pipe.
        // The child process won't be reading from this pipe, so we close it.
        close(pipefd[0]);

        // Close the original write end of the pipe.
        // We don't need it anymore since we've duplicated it to STDOUT_FILENO.
        close(pipefd[1]);
    }

    // Set up any additional redirections specified for this command.
    // This could include file redirections (>, <, >>), which are handled separately.
    setup_redirections(cmd->redir);
}

void execute_pipeline(t_shell *shell, t_cmd *cmd)
{
    // This will hold the file descriptors for the current pipe.
    // pipefd[0] is for reading, pipefd[1] is for writing.
    int     pipefd[2];

    // This stores the file descriptor of the previous pipe's read end.
    // We need it to connect the output of the previous command to the input of the current command.
    int     prev_pipe;

    // This will store the total number of commands in the pipeline.
    // It's useful for knowing when we're at the last command.
    int     cmd_count;

    // This keeps track of which command we're currently processing in the pipeline.
    int     cmd_index;

    // This will store the process ID returned by fork().
    pid_t   pid;

    // Initialize prev_pipe to standard input.
    // For the first command, if there's no redirection, input will come from stdin.
    prev_pipe = STDIN_FILENO;

    // Count the total number of commands in the pipeline.
    // This helps us know when we're at the last command, which doesn't need a pipe.
    cmd_count = count_commands(cmd);

    // Initialize the command index to 0.
    // We'll increment this for each command we process.
    cmd_index = 0;

    // We will loop on the linked list of commands until we reach the end (NULL).
    // This allows us to process each command in the pipeline sequentially.
    while (cmd)
    {
        // If there's a next command, we need to create a new pipe.
        // The last command doesn't need a pipe because its output goes to stdout.
        if (cmd->next)
            if (pipe(pipefd) == -1)
            {
                // If pipe creation fails, print an error and return.
                perror("pipe");
                return ;
            }

        // Fork a new process for each command.
        pid = fork();

        if (pid == 0)
        {
            // This is the child process.
            // Set up its input/output and execute the command.
            setup_child_process(prev_pipe, pipefd, cmd);
            execute_command(shell, cmd);
        }
        else if (pid < 0)
        {
            // Fork failed. Print an error and return.
            perror("fork");
            return ;
        }

        // This is the parent process.
        // Close unused file descriptors and prepare for the next command.
        handle_parent_process(&prev_pipe, pipefd, cmd);

        // Move to the next command in the linked list.
        cmd = cmd->next;

        // Increment the command index.
        cmd_index++;
    }

    // After all commands have been launched, wait for all child processes to finish.
    wait_for_children(shell);
}
#include "../minishell.h"
#include <fcntl.h>
#include <errno.h> 


void check_fd_(int fd, const char *file)
{
    if (fcntl(fd, F_GETFD) != -1 || errno != EBADF) {
        printf(GREEN "    FD %d is open" RST, fd);
        
        // Check if we can read from the FD
        if (fcntl(fd, F_GETFL) & O_RDONLY || fcntl(fd, F_GETFL) & O_RDWR)
            printf(" and readable");
        
        // Check if we can write to the FD
        if (fcntl(fd, F_GETFL) & O_WRONLY || fcntl(fd, F_GETFL) & O_RDWR)
            printf(" and writable");
        
        printf(".\n");
    } else {
        printf(RED "    FD %d is not open or accessible" RST "\n", fd);
    }
    
    if (file)
        printf(BLUE "    Associated file: %s\n" RST, file);
}

void print_redir_test(t_redir *redir)
{
    while (redir)
    {
        printf(YELLOW "    Redirection:" RST "\n");
        printf(BLUE "      FD: " RST "%d\n", redir->fd);
        printf(BLUE "      File: " RST "%s\n", redir->file);
        printf(BLUE "      Type: " RST);
        switch (redir->type)
        {
            case IN: printf("IN\n"); break;
            case OUT: printf("OUT\n"); break;
            case HERE: printf("HERE\n"); break;
            case APPEND: printf("APPEND\n"); break;
            default: printf("UNKNOWN\n");
        }
        check_fd_(redir->fd, redir->file);

        redir = redir->next;
    }
}

void print_cmd_test(t_cmd *cmd)
{
    int i = 0;
    while (cmd)
    {
        printf(GREEN "Command %d:" RST "\n", ++i);
        printf(BLUE "  Type: " RST "%s\n", cmd->type ? "Builtin" : "External");
        printf(BLUE "  Cmd: " RST "%s\n", cmd->cmd);
        printf(BLUE "  Args:" RST "\n");
        for (int j = 0; cmd->args && cmd->args[j]; j++)
        {
            printf("    [%d]: %s\n", j, cmd->args[j]);
        }

        printf(YELLOW "  Redirections:" RST "\n");
        if (cmd->redir)
            print_redir_test(cmd->redir);
        else
            printf("    No redirections\n");

        //print_redir_test(cmd->redir);
        cmd = cmd->next;
    }
}

void print_envm(t_env *env)
{
    int i = 0;
    while (env)
    {
        printf(M "Env Variable %d:" RST "\n", ++i);
        printf(BLUE "  Var: " RST "%s\n", env->var);
        printf(BLUE "  Value: " RST "%s\n", env->value);
        printf(BLUE "  Exported with equals: " RST "%s\n", env->exported_with_equals ? "Yes" : "No");
        env = env->next;
    }
}

void check_t_shell(t_shell *shell)
{
    if (!shell)
    {
        printf(RED "Error: Null shell pointer\n" RST);
        return;
    }

    printf(C "=== Shell Structure Debug Info ===" RST "\n\n");

    printf(YELLOW "Return Value: " RST "%d\n\n", get_set_return(0,0));
    // printf(YELLOW "Return Value: " RST "%d\n\n", shell->return_value);

    printf(YELLOW "Command List:" RST "\n");
    if (shell->cmd_list)
        print_cmd_test(shell->cmd_list);
    else
        printf(RED "  No commands in the list\n" RST);

    // printf("\n");

    // printf(YELLOW "Environment Variables:" RST "\n");
    // if (shell->my_env)
    //     print_envm(shell->my_env);
    // else
    //     printf(RED "  No environment variables\n" RST);

    printf("\n" C "=== End of Shell Structure Debug Info ===" RST "\n");
}
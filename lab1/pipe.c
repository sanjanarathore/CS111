#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    // Error handling for when no commands are given
	if (argc < 2) {
        errno = EINVAL;
        perror("Error: Insufficient arguments");
        return errno;
    }

	// Execute a single command with no pipe
    if (argc == 2) {
        execlp(argv[1], argv[1], NULL);
        perror("Execution failed");
        return errno;
    }

    // link commands together with pipes
	int pipes[argc - 2][2];
    for (int i = 0; i < argc - 2; i++) {
        if (pipe(pipes[i]) == -1) {
            perror("Pipe creation failed");
            return errno;
        }
    }

	pid_t pid[argc-1];
    for (int i = 1; i < argc; i++) {
		// create child process for each command
        pid[i-1] = fork();
        if (pid[i-1] == -1) {
            perror("Fork failed");	// handle case in which fork fails
            return errno;
        } else if (pid[i-1] == 0) {	// set up pipes and handle i/o redirection
            if (i == 1) {			// first pipe
                dup2(pipes[i - 1][1], STDOUT_FILENO);
            } else if (i == argc - 1) {		// last pipe
                dup2(pipes[i - 2][0], STDIN_FILENO);
            } else {				// middle pipes
                dup2(pipes[i - 2][0], STDIN_FILENO);
                dup2(pipes[i - 1][1], STDOUT_FILENO);
            }

			// close all pipes
            for (int j = 0; j < argc - 2; j++) {
                close(pipes[j][0]);
                close(pipes[j][1]);
            }

			// execute all commands
            execlp(argv[i], argv[i], NULL);
            perror("Execution failed");
            exit(errno);
        }
    }

    for (int i = 0; i < argc - 2; i++) {
        close(pipes[i][0]);
        close(pipes[i][1]);
    }

	// wait for all processes to finish and check error codes
    for (int i = 0; i < argc-1; i++) {
        int status;
		waitpid(pid[i], &status, 0);
		if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
			return 1;
		}
    }

    return 0;
}

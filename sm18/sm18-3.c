#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char * argv[]) {
    // Checking if there are exactly 4 command line args
    if (argc != 5) {
        return 0;
    }

    // Creating pipe and checking for errors
    int pipe_stream[2];
    if (pipe(pipe_stream) < 0) {
        exit(1);
    }

    // Creating child process
    pid_t pid1 = fork();
    if (pid1 < 0) {
        _exit(1);
    } else if (!pid1) {
        // Setting up in&out streams
        dup2(pipe_stream[1], 1); // pipe.write as stdout
        close(pipe_stream[0]);
        close(pipe_stream[1]);
        // Creating another child process to execute cmd1
        // ...that wierd demographics
        pid_t pid2 = fork();
        if (pid2 < 0) {
            _exit(1);
        } else if (!pid2) {
            // cmd1 execution
            execlp(argv[1], argv[1], NULL);
            _exit(0);
        }
        // waiting for Grandchild #1 to finish
        waitpid(-1, NULL, 0);

        // <...>

        // Setting up in&out streams
        dup2(pipe_stream[1], 1); // pipe.write as stdout
        close(pipe_stream[0]);
        close(pipe_stream[1]);
        // Creating another child process to execute cmd2
        pid_t pid3 = fork();
        if (pid3 < 0) {
            _exit(1);
        } else if (!pid3) {
            // cmd2 execution
            execlp(argv[2], argv[2], NULL);
            _exit(0);
        }
        // waiting for Grandchild #2 to finish and checking
        // if all the steps above finished successful
        int wait_ret;
        wait(&wait_ret);
        exit(wait_ret);
    }

    // Closing write stream - we don't need it any longer
    close(pipe_stream[1]);

    // One more process to handle cmd3
    pid_t pid4 = fork();
    if (pid4 < 0) {
        _exit(1);
    } else if (!pid4) {
        // Opening the output file and chaecking for errors
        int out_file = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0666);
        if (out_file < 0) {
            return 1;
        }

        dup2(pipe_stream[0], 0); // pipe.read as stdin
        dup2(out_file, 1); // out_file as stdout

        close(pipe_stream[0]); // no longer needed...
        close(out_file); // ... can be closed!

        // Creating a process to execute cmd3
        execlp(argv[3], argv[3], NULL);
        _exit(0);
    }

    // waiting for all processes to finish
    close(pipe_stream[0]);
    waitpid(-1, NULL, 0);
    waitpid(-1, NULL, 0);
    return(0);
}

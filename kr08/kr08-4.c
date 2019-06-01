

int main() {
    int pipe_fds[2];
    if (pipe(pipe_fds) < 0) {
        // Error while initializing pipe fds
        exit(1);
    }

    pid_t pid2 = fork();
    if (pid2 == 0) {
        // Child code
        close_fd(pipe_fds[1]);

        pid_t pid3 = fork();
        if (pid3 == 0) {
            // Grandchild process
            if (dup2(pipe_fds[0], STDIN_FILENO) < 0) {
                // Error while redirecting stdin
                exit(1);
            }
            close_fd(pipe_fds[0]);

            int fd_out_file = open(argv[5], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
            if (dup2(fd_out_file, STDOUT_FILENO) < 0) {
                // Error while redirecting stdin
                exit(1);
            }
            close_fd(fd_out_file);

            execlp(argv[3], argv[3], NULL);
            exit(0);
        } else if (pid3 < 0) {
            // Error while initializing process
            exit(1);
        }

        waitpid(pid3, NULL, 0);
        pid_t pid4 = fork();

        if (pid4 == 0) {
            // Grandchild process
            if (dup2(pipe_fds[0], STDIN_FILENO) < 0) {
                // Error while redirecting stdin
                exit(1);
            }
            close_fd(pipe_fds[0]);

            int fd_out_file = open(argv[5], O_WRONLY | O_APPEND);
            if (dup2(fd_out_file, STDOUT_FILENO) < 0) {
                // Error while redirecting stdin
                exit(1);
            }
            close_fd(fd_out_file);

            execlp(argv[4], argv[4], NULL);
            exit(0);
        } else if (pid4 < 0) {
            // Error while initializing process
            exit(1);
        }

        close_fd(pipe_fds[0]);
        waitpid(pid4, NULL, 0);
        exit(0);
    } else if (pid2 < 0) {
        // Error while initializing child process
        exit(1);
    }

    pid_t pid1 = fork();
    if (pid1 == 0) {
        // Child code
        close_fd(pipe_fds[0]);

        int status;
        pid_t pid5 = fork();
        if (pid5 == 0) {
            // Grandchild process
            if (dup2(pipe_fds[1], STDOUT_FILENO) < 0) {
                // Error while initializing child process
                exit(1);
            }
            close_fd(pipe_fds[1]);
            
            execlp(argv[1], argv[1], NULL);
            exit(0);
        } else if (pid5 < 0) {
            // Error while initializing child process
            exit(1);
        }

        waitpid(pid5, &status, 0);

        if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_SUCCESS) {
            pid_t pid6 = fork();
            if (pid6 == 0) {
                // Grandchild process
                if (dup2(pipe_fds[1], STDOUT_FILENO) < 0) {
                    // Error while initializing child process
                    exit(1);
                }
                close_fd(pipe_fds[1]);

                execlp(argv[2], argv[2], NULL);
                exit(0);
            } else if (pid6 < 0) {
                // Error while initializing child process
                exit(1);
            }
            waitpid(pid6, NULL, 0);
        }

        close_fd(pipe_fds[1]);
        exit(0);
    } else if (pid1 < 0) {
        // Error while initializing child process
        exit(1);
    }

    close_fd(pipe_fds[0]);
    close_fd(pipe_fds[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    return 0;
}

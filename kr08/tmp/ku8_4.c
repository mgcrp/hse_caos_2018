#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>

void close_fd(int fd) {
    if (close(fd) < 0) {
        perror(NULL);
        exit(EXIT_FAILURE);
    }
}

void redirect_stdin(int fd_in) {
    if (dup2(fd_in, STDIN_FILENO) < 0) {
        perror(NULL);
        exit(EXIT_FAILURE);
    }

    close_fd(fd_in);
}

void redirect_stdout(int fd_out) {
    if (dup2(fd_out, STDOUT_FILENO) < 0) {
        perror(NULL);
        exit(EXIT_FAILURE);
    }

    close_fd(fd_out);
}

void redirect_stdout_to_file1(const char *path) {
    int fd_out = open(path, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

    redirect_stdout(fd_out);
}

void redirect_stdout_to_file2(const char *path) {
    int fd_out = open(path, O_WRONLY | O_APPEND);

    redirect_stdout(fd_out);
}

void init_channel(int fds[2]) {
    if (pipe(fds) < 0) {
        perror(NULL);
        exit(EXIT_FAILURE);
    }
}

void do_secuence2(const char *cmd3, const char *cmd4, const char *file, int fds[2]) {
    int pid3, pid4;
    close_fd(fds[1]);

    pid3 = fork();

    if (pid3 == 0) {
        redirect_stdin(fds[0]);
        redirect_stdout_to_file1(file);
        execlp(cmd3, cmd3, NULL);
        exit(EXIT_FAILURE);
    } else if (pid3 < 0) {
        perror(NULL);
        exit(EXIT_FAILURE);
    }

    waitpid(pid3, NULL, 0);
    pid4 = fork();

    if (pid4 == 0) {
        redirect_stdin(fds[0]);
        redirect_stdout_to_file2(file);
        execlp(cmd4, cmd4, NULL);
        exit(EXIT_FAILURE);
    }
    close_fd(fds[0]);
    waitpid(pid4, NULL, 0);
    exit(EXIT_SUCCESS);
}

void do_secuence1(const char *cmd1, const char *cmd2, int fds[2]) {
    int pid1, pid2, status;
    close_fd(fds[0]);
    pid1 = fork();

    if (pid1 == 0) {
        redirect_stdout(fds[1]);
        execlp(cmd1, cmd1, NULL);
        exit(EXIT_FAILURE);
    } else if (pid1 < 0) {
        perror(NULL);
        exit(EXIT_FAILURE);
    }

    waitpid(pid1, &status, 0);

    if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_SUCCESS) {
        pid2 = fork();

        if (pid2 == 0) {
            redirect_stdout(fds[1]);
            execlp(cmd2, cmd2, NULL);
            exit(EXIT_FAILURE);
        } else if (pid2 < 0) {
            perror(NULL);
            exit(EXIT_FAILURE);
        }
        waitpid(pid2, NULL, 0);
    }

    close_fd(fds[1]);

    exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[]) {
    int pid1, pid2;
    int fds[2];
    init_channel(fds);

    pid2 = fork();

    if (pid2 == 0) {
        do_secuence2(argv[3], argv[4], argv[5], fds);
    } else if (pid2 < 0) {
        perror(NULL);
        exit(EXIT_FAILURE);
    }

    pid1 = fork();

    if (pid1 == 0) {
        do_secuence1(argv[1], argv[2], fds);
    } else if (pid1 < 0) {
        perror(NULL);
        exit(EXIT_FAILURE);
    }

    close_fd(fds[1]);
    close_fd(fds[0]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    return 0;
}

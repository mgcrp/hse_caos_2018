#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <math.h>
#include <stdlib.h>

void close_fd(int fd) {
    if (close(fd) < 0) {
        perror("close");
        exit(EXIT_FAILURE);
    }
}

void init_channel(int fds[2]) {
    if (pipe(fds) < 0) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
}

void fclose_f(FILE *f) {
    if (fclose(f) < 0) {
        perror("fclose");
        exit(EXIT_FAILURE);
    }
}

void process_1(double x0, unsigned long n, double dx, int fd_in, int fd_out) {
    int pid;  /* pid of grandson */

    pid = fork();

    if (pid > 0) {
        close_fd(fd_in);
        close_fd(fd_out);
        waitpid(pid, NULL, 0);
        exit(EXIT_SUCCESS);
    } else if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    double sum = 0.0, cur_number, rec_number;  /* current number, received number */

    for (unsigned long i = 0; i <= n; ++i) {
        cur_number = sin(x0 + i * dx);
        if (write(fd_out, &cur_number, sizeof(double)) != sizeof(double)) {
            perror("write");
            exit(EXIT_FAILURE);
        }
    }

    if (read(fd_in, &sum, sizeof(double)) != sizeof(double)) {
        perror("read");
        exit(EXIT_FAILURE);
    }

    printf("2 %.10lg\n", sum);
    fflush(stdout);

    sum = 0.0;

    for (unsigned long j = 0; j <= n; ++j) {
        if (read(fd_in, &rec_number, sizeof(double)) != sizeof(double)) {
            perror("read");
            exit(EXIT_FAILURE);
        }

        sum = sum + rec_number * rec_number;
    }

    if (write(fd_out, &sum, sizeof(double)) != sizeof(double)) {
        perror("write");
        exit(EXIT_FAILURE);
    }

    close_fd(fd_in);
    close_fd(fd_out);

    exit(EXIT_SUCCESS);
}

void process_2(long double x0, unsigned long n, long double dx, int fd_in, int fd_out) {
    int pid;  /* pid of grandson */

    pid = fork();

    if (pid > 0) {
        close_fd(fd_in);
        close_fd(fd_out);
        waitpid(pid, NULL, 0);
        exit(EXIT_SUCCESS);
    } else if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    double sum = 0.0, cur_number, rec_number;

    for (unsigned long j = 0; j <= n; ++j) {
        if (read(fd_in, &rec_number, sizeof(double)) != sizeof(double)) {
            perror("read");
            exit(EXIT_FAILURE);
        }

        sum = sum + fabs(rec_number);
    }

    if (write(fd_out, &sum, sizeof(double)) != sizeof(double)) {
        perror("write");
        exit(EXIT_FAILURE);
    }

    for (unsigned long i = 0; i <= n; ++i) {
        cur_number = cos(x0 + i * dx);
        if (write(fd_out, &cur_number, sizeof(double)) != sizeof(double)) {
            perror("write");
            exit(EXIT_FAILURE);
        }
    }

    if (read(fd_in, &sum, sizeof(double)) != sizeof(double)) {
        perror("read");
        exit(EXIT_FAILURE);
    }

    printf("1 %.10lg\n", sum);
    fflush(stdout);

    close_fd(fd_in);
    close_fd(fd_out);
    exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[]) {
    if (argc < 4) {
        fprintf(stderr, "Expected 3 arguments!\n");
        exit(EXIT_FAILURE);
    }

    double x0 = strtod(argv[1], NULL);
    unsigned long count = strtoul(argv[2], NULL, 10);
    double dx = strtod(argv[3], NULL);

    int fds1[2], fds2[2];  /* channels for sending numbers */

    init_channel(fds1);
    init_channel(fds2);

    int pid1, pid2;  /* pids of two sons */

    pid1 = fork();

    if (pid1 == 0) {
        close_fd(fds2[1]);
        close_fd(fds1[0]);
        process_1(x0, count, dx, fds2[0], fds1[1]);
    } else if (pid1 < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    pid2 = fork();

    if (pid2 == 0) {
        close_fd(fds2[0]);
        close_fd(fds1[1]);
        process_2(x0, count, dx, fds1[0], fds2[1]);
    } else if (pid2 < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    close_fd(fds1[0]);
    close_fd(fds1[1]);
    close_fd(fds2[0]);
    close_fd(fds2[1]);

    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    printf("0 0\n");

    exit(EXIT_SUCCESS);
}


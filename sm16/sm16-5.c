#include <fcntl.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void writer(char filename[], int N, int A, int D, int K, int process_number) {
    pid_t pid = fork();
    if (pid < 0) {
        exit(1);
    } else if (pid == 0) {
        int fd = open(filename, O_RDWR, 0666);

        for (int j = 0; j < K; ++j) {
            int off = lseek(fd, j + (process_number * 4), SEEK_SET);
            if (off < 0) {
                exit(1);
            }
            int res = write(fd, A + process_number + (D * j), 4);
            if (res != 1) {
                exit(1);
            }
        }

        close(fd);
    }
}

int main(int argc, char * argv[]) {
    if (argc < 6) {
        return 1;
    }

    int file = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, 0666);
    close(file);

    int N = strtol(argv[1], NULL, 10);
    int A = strtol(argv[3], NULL, 10);
    int D = strtol(argv[4], NULL, 10);
    int K = strtol(argv[5], NULL, 10);

    for (int i = 0; i < N; ++i) {
        writer(argv[2], N, A, D, K, i);
    }

    for (int i = 0; i < N; ++i) {
        wait(NULL);
    }

    return 0;
}

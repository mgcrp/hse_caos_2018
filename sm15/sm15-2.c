










{
    if (argc != 4) {
        return 1;
    }

    int fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, 0666);
    if (fd < 0) {
        return 2;
    }

    int rows = strtol(argv[2], NULL, NUM_BASE);
    int cols = strtol(argv[3], NULL, NUM_BASE);

    int off = lseek(fd, rows * cols * I32_SIZE - 1, SEEK_SET);
    if (off < 0) {
        return 5;
    }
    int res = write(fd, "", 1);
    if (res != 1) {
        return 4;
    }

    int32_t * array = (int32_t *) mmap(NULL, rows * cols * I32_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (array = MAP_FAILED) {
        close(fd);
        return 3;
    }

    /* skipped */

    int N = rows;
    int M = cols;
    int a[N][M];
    int number = 1;
    for (int i = 0; i < N/2; ++i) {
        for (int j = i; j < M - i; ++j) {
            if (number <= N * M) {
                a[i][j] = number++;                     // WATCH PROBLEMS HERE
            }
        }

        for (int y = i + 1; y < N - i - 1; ++y) {
            if (number <= N * M) {
                a[y][M - i - 1] = number++;
            }
        }

        for (int j = i; j < M - i; ++j) {
            if (number <= N * M) {
                a[N - i - 1][M - j - 1] = number ++;
            }
        }

        for (int y = i + 1; y < N - i - 1; ++y) {
            if (number <= N * M) {
                a[N - y - 1][i] = number++;
            }
        }
    }

    int k = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            array[k] = a[i][j];
            ++k;
        }
    }

    /* end of skipped */

    /* skipped in Sonya's code */

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            printf("%d ", array[i * cols + j]);
        }
        printf("\n");
    }

    /* end of skipped in Sonya's code */

    msync(array, rows * cols * I32_SIZE, MS_SYNC);
    munmap(array, rows * cols * I32_SIZE);
    close(fd);
    return 0;
}

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        return 1;
    }
    // open/create file
    int file = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    // while reading u_short
    unsigned short tmp_short;
    while (scanf("%hu", &tmp_short) == 1) {
        // lower - last bite of short
        unsigned char lower = (unsigned char) tmp_short;
        // higher - first bite of short
        unsigned char higher = (unsigned char) (tmp_short >> 8);
        // creating buffer of size 2 formatted as Big Endian
        char buf[] = { higher, lower };
        // writing buffer to file
        ssize_t result = write(file, buf, 2);
        if (result != 2) {
            return 1;
        }
    }
    // close file
    close(file);
}

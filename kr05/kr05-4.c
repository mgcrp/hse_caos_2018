#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        return 1;
    }
    // open/create file
    int file = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    // while reading u_int
    unsigned tmp_uint;
    while (scanf("%u", &tmp_uint) == 1) {
        // uint consists of 32 bits - 4 bytes
        // uint = |byte1| |byte2| |byte3| |byte4|
        // byte4 - last 8 bits of uint
        unsigned char byte4 = (unsigned char) tmp_uint;
        // creating byte3, byte2 and byte1
        unsigned char byte3 = (unsigned char) (tmp_uint >> 8);
        unsigned char byte2 = (unsigned char) (tmp_uint >> 16);
        unsigned char byte1 = (unsigned char) (tmp_uint >> 24);
        // creating buffer of size 4 formatted as Big Endian
        char buf[] = { byte1, byte2, byte3, byte4 };
        // writing buffer to file
        ssize_t result = write(file, buf, 4);
        if (result != 4) {
            return 1;
        }
    }
    // close file
    close(file);
}

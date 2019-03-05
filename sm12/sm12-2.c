#include <unistd.h>

void copy_file(int in_fd, int out_fd) {
    char buf[4096];
    ssize_t r_ret;
    while ((r_ret = read(in_fd, buf, 4096)) > 0) {
        ssize_t w_ret = write(out_fd, buf, r_ret);
        if (w_ret == -1) {
            exit(1);
        }
        while (w_ret < r_ret) {
            w_ret += write(out_fd, buf + w_ret, r_ret - w_ret);
        }
    }
}

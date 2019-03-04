#include <stdlib.h>
#include <string.h>
#include <unistd.h>

enum { BUF_SIZE = 4096 };

// release data in case of error
void release(struct FileContent* file) {
    if (file->data != NULL) {
        free(file->data);
    }
    file->data = NULL;
    file->size = -1;
}

// TODO:
//    - read() -> r_ret
//    - check for possible errors
//        + reading errors
//        + file is too big
//        + realloc errors
//    - realloc
//    - memcpy

struct FileContent read_file(int fd) {
    // creating buffer
    char *buf[BUF_SIZE];
    // creating structure to put the file in
    struct FileContent result = { 0, NULL };
    // creating variable for the read()'s return
    ssize_t r_ret;
    // while reading is successfull
    while ((r_ret = read(fd, buf, BUF_SIZE)) != 0) {
        // in case of error - release&return
        if (r_ret < 0) {
            release(&result);
            return result;
        }
        result.size += r_ret;
        char *new_data = (char*) realloc(result.data, result.size);
        if (new_data == NULL) {
            release(&result);
            return(result);
        }
        result.data = new_data;
        memcpy(result.data + result.size - r_ret, buf, r_ret);
    }
    char *new_data = (char*) realloc(result.data, result.size + 1);
    if (new_data == NULL) {
        release(&result);
        return result;
    }
    result.data = new_data;
    // last byte is '\0' - data is stored like string
    result.data[result.size] = 0;
    return result;
}

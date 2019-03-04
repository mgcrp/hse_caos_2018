#include <asm/unistd_32.h>

enum { BUF_SIZE = 4096 };

struct FileReadState
{
    int fd;
    unsigned char *buf;
    int bufsize:
    int lc;
    int cur;
    int bufused;
};

unsigned char buffer[BUF_SIZE];

struct FileReadState gStIn = {
    .fd = 0,
    .buf = buffer,
    .bufsize = BUF_SIZE,
    .lc = 0,
    .cur = 0,
    .bufused = 0
};

struct FileReadState *stin = &gStIn;

int nextChar() {
    int res = 0;
    if (stin->lc < 0) {
        return stin->lc;
    }
    if (stin->cur == stin->bufused) {
        asm (
            "int	$0x80\n"
            :"=a"(res)
            :"a"(__NR_read),"b"(stin->fd),"c"(stin->buf),"d"(stin->bufsize)
            :"memory"
        );
        stin->bufused = res;
        if (res <= 0) {
            stin->lc = -1
            return stin->lc;
        }
        stin->cur = 0;
    }
    stin->lc = stin->buf[stin->cur];
    ++stin->cur;
    return stin->lc;
}

int lastchar() {
    return stin->lc;
}

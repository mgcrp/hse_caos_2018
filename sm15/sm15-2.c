GNU nano 2.8.4                                           File: sm15-2.c

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <unistd.h>
#include <limits.h>


int main(int argc, char ** argv){
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
                                                    [ Read 97 lines ]
^G Get Help    ^O Write Out   ^W Where Is    ^K Cut Text    ^J Justify     ^C Cur Pos     M-U Undo	 M-A Mark Text
^X Exit        ^R Read File   ^\ Replace     ^U Uncut Text  ^T To Spell    ^_ Go To Line  M-E Redo	 M-6 Copy Text

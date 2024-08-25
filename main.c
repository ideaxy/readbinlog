#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define BINLOG_MAGIC "\xfe\x62\x69\x6e"
#define BINLOG_MAGIC_SIZE 4


int main(int argc,char *argv[])
{

    int fd = -1;
    fd = open(argv[1],O_RDONLY);
    if (fd < 0)
    {
        perror("open binlog file failed");
        return 1;
    }

    char magic[BINLOG_MAGIC_SIZE];
    read(fd,magic,BINLOG_MAGIC_SIZE);
    printf("%d\n",memcmp(magic,(const char *)BINLOG_MAGIC,BINLOG_MAGIC_SIZE));

}
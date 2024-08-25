#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#define ULONG unsigned long long

#define BINLOG_MAGIC "\xfe\x62\x69\x6e"
#define BINLOG_MAGIC_SIZE 4





int main(int argc,char *argv[])
{
    int r_count;
    struct event
    {
        int timestamp;
        int type;
        int server_id;
        int event_len;
        int end_log_p;
        int flags;
        unsigned char *data;
    };

    int fd = -1;
    fd = open(argv[1],O_RDONLY);
    if (fd < 0)
    {
        perror("open binlog file failed");
        return 1;
    }

    // check binlog file.
    char magic[BINLOG_MAGIC_SIZE];
    read(fd,magic,BINLOG_MAGIC_SIZE);
    if((memcmp(magic,(const char *)BINLOG_MAGIC,BINLOG_MAGIC_SIZE))!= 0)
    {
        printf("Not a binlog file.\n");
        return 1;
    }

    struct event *buffer = NULL;
    buffer = malloc(sizeof(struct event));
    int fd_point = lseek(fd,0,SEEK_CUR);
    read(fd,&buffer->timestamp,4);
    read(fd,&buffer->type,1);
    read(fd,&buffer->server_id,4);
    read(fd,&buffer->event_len,4);
    read(fd,&buffer->end_log_p,4);
    read(fd,&buffer->flags,2);

    printf("%d %d %d %d %d %d\n",\
    buffer->timestamp,\
    buffer->type,\
    buffer->server_id,\
    buffer->event_len,\
    buffer->end_log_p,\
    buffer->flags
    );


    int data_size = buffer->end_log_p - fd_point - 2;
    if((buffer->data = malloc(sizeof(data_size)))== NULL)
    {
        perror("malloc data");
    }
    
    r_count = read(fd,buffer->data,data_size);
    for(int i = 0; i <= r_count; i++)
    {
        printf("%02x\t",(unsigned char)buffer->data[i]);
        if(i%10 == 0)
        {
            printf("\n");
        }
    }
    
    printf("\n");
    


}
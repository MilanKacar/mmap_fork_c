#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define PAGE_SIZE 4096

int main(void)
{
    int fd = shm_open("/testing_fd", O_RDWR | O_CREAT, S_IWUSR | S_IRUSR);

    char *shared_mem = mmap(NULL, PAGE_SIZE, 
                        PROT_WRITE | PROT_WRITE,
                        MAP_SHARED, fd, 0);

    strcpy(shared_mem, "IT WORKED");
    printf("I changed the value : %s\n", shared_mem);

    return 0;
}
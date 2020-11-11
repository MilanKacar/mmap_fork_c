#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define PAGE_SIZE 4096
int v = 10;

int main(void)
{
    pid_t pid;
    int fd = shm_open("/testing_fd", O_RDWR | O_CREAT, S_IWUSR | S_IRUSR);

    size_t len = 4096;
    if (ftruncate(fd, len) == -1) {
        perror("ftruncate");
        return 1;
    }

    char *shared_mem = mmap(NULL, PAGE_SIZE, 
                            PROT_WRITE | PROT_WRITE,
                            MAP_SHARED, fd, 0);

    strcpy(shared_mem, "FUCK");
    printf("Value before forking : %s\n", shared_mem);

    pid = fork();

    if (pid == 0)
    {
        char *args[] = {"./server", NULL};
        execv("./server", args);
    }
    else
    {
        wait(NULL);
        printf("Parent value now : %s\n", shared_mem);
    }
    
    shm_unlink("/testing_fd");
    munmap(shared_mem, PAGE_SIZE);
    return 0;
}
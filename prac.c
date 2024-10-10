//Abhinav Vengala, 11698751
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int d = open("new.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (d == -1) {
        perror("Failed to open file");
        return 1;
    }

    if (dup2(d,1)== -1) {
        perror("Failed in duplicating the original file");
        close(d);
        return 1;
    }

    int b = dup2(d, 1);
    fprintf(stderr, "Old_File descriptor: %d, New_File descriptor: %d\n", d,b);
    fflush(stdout);
    close(d);
    return 0;
}

---------------------------------

//Abhinav Vengala, av112
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main() {

    int d = open("example.txt", O_RDWR);
    if (d < 0) {
        perror("failed");
        return 1;
    }

    int new_d = dup(d);
    if (new_d < 0) {
        perror("Failed in duplicating file");
        close(d);
        return 1;
    }

    char stk[6];
    ssize_t b_read = read(d, stk, 5);
    if (b_read < 0) {
        perror("read error");
        close(d);
        close(new_d);
        return 1;
    }

    stk[b_read] = '\0';
    printf("Read from file: %s\n", stk);

    const char *new = " - Appended content.";
    if (lseek(new_d, 0, SEEK_END) < 0) {
        perror("lseek");
        close(d);
        close(new_d);
        return 1;
    }
    if (write(new_d, new, strlen(new)) < 0) {
        perror("write");
        close(d);
        close(new_d);
        return 1;
    }

    close(d);
    close(new_d);

    return 0;
}


---------------------------
//Abhinav Vengala, av1112
#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t p_1, p_2;

    p_1 = fork();

    if (p_1 < 0) {
        perror("Failed fork");
        return 1;
    } else if (p_1 == 0) {
        printf("This is the first child process (P1) with PID: %d\n", getpid());
        printf("This is the PARENT process id is : %d\n",getppid());
    } else {
        p_2 = fork();
        if (p_2 < 0) {
            perror("Failed fork");
            return 1;
        } 
        else if (p_2 == 0) {
            printf("This is the second child process (P2) with PID: %d\n", getpid());
            printf("This is the PARENT process id is : %d\n",getppid());
        }
        else {
            printf("This is the parent process id:%d\n", getpid());
        }
    }
    return 0;
}


---------------

//Abhinav Vengala, av1112
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t p_1, p_2;
    p_1 = fork();

    if (p_1 == -1) {
        perror("fork failed");
        return 1;
    } 
    else if (p_1 == 0) {
        printf("This is the first child process P1 - PID: %d, Parent-PID: %d\n", getpid(), getppid());
        p_2 = fork();
        if (p_2 == -1) {
            perror("fork");
            return 1;
        } 
        else if (p_2 == 0) {
            printf("This is the second child process P2 - PID: %d, Parent-PID: %d\n", getpid(), getppid());
        } 
        else {
            wait(NULL); 
        }
    } 
    else {
        printf("This is the parent process (P) with PID: %d\n", getpid());
        wait(NULL); 
    }
    return 0;
}

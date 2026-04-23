#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <sys/wait.h>

#define SHM_SIZE 1024
#define MSG_KEY 1234
#define SHM_KEY 5678

// Structure for Message Queue
struct msg_buffer {
    long msg_type;
    char msg_text[100];
} message;

// 1. Unnamed Pipes: Unidirectional communication between related processes
void demo_pipe() {
    int fd[2];
    char buffer[100];
    if (pipe(fd) == -1) { perror("Pipe failed"); return; }

    if (fork() == 0) { // Child: Writer
        close(fd[0]); // Close unused read end
        char *data = "Hello from Pipe!";
        write(fd[1], data, strlen(data) + 1);
        close(fd[1]);
        exit(0);
    } else { // Parent: Reader
        close(fd[1]); // Close unused write end
        read(fd[0], buffer, sizeof(buffer));
        printf("[Pipe] Parent received: %s\n", buffer);
        close(fd[0]);
        wait(NULL);
    }
}

// 2. Message Queues: Linked list of messages in kernel
void demo_msg_queue() {
    int msgid = msgget(MSG_KEY, 0666 | IPC_CREAT);

    if (fork() == 0) { // Child: Sender
        message.msg_type = 1;
        strcpy(message.msg_text, "Hello from Msg Queue!");
        msgsnd(msgid, &message, sizeof(message.msg_text), 0);
        exit(0);
    } else { // Parent: Receiver
        wait(NULL);
        msgrcv(msgid, &message, sizeof(message.msg_text), 1, 0);
        printf("[Msg Queue] Parent received: %s\n", message.msg_text);
        msgctl(msgid, IPC_RMID, NULL); // Cleanup
    }
}

// 3. Shared Memory: Fastest IPC; processes map same memory segment
void demo_shared_memory() {
    int shmid = shmget(SHM_KEY, SHM_SIZE, 0666 | IPC_CREAT);
    char *shm_ptr = (char*) shmat(shmid, NULL, 0);

    if (fork() == 0) { // Child: Writer
        char *child_ptr = (char*) shmat(shmid, NULL, 0);
        strcpy(child_ptr, "Hello from Shared Memory!");
        shmdt(child_ptr);
        exit(0);
    } else { // Parent: Reader
        wait(NULL);
        printf("[Shared Memory] Parent received: %s\n", shm_ptr);
        shmdt(shm_ptr);
        shmctl(shmid, IPC_RMID, NULL); // Cleanup
    }
}

int main() {
    printf("--- IPC Demonstration ---\n");
    demo_pipe();
    demo_msg_queue();
    demo_shared_memory();
    return 0;
}

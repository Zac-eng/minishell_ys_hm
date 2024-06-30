#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int g_flag; // グローバルフラグ

void handle_status(pid_t pid_to_wait) {
    int status;
    waitpid(pid_to_wait, &status, 0);
    printf("yupoooon\n");
    if (status % 256 == 0)
        g_flag = status / 256;
    else {
        g_flag = 128 + status;
        printf("\n");
    }
}

int main() {
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // 子プロセス
        printf("子プロセスが実行されます\n");
        printf("aaa\n");
        execlp("ls", "ls", NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    } else {
        // 親プロセス
        printf("bbbb\n");
        handle_status(pid);
        printf("親プロセス: 子プロセスの終了ステータスは %d です\n", g_flag);
    }
    return 0;
}
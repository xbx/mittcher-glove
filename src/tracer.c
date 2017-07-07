#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/user.h>
#include <sys/reg.h>

WORD_SIZE = 8;

int main(int argc, char *argv[]){
    int status;
    pid_t traced_process;
    struct user_regs_struct regs;
    long ins;
    if (argc != 2){
        printf("Usage: %s %s <pid to be traced>\n", argv[0], argv[1]);
        exit(1);
    } 
    traced_process = atoi(argv[1]);
    ptrace(PTRACE_ATTACH, traced_process, NULL, NULL);
    printf("Waiting for Syscall #1\n");
    wait(&status);
    ptrace(PTRACE_GETREGS, traced_process, NULL, &regs);
    ptrace(PTRACE_SYSCALL, traced_process, NULL, NULL);
    wait(&status);
    while (regs.orig_rax != 1){
        ptrace(PTRACE_GETREGS, traced_process, NULL, &regs);
        ptrace(PTRACE_SYSCALL, traced_process, NULL, NULL);
        wait(&status);
    }
    while (regs.orig_rax == 1) {
        //printf("Syscall number: %d\n",regs.orig_rax);
        //printf("File descriptor number: %d\n", regs.rdi);
        //printf("Buffer length: %d\n", regs.rdx);
        int counter = 0;
        int total_data = regs.rdx;
        ptrace(PTRACE_SYSCALL, traced_process, NULL, NULL);
        wait(&status);
        printf("Printing output from error: \n");
        while (counter < total_data){
            char val[WORD_SIZE];
            char *pval;
            pval = val;
            pval = ptrace(PTRACE_PEEKDATA, traced_process, regs.rsi + counter, NULL);
            printf("%s", &pval);
            counter = counter + WORD_SIZE;
        }
        ptrace(PTRACE_SYSCALL, traced_process, NULL, NULL);
        wait(&status);
        ptrace(PTRACE_GETREGS, traced_process, NULL, &regs);
    }
    printf("END OF DATA\n");
    return 0;
}

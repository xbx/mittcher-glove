#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/user.h>
#include <sys/reg.h>

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
    wait(&status);
    ptrace(PTRACE_GETREGS, traced_process, NULL, &regs);
    ptrace(PTRACE_SYSCALL, traced_process, NULL, NULL);
    wait(&status);
    while (regs.orig_rax != 1){
        ptrace(PTRACE_GETREGS, traced_process, NULL, &regs);
        printf("Syscall number: %d\n",regs.orig_rax);
        ptrace(PTRACE_SYSCALL, traced_process, NULL, NULL);
        wait(&status);
    }
    printf("Syscall number: %d\n",regs.orig_rax);
    ins = ptrace(PTRACE_PEEKTEXT, traced_process, regs.rip, NULL);
    printf("EIP: %lx Instruction executedL %s \n", regs.rip, &ins);
    printf("File descriptor number: %d\n", regs.rdi);
    printf("Buffer length: %d\n", regs.rdx);
    printf("Buffer data: %lx\n", regs.rsi);
    printf("Buffer data: %s\n", &regs.rbx);
    char *val;
    val = ptrace(PTRACE_PEEKDATA, traced_process, regs.rsi, NULL);
    printf("LA data posta: %s", &val);
    printf("END OF DATA");

    return 0;
}

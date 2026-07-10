#include <stdio.h>
#include <stdint.h>
#include <syscall.h>


__attribute__((naked)) int syscall1(int snum) {
    (void) snum;
    __asm__ __volatile__ (
        "mov 0x08(%rsp),%rax;"
        "syscall;"
        "ret;"
    );
}

__attribute__((naked)) int syscall2(int snum, uint32_t arg1) {
    (void) snum;
    (void) arg1;
    __asm__ __volatile__ (
        "mov 0x08(%rsp),%rax;"
        "mov 0x10(%rsp),%rdi;"
        "syscall;"
        "ret;"
    );
}

__attribute__((naked)) int syscall3(int snum, uint32_t arg1, uint32_t arg2) {
    (void) snum;
    (void) arg1;
    (void) arg2;
    __asm__ __volatile__ (
        "mov 0x08(%rsp),%rax;"
        "mov 0x10(%rsp),%rdi;"
        "mov 0x18(%rsp),%rsi;"
        "syscall;"
        "ret;"
    );
}

__attribute__((naked)) int syscall4(int snum, uint32_t arg1, uint32_t arg2, uint32_t arg3) {
    (void) snum;
    (void) arg1;
    (void) arg2;
    (void) arg3;
    __asm__ __volatile__ (
        "mov 0x08(%rsp),%rax;"
        "mov 0x10(%rsp),%rdi;"
        "mov 0x18(%rsp),%rsi;"
        "syscall;"
        "ret;"
    );
}

__attribute__((naked)) int syscall5(int snum, uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t arg4) {
    (void) snum;
    (void) arg1;
    (void) arg2;
    (void) arg3;
    (void) arg4;
    __asm__ __volatile__ (
        "mov 0x08(%rsp),%rax;"
        "mov 0x10(%rsp),%rdi;"
        "mov 0x18(%rsp),%rsi;"
        "syscall;"
        "ret;"
    );
}

__attribute__((naked)) int syscall6(int snum, uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t arg4, uint32_t arg5) {
    (void) snum;
    (void) arg1;
    (void) arg2;
    (void) arg3;
    (void) arg4;
    (void) arg5;
    __asm__ __volatile__ (
        "mov 0x08(%rsp),%rax;"
        "mov 0x10(%rsp),%rdi;"
        "mov 0x18(%rsp),%rsi;"
        "syscall;"
        "ret;"
    );
}

__attribute__((naked)) int syscall7(int snum, uint32_t arg1, uint32_t arg2, uint32_t arg3, uint32_t arg4, uint32_t arg5, uint32_t arg6) {
    (void) snum;
    (void) arg1;
    (void) arg2;
    (void) arg3;
    (void) arg4;
    (void) arg5;
    (void) arg6;
    __asm__ __volatile__ (
        "mov 0x08(%rsp),%rax;"
        "mov 0x10(%rsp),%rdi;"
        "mov 0x18(%rsp),%rsi;"
        "mov 0x10(%esp), %edx;"
        "mov 0x10(%esp), %esi;"
        "mov 0x10(%esp), %edi;"
        "mov 0x10(%esp), %ebp;"
        "syscall;"
        "ret;"
    );
}

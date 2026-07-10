#include <stdio.h>
#include <stdint.h>

#define SYS_write 4

#define SYSCALL1 int syscall1(int syscall_number)
#define SYSCALL2 int syscall2(int syscall_number, uint32_t arg1, uint32_t arg2)
#define SYSCALL3 int syscall3(int syscall_number, uint32_t arg1, uint32_t arg2, uint32_t arg3)

__attribute__((naked)) int syscall1(int syscall_number) {
    __asm__ __volatile__ (
        "int $0x80"
        : "=a" (syscall_number)
        : "a" (syscall_number) // Syscall number in EAX
        : "memory"
    );
    return syscall_number; // Return value in EAX
}


__attribute__((naked)) int syscall2(int syscall_number, uint32_t arg1) {
    __asm__ __volatile__ (
        "int $0x80"
        : "=a" (syscall_number)
        : "a" (syscall_number), // Syscall number in EAX
          "b" (arg1)            // Arg 1 in EBX
        : "memory"
    );
    return syscall_number; // Return value in EAX
}

__attribute__((naked)) int syscall3(int syscall_number, uint32_t arg1, uint32_t arg2) {
    __asm__ __volatile__ (
        "int $0x80"
        : "=a" (syscall_number)
        : "a" (syscall_number), // Syscall number in EAX
          "b" (arg1),           // Arg 1 in EBX
          "c" (arg2)            // Arg 2 in ECX
        : "memory"
    );
    return syscall_number; // Return value in EAX
}

__attribute__((naked)) int syscall4(int syscall_number, uint32_t arg1, uint32_t arg2, uint32_t arg3) {
    __asm__ __volatile__ (
        "mov 0x04(%esp), %eax;"
        "mov 0x08(%esp), %ebx;"
        "mov 0x0C(%esp), %ecx;"
        "mov 0x10(%esp), %edx;"
        "int $0x80\n"
        "ret\n"
    );
}


int my_write(int fd, const char *buf, size_t count) {
    return syscall4(SYS_write, (uint32_t) fd, (uint32_t) buf, (uint32_t) count);
}

int main() {
    const char *message = "Hello, World!\n";
    my_write(1, message, 14); // Write to stdout (file descriptor 1)
    return 0;
}
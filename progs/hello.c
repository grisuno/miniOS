/* MiniOS test program — compiled as relocatable .o, loaded by kernel ELF loader */
extern int printf(const char *fmt, ...);

int main(int argc, char **argv) {
    printf("Hello from dynamically loaded program!\n");
    printf("argc = %d\n", argc);
    if (argc > 1) {
        int i;
        for (i = 1; i < argc; i++)
            printf("argv[%d] = %s\n", i, argv[i]);
    }
    return 42;
}

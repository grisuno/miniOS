int write(int fd, char *buf, int n);

int main(void) {
    write(1, "hola cvm\n", 9);
    return 0;
}

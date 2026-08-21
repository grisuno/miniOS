int printf();
void *fopen();
int fclose();
int fread();
int fwrite();

#define CP_BUF_SIZE 4096
#define CP_EXIT_FAIL 1

int main(int argc, char **argv) {
    if (argc != 3) {
        printf("usage: cp <src> <dst>\n");
        return CP_EXIT_FAIL;
    }
    void *in = fopen(argv[1], "r");
    if (!in) {
        printf("cp: cannot open %s\n", argv[1]);
        return CP_EXIT_FAIL;
    }
    void *out = fopen(argv[2], "w");
    if (!out) {
        fclose(in);
        printf("cp: cannot create %s\n", argv[2]);
        return CP_EXIT_FAIL;
    }
    char buf[CP_BUF_SIZE];
    int n;
    while ((n = fread(buf, 1, CP_BUF_SIZE, in)) > 0) {
        if (fwrite(buf, 1, n, out) != n) {
            fclose(in);
            fclose(out);
            printf("cp: write failed\n");
            return CP_EXIT_FAIL;
        }
    }
    fclose(in);
    if (fclose(out) != 0) {
        printf("cp: write failed\n");
        return CP_EXIT_FAIL;
    }
    return 0;
}

#include <stdio.h>
#include <time.h>
#include <assert.h>


//----------------/Sequencial-----------------------------------------------------------------------//

void ints_fget(FILE *f, char choice , char *variable) {
    double result = 0;
    double d = 0;

    char c;
    while (fscanf(f, "%c", &c) != EOF) {
        if (c == choice) {
            fseek(f, 1, SEEK_CUR);
            char t1[10];
            int tpos = 0;
            while (fscanf(f, "%c", &c) != EOF) {
                if (c == 'm') {
                    t1[tpos+1] = '\0';
                    break;
                }
                if (c == ',')
                    c = '.';
                t1[tpos++] = c;
            }
            sscanf(t1, "%lf", &d);
            result += d;
        }
    }
    rewind(f);
    printf("%s = %lf\n", variable, result/30);
}

void test_media(const char *filename) {

    FILE *f = fopen(filename, "r");
    assert(f != NULL);

    ints_fget(f, 'R', "Rows");
    ints_fget(f, 'C', "Columns");
    ints_fget(f, 'D', "Diagonals");
    ints_fget(f, 'T', "Threads");
    ints_fget(f, 'E', "Execution");
    ints_fget(f, 'e', "Without Read");
}

//----------------/Sequencial-----------------------------------------------------------------------//

//----------------Main-----------------------------------------------------------------------//

int main(int argc, char *argv[]) {
    char *filename = NULL;
    if (argc >= 2)
        filename = argv[1];

    test_media(filename);
    return (0);
}
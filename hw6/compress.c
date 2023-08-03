#include "students.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

static void usage(const char *prog_name);

void compress(FILE *file);
void extract(FILE *file);

int main(int argc, char *argv[])
{
        if (argc != 3) {
                usage(argv[0]);
        }

        bool to_compress = false;
        if (strcmp(argv[1], "-c") == 0 || strcmp(argv[1], "--compress") == 0) {
                to_compress = true;
        } else if (strcmp(argv[1], "-x") == 0 ||
                        strcmp(argv[1], "--extract") == 0) {
                to_compress = false;
        } else {
                usage(argv[0]);
        }

        FILE *file;
        if (strcmp(argv[2], "-") == 0) {
                file = stdin;
        } else {
                file = fopen(argv[2], "r");
                if (file == NULL) {
                        printf("cannot open file '%s'\n", argv[2]);
                        usage(argv[0]);
                }
        }

        if (to_compress) {
                compress(file);
        } else {
                extract(file);
        }

        if (file != stdin) {
                fclose(file);
        }

        return 0;
}

static void usage(const char *prog_name)
{
        printf("usage: %s [-c|-x] <file>\n", prog_name);
        printf("\t-c,--compress\t(c)ompress a student record file\n");
        printf("\t-x,--extract\te(x)tract a compressed file\n");
        printf("\t<file>\t the filename. If the filename is \"-\","
               " then the program will read from the standard input.\n");

        exit(EXIT_FAILURE);
}

const uint64_t ONES = ~(uint64_t) 0;
const uint64_t UCID_MASK = ONES >> (64 - 24) << 15;
const uint64_t LATE_MASK = ONES >> (64 - 2) << 13;
const uint64_t POINT_MASK = ONES >> (64 - 4) << 9;
const uint64_t GRADE_MASK = ONES >> (64 - 3) << 6;
const uint64_t MAJOR_MASK = ONES >> (64 - 6);

const char FILE_HEADER[] = "CS143 student binary format\n";

void compress(FILE *file)
{
        printf("%s", FILE_HEADER);

        struct student *s;
        while ((s = student_read(file)) != NULL) {
                uint64_t word = 0;

                uint64_t ucid = s->ucid - 10000000;
                word |= ucid << 15;
                word |= (uint64_t) s->late_days << 13;
                word |= ((int64_t) s->point_adjust << 9) & POINT_MASK;

                uint64_t grade = (s->grade == 'F') ? 4 : s->grade - 'A';
                word |= grade << 6;

                uint64_t major = s->major;
                word |= major;

                for (int i = 4; i >= 0; i--) {
                        uint8_t byte = word >> (i * 8);
                        putchar(byte);
                }

                for (int i = 0; i < 17; i++) {
                        putchar(s->hometown[i]);
                }
                student_free(s);
        }
}

void extract(FILE *file)
{
        /* This block of code checks if the file format has the expected header.
         * If the header is not found, this function returns immediately. */
        char *header_line = NULL;
        size_t linecap;
        getline(&header_line, &linecap, file);
        if (strcmp(header_line, FILE_HEADER) != 0) {
                fprintf(stderr, "wrong binary format\n");
                return;
        }
        free(header_line);

        while (!feof(file)) {
                uint64_t word = 0;
                for (int i = 4; i >= 0; i--) {
                        int byte = fgetc(file);
                        if (byte == EOF) {
                                return;
                        }
                        word |= (uint64_t) byte << (i * 8);
                }

                char hometown[18] = { 0 };
                for (int i = 0; i < 17; i++) {
                        int byte = fgetc(file);
                        assert(byte != EOF);
                        hometown[i] = byte;
                }

                uint32_t ucid = ((word & UCID_MASK) >> 15) + 10000000;
                uint8_t late_days = (word & LATE_MASK) >> 13;
                int8_t point_adjust = (int64_t) (word & POINT_MASK) << 51 >> 60;
                char grade = ((word & GRADE_MASK) >> 6) + 'A';
                if (grade == 'E') {
                        grade = 'F';
                }

                enum major major = word & MAJOR_MASK;

                struct student *s = student_create(ucid, late_days,
                                point_adjust, grade, major, hometown);
                student_write(s, stdout);
                student_free(s);
        }
}


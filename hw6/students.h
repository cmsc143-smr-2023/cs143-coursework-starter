#ifndef STUDENTS_H_
#define STUDENTS_H_

#include <stdio.h>
#include <stdint.h>

enum major {
        ANTHROPOLOGY = 0,
        ARCHITECTURAL_STUDIES,
        ART_HISTORY,
        ASTRONOMY_ASTROPHYSICS,
        BIG_PROBLEMS,
        BIOLOGICAL_CHEMISTRY,
        BIOLOGICAL_SCIENCES,
        CHEMISTRY,
        CHICAGO_STUDIES,
        CINEMA_MEDIA_STUDIES,
        CLASSICAL_STUDIES,
        CLINICAL_TRANSLATIONAL_SCIENCE,
        COMPARATIVE_HUMAN_DEVELOPMENT,
        COMPARATIVE_LITERATURE,
        COMPUTATIONAL_APPLIED_MATHEMATICS,
        COMPUTATIONAL_NEUROSCIENCE,
        COMPUTER_SCIENCE,
        CREATIVE_WRITING,
        DEMOCRACY_STUDIES,
        DIGITAL_STUDIES_OF_LANGUAGE_CULTURE_HISTORY,
        EAST_ASIAN_LANGUAGES_CIVILIZATIONS,
        ECONOMICS,
        ENGLISH_LANGUAGE_LITERATURE,
        ENVIRONMENTAL_URBAN_STUDIES,
        ENVIRONMENTAL_SCIENCE,
        ISSUES_TEXTS,
        GENDER_SEXUALITY_STUDIES,
        GEOGRAPHIC_INFORMATION_SCIENCE,
        GEOPHYSICAL_SCIENCES,
        GERMANIC_STUDIES,
        GLOBAL_STUDIES,
        HISTORY,
        HISTORY_PHILOSOPHY_SOCIAL_STUDIES_OF_SCIENCE_MEDICINE,
        HUMAN_RIGHTS,
        INQUIRY_RESEARCH_IN_THE_HUMANITIES,
        INSTITUTE_FOR_THE_FORMATION_OF_KNOWLEDGE,
        JEWISH_STUDIES,
        LATIN_AMERICAN_CARIBBEAN_STUDIES,
        LAW_LETTERS_SOCIETY,
        LINGUISTICS,
        MATHEMATICS,
        MEDIA_ARTS_DESIGN,
        MEDIEVAL_STUDIES,
        MOLECULAR_ENGINEERING,
        MUSIC,
        NEAR_EASTERN_LANGUAGES_CIVILIZATIONS,
        NEUROSCIENCE,
        NORWEGIAN_STUDIES,
        PHILOSOPHY,
        PHYSICS,
        POLITICAL_SCIENCE,
        PROFESSIONAL_OPTION_MEDICINE,
        PSYCHOLOGY,
        PUBLIC_POLICY_STUDIES,
        RACE_DIASPORA_INDIGENEITY,
        RELIGIOUS_STUDIES,
        RENAISSANCE_STUDIES,
        ROMANCE_LANGUAGES_LITERATURES,
        RUSSIAN_EAST_EUROPEAN_STUDIES,
        SOCIOLOGY,
        SOUTH_ASIAN_LANGUAGES_CIVILIZATIONS,
        STATISTICS,
        THEATER_PERFORMANCE_STUDIES,
        VISUAL_ARTS,
        /* there are 64 majors */
};

struct student {
        uint32_t   ucid;         /* from 10000000 to 19999999 (inclusive) */
        uint8_t    late_days;    /* from 0 to 3 (inclusive) */
        int8_t     point_adjust; /* from -5 to 5 (inclusive) */
        char       grade;        /* 'A', 'B', 'C', 'D', or 'F' */
        enum major major;        /* major */
        char       hometown[18]; /* the name of hometown <= 17 characters */
};

/* 24 2 4 3 6 */


/* create a heap-allocated student record based on the arguments.
 *
 * The arguments are validated in the function. If any field is outside of the
 * expected values, the function will abort().
 */
struct student *student_create(uint32_t ucid,
                               uint8_t late_days,
                               int8_t point_adjust,
                               char grade,
                               enum major major,
                               char *hometown);

/* read one student record from the file. The student record is heap-allocated.
 *
 * If the file pointer reaches EOF, the function will return NULL. If the file
 * format cannot be recognized, this function will call exit(EXIT_FAILURE) and
 * prints a message to stderr.
 */
struct student *student_read(FILE *file);

/* print a student record to file. */
void student_write(struct student *student, FILE *file);

/* deallocate a student record */
void student_free(struct student *student);

#endif

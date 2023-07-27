#include "students.h"

#include <assert.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static inline enum major major_number(char major_name[]);
static inline const char *major_name(enum major major);

#define STUDENT_FORMAT_I "%"SCNu32"\t%"SCNu8"\t%"SCNi8"\t%c\t%63[^\t]\t%17[^\n]\n"
#define STUDENT_FORMAT_O "%"PRIu32"\t%"PRIu8"\t%"PRIi8"\t%c\t%s\t%s\n"

struct student *student_create(uint32_t ucid,
                               uint8_t late_days,
                               int8_t point_adjust,
                               char grade,
                               enum major major,
                               char *hometown)
{
        struct student *s = calloc(1, sizeof *s);

        if (!(10000000 <= ucid && ucid < 20000000)) {
                fprintf(stderr, "UCID out of range: %08d", ucid);
                abort();
        }
        if (!(late_days <= 3)) {
                fprintf(stderr, "late days out of range: %d\n", late_days);
                abort();
        }
        if (!(-5 <= point_adjust && point_adjust <= 5)) {
                fprintf(stderr, "point adjustment out of range: %d\n",
                                point_adjust);
                abort();
        }
        if (!(grade == 'A' || grade == 'B' || grade == 'C' || grade == 'D' ||
              grade == 'F')) {
                fprintf(stderr, "invalid grade `%c`\n", grade);
                abort();
        }
        if (!(strlen(hometown) <= 17)) {
                fprintf(stderr, "hometown name `%s` too long\n", hometown);
                abort();
        }

        s->ucid = ucid;
        s->late_days = late_days;
        s->point_adjust = point_adjust;
        s->grade = grade;
        s->major = major;
        strcpy(s->hometown, hometown);

        return s;
}

struct student *student_read(FILE *file)
{
        if (feof(file)) {
                /* if the file has nothing more to read, return NULL */
                return NULL;
        }

        struct student *s = malloc(sizeof *s);

        char major_name[64];

        /* fscanf is the opposite of fprintf. It ``scans'' the file according to
         * a particular format, and returns how many of the fields are scanned
         * correctly. */
        int n = fscanf(file, STUDENT_FORMAT_I,
                       &s->ucid,
                       &s->late_days,
                       &s->point_adjust,
                       &s->grade,
                       major_name,
                       s->hometown);

        if (n != 6) {
                fprintf(stderr, "cannot read student file\n");
                exit(EXIT_FAILURE);
        }

        enum major major = major_number(major_name);

        if (major < 0) {
                fprintf(stderr, "major '%s' doesn't exist\n", major_name);
                exit(EXIT_FAILURE);
        }
        s->major = major;

        return s;
}

void student_write(struct student *student, FILE *file)
{
        assert(student != NULL);
        fprintf(file, STUDENT_FORMAT_O,
                student->ucid,
                student->late_days,
                student->point_adjust,
                student->grade,
                major_name(student->major),
                student->hometown);
}

void student_free(struct student *student)
{
        free(student);
}

static inline enum major major_number(char major_name[])
{
        if (strcmp(major_name, "Anthropology") == 0) {
                return ANTHROPOLOGY;
        } else if (strcmp(major_name, "Architectural Studies") == 0) {
                return ARCHITECTURAL_STUDIES;
        } else if (strcmp(major_name, "Art History") == 0) {
                return ART_HISTORY;
        } else if (strcmp(major_name, "Astronomy and Astrophysics") == 0) {
                return ASTRONOMY_ASTROPHYSICS;
        } else if (strcmp(major_name, "Big Problems") == 0) {
                return BIG_PROBLEMS;
        } else if (strcmp(major_name, "Biological Chemistry") == 0) {
                return BIOLOGICAL_CHEMISTRY;
        } else if (strcmp(major_name, "Biological Sciences") == 0) {
                return BIOLOGICAL_SCIENCES;
        } else if (strcmp(major_name, "Chemistry") == 0) {
                return CHEMISTRY;
        } else if (strcmp(major_name, "Chicago Studies") == 0) {
                return CHICAGO_STUDIES;
        } else if (strcmp(major_name, "Cinema and Media Studies") == 0) {
                return CINEMA_MEDIA_STUDIES;
        } else if (strcmp(major_name, "Classical Studies") == 0) {
                return CLASSICAL_STUDIES;
        } else if (strcmp(major_name, "Clinical and Translational Science") == 0) {
                return CLINICAL_TRANSLATIONAL_SCIENCE;
        } else if (strcmp(major_name, "Comparative Human Development") == 0) {
                return COMPARATIVE_HUMAN_DEVELOPMENT;
        } else if (strcmp(major_name, "Comparative Literature") == 0) {
                return COMPARATIVE_LITERATURE;
        } else if (strcmp(major_name, "Computational and Applied Mathematics") == 0) {
                return COMPUTATIONAL_APPLIED_MATHEMATICS;
        } else if (strcmp(major_name, "Computational Neuroscience") == 0) {
                return COMPUTATIONAL_NEUROSCIENCE;
        } else if (strcmp(major_name, "Computer Science") == 0) {
                return COMPUTER_SCIENCE;
        } else if (strcmp(major_name, "Creative Writing") == 0) {
                return CREATIVE_WRITING;
        } else if (strcmp(major_name, "Democracy Studies") == 0) {
                return DEMOCRACY_STUDIES;
        } else if (strcmp(major_name, "Digital Studies of Language, Culture, and History") == 0) {
                return DIGITAL_STUDIES_OF_LANGUAGE_CULTURE_HISTORY;
        } else if (strcmp(major_name, "East Asian Languages and Civilizations") == 0) {
                return EAST_ASIAN_LANGUAGES_CIVILIZATIONS;
        } else if (strcmp(major_name, "Economics") == 0) {
                return ECONOMICS;
        } else if (strcmp(major_name, "English Language and Literature") == 0) {
                return ENGLISH_LANGUAGE_LITERATURE;
        } else if (strcmp(major_name, "Environmental and Urban Studies") == 0) {
                return ENVIRONMENTAL_URBAN_STUDIES;
        } else if (strcmp(major_name, "Environmental Science") == 0) {
                return ENVIRONMENTAL_SCIENCE;
        } else if (strcmp(major_name, "Issues and Texts") == 0) {
                return ISSUES_TEXTS;
        } else if (strcmp(major_name, "Gender and Sexuality Studies") == 0) {
                return GENDER_SEXUALITY_STUDIES;
        } else if (strcmp(major_name, "Geographic Information Science") == 0) {
                return GEOGRAPHIC_INFORMATION_SCIENCE;
        } else if (strcmp(major_name, "Geophysical Sciences") == 0) {
                return GEOPHYSICAL_SCIENCES;
        } else if (strcmp(major_name, "Germanic Studies") == 0) {
                return GERMANIC_STUDIES;
        } else if (strcmp(major_name, "Global Studies") == 0) {
                return GLOBAL_STUDIES;
        } else if (strcmp(major_name, "History") == 0) {
                return HISTORY;
        } else if (strcmp(major_name, "History, Philosophy, and Social Studies of Science and Medicine") == 0) {
                return HISTORY_PHILOSOPHY_SOCIAL_STUDIES_OF_SCIENCE_MEDICINE;
        } else if (strcmp(major_name, "Human Rights") == 0) {
                return HUMAN_RIGHTS;
        } else if (strcmp(major_name, "Inquiry and Research in the Humanities") == 0) {
                return INQUIRY_RESEARCH_IN_THE_HUMANITIES;
        } else if (strcmp(major_name, "Institute for the Formation of Knowledge") == 0) {
                return INSTITUTE_FOR_THE_FORMATION_OF_KNOWLEDGE;
        } else if (strcmp(major_name, "Jewish Studies") == 0) {
                return JEWISH_STUDIES;
        } else if (strcmp(major_name, "Latin American and Caribbean Studies") == 0) {
                return LATIN_AMERICAN_CARIBBEAN_STUDIES;
        } else if (strcmp(major_name, "Law, Letters, and Society") == 0) {
                return LAW_LETTERS_SOCIETY;
        } else if (strcmp(major_name, "Linguistics") == 0) {
                return LINGUISTICS;
        } else if (strcmp(major_name, "Mathematics") == 0) {
                return MATHEMATICS;
        } else if (strcmp(major_name, "Media Arts and Design") == 0) {
                return MEDIA_ARTS_DESIGN;
        } else if (strcmp(major_name, "Medieval Studies") == 0) {
                return MEDIEVAL_STUDIES;
        } else if (strcmp(major_name, "Molecular Engineering") == 0) {
                return MOLECULAR_ENGINEERING;
        } else if (strcmp(major_name, "Music") == 0) {
                return MUSIC;
        } else if (strcmp(major_name, "Near Eastern Languages and Civilizations") == 0) {
                return NEAR_EASTERN_LANGUAGES_CIVILIZATIONS;
        } else if (strcmp(major_name, "Neuroscience") == 0) {
                return NEUROSCIENCE;
        } else if (strcmp(major_name, "Norwegian Studies") == 0) {
                return NORWEGIAN_STUDIES;
        } else if (strcmp(major_name, "Philosophy") == 0) {
                return PHILOSOPHY;
        } else if (strcmp(major_name, "Physics") == 0) {
                return PHYSICS;
        } else if (strcmp(major_name, "Political Science") == 0) {
                return POLITICAL_SCIENCE;
        } else if (strcmp(major_name, "Professional Option: Medicine") == 0) {
                return PROFESSIONAL_OPTION_MEDICINE;
        } else if (strcmp(major_name, "Psychology") == 0) {
                return PSYCHOLOGY;
        } else if (strcmp(major_name, "Public Policy Studies") == 0) {
                return PUBLIC_POLICY_STUDIES;
        } else if (strcmp(major_name, "Race, Diaspora, and Indigeneity") == 0) {
                return RACE_DIASPORA_INDIGENEITY;
        } else if (strcmp(major_name, "Religious Studies") == 0) {
                return RELIGIOUS_STUDIES;
        } else if (strcmp(major_name, "Renaissance Studies") == 0) {
                return RENAISSANCE_STUDIES;
        } else if (strcmp(major_name, "Romance Languages and Literatures") == 0) {
                return ROMANCE_LANGUAGES_LITERATURES;
        } else if (strcmp(major_name, "Russian and East European Studies") == 0) {
                return RUSSIAN_EAST_EUROPEAN_STUDIES;
        } else if (strcmp(major_name, "Sociology") == 0) {
                return SOCIOLOGY;
        } else if (strcmp(major_name, "South Asian Languages and Civilizations") == 0) {
                return SOUTH_ASIAN_LANGUAGES_CIVILIZATIONS;
        } else if (strcmp(major_name, "Statistics") == 0) {
                return STATISTICS;
        } else if (strcmp(major_name, "Theater and Performance Studies") == 0) {
                return THEATER_PERFORMANCE_STUDIES;
        } else if (strcmp(major_name, "Visual Arts") == 0) {
                return VISUAL_ARTS;
        } else {
                return -1;
        }
}

static inline const char *major_name(enum major major)
{
        switch (major) {
        case ANTHROPOLOGY:
                return "Anthropology";
        case ARCHITECTURAL_STUDIES:
                return "Architectural Studies";
        case ART_HISTORY:
                return "Art History";
        case ASTRONOMY_ASTROPHYSICS:
                return "Astronomy and Astrophysics";
        case BIG_PROBLEMS:
                return "Big Problems";
        case BIOLOGICAL_CHEMISTRY:
                return "Biological Chemistry";
        case BIOLOGICAL_SCIENCES:
                return "Biological Sciences";
        case CHEMISTRY:
                return "Chemistry";
        case CHICAGO_STUDIES:
                return "Chicago Studies";
        case CINEMA_MEDIA_STUDIES:
                return "Cinema and Media Studies";
        case CLASSICAL_STUDIES:
                return "Classical Studies";
        case CLINICAL_TRANSLATIONAL_SCIENCE:
                return "Clinical and Translational Science";
        case COMPARATIVE_HUMAN_DEVELOPMENT:
                return "Comparative Human Development";
        case COMPARATIVE_LITERATURE:
                return "Comparative Literature";
        case COMPUTATIONAL_APPLIED_MATHEMATICS:
                return "Computational and Applied Mathematics";
        case COMPUTATIONAL_NEUROSCIENCE:
                return "Computational Neuroscience";
        case COMPUTER_SCIENCE:
                return "Computer Science";
        case CREATIVE_WRITING:
                return "Creative Writing";
        case DEMOCRACY_STUDIES:
                return "Democracy Studies";
        case DIGITAL_STUDIES_OF_LANGUAGE_CULTURE_HISTORY:
                return "Digital Studies of Language, Culture, and History";
        case EAST_ASIAN_LANGUAGES_CIVILIZATIONS:
                return "East Asian Languages and Civilizations";
        case ECONOMICS:
                return "Economics";
        case ENGLISH_LANGUAGE_LITERATURE:
                return "English Language and Literature";
        case ENVIRONMENTAL_URBAN_STUDIES:
                return "Environmental and Urban Studies";
        case ENVIRONMENTAL_SCIENCE:
                return "Environmental Science";
        case ISSUES_TEXTS:
                return "Issues and Texts";
        case GENDER_SEXUALITY_STUDIES:
                return "Gender and Sexuality Studies";
        case GEOGRAPHIC_INFORMATION_SCIENCE:
                return "Geographic Information Science";
        case GEOPHYSICAL_SCIENCES:
                return "Geophysical Sciences";
        case GERMANIC_STUDIES:
                return "Germanic Studies";
        case GLOBAL_STUDIES:
                return "Global Studies";
        case HISTORY:
                return "History";
        case HISTORY_PHILOSOPHY_SOCIAL_STUDIES_OF_SCIENCE_MEDICINE:
                return "History, Philosophy, and Social Studies of Science and Medicine";
        case HUMAN_RIGHTS:
                return "Human Rights";
        case INQUIRY_RESEARCH_IN_THE_HUMANITIES:
                return "Inquiry and Research in the Humanities";
        case INSTITUTE_FOR_THE_FORMATION_OF_KNOWLEDGE:
                return "Institute for the Formation of Knowledge";
        case JEWISH_STUDIES:
                return "Jewish Studies";
        case LATIN_AMERICAN_CARIBBEAN_STUDIES:
                return "Latin American and Caribbean Studies";
        case LAW_LETTERS_SOCIETY:
                return "Law, Letters, and Society";
        case LINGUISTICS:
                return "Linguistics";
        case MATHEMATICS:
                return "Mathematics";
        case MEDIA_ARTS_DESIGN:
                return "Media Arts and Design";
        case MEDIEVAL_STUDIES:
                return "Medieval Studies";
        case MOLECULAR_ENGINEERING:
                return "Molecular Engineering";
        case MUSIC:
                return "Music";
        case NEAR_EASTERN_LANGUAGES_CIVILIZATIONS:
                return "Near Eastern Languages and Civilizations";
        case NEUROSCIENCE:
                return "Neuroscience";
        case NORWEGIAN_STUDIES:
                return "Norwegian Studies";
        case PHILOSOPHY:
                return "Philosophy";
        case PHYSICS:
                return "Physics";
        case POLITICAL_SCIENCE:
                return "Political Science";
        case PROFESSIONAL_OPTION_MEDICINE:
                return "Professional Option: Medicine";
        case PSYCHOLOGY:
                return "Psychology";
        case PUBLIC_POLICY_STUDIES:
                return "Public Policy Studies";
        case RACE_DIASPORA_INDIGENEITY:
                return "Race, Diaspora, and Indigeneity";
        case RELIGIOUS_STUDIES:
                return "Religious Studies";
        case RENAISSANCE_STUDIES:
                return "Renaissance Studies";
        case ROMANCE_LANGUAGES_LITERATURES:
                return "Romance Languages and Literatures";
        case RUSSIAN_EAST_EUROPEAN_STUDIES:
                return "Russian and East European Studies";
        case SOCIOLOGY:
                return "Sociology";
        case SOUTH_ASIAN_LANGUAGES_CIVILIZATIONS:
                return "South Asian Languages and Civilizations";
        case STATISTICS:
                return "Statistics";
        case THEATER_PERFORMANCE_STUDIES:
                return "Theater and Performance Studies";
        case VISUAL_ARTS:
                return "Visual Arts";
        default:
                return "UNKNOWN";
        }
}

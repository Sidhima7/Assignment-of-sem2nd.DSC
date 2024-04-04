#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COURSES 10
#define MAX_ASSIGNMENTS 20
#define MAX_STUDENTS 50

// Structure definitions
typedef struct {
    char name[100];
    int assignmentCount;
    float assignmentScores[MAX_STUDENTS][MAX_ASSIGNMENTS];
    float weights[MAX_ASSIGNMENTS];
} Course;

typedef struct {
    int id;
    char name[100];
    float finalGrade;
} Student;

// Function prototypes
void createCourse(Course courses[], int *numCourses);
void addAssignment(Course *course);
void registerStudent(Student students[], int *numStudents);
void enterGrades(Course *course, Student students[], int numStudents);
void calculateFinalGrades(Course *course, int numStudents);
void generateReports(Course courses[], int numCourses, Student students[], int numStudents);

int main() {
    Course courses[MAX_COURSES];
    Student students[MAX_STUDENTS];
    int numCourses = 0, numStudents = 0;
    int choice;

    do {
        printf("\nStudent Grade Tracker\n");
        printf("1. Create Course\n");
        printf("2. Add Assignment\n");
        printf("3. Register Student\n");
        printf("4. Enter Grades\n");
        printf("5. Calculate Final Grades\n");
        printf("6. Generate Reports\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                createCourse(courses, &numCourses);
                break;
            case 2:
                if (numCourses > 0) {
                    addAssignment(&courses[numCourses - 1]);
                } else {
                    printf("Please create a course first.\n");
                }
                break;
            case 3:
                registerStudent(students, &numStudents);
                break;
            case 4:
                if (numCourses > 0 && numStudents > 0) {
                    enterGrades(&courses[numCourses - 1], students, numStudents);
                } else {
                    printf("Please create a course and register students first.\n");
                }
                break;
            case 5:
                if (numCourses > 0 && numStudents > 0) {
                    calculateFinalGrades(&courses[numCourses - 1], numStudents);
                } else {
                    printf("Please create a course and register students first.\n");
                }
                break;
            case 6:
                if (numCourses > 0 && numStudents > 0) {
                    generateReports(courses, numCourses, students, numStudents);
                } else {
                    printf("Please create a course and register students first.\n");
                }
                break;
            case 0:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);

    return 0;
}

void createCourse(Course courses[], int *numCourses) {
    if (*numCourses < MAX_COURSES) {
        printf("Enter course name: ");
        scanf("%s", courses[*numCourses].name);
        printf("Enter number of assignments: ");
        scanf("%d", &courses[*numCourses].assignmentCount);
        for (int i = 0; i < courses[*numCourses].assignmentCount; i++) {
            printf("Enter weight for assignment %d: ", i + 1);
            scanf("%f", &courses[*numCourses].weights[i]);
        }
        (*numCourses)++;
        printf("Course created successfully.\n");
    } else {
        printf("Maximum courses reached.\n");
    }
}

void addAssignment(Course *course) {
    if (course->assignmentCount < MAX_ASSIGNMENTS) {
        printf("Enter assignment name: ");
        scanf("%s", course->name);
        (course->assignmentCount)++;
        printf("Assignment added successfully.\n");
    } else {
        printf("Maximum assignments reached for this course.\n");
    }
}

void registerStudent(Student students[], int *numStudents) {
    if (*numStudents < MAX_STUDENTS) {
        printf("Enter student ID: ");
        scanf("%d", &students[*numStudents].id);
        printf("Enter student name: ");
        scanf("%s", students[*numStudents].name);
        (*numStudents)++;
        printf("Student registered successfully.\n");
    } else {
        printf("Maximum students reached.\n");
    }
}

void enterGrades(Course *course, Student students[], int numStudents) {
    for (int i = 0; i < numStudents; i++) {
        printf("Enter grades for student %s:\n", students[i].name);
        for (int j = 0; j < course->assignmentCount; j++) {
            printf("Enter grade for assignment %d: ", j + 1);
            scanf("%f", &course->assignmentScores[i][j]);
        }
    }
    printf("Grades entered successfully.\n");
}

void calculateFinalGrades(Course *course, int numStudents) {
    for (int i = 0; i < numStudents; i++) {
        float finalGrade = 0;
        for (int j = 0; j < course->assignmentCount; j++) {
            finalGrade += course->assignmentScores[i][j] * course->weights[j];
        }
        course->assignmentScores[i][course->assignmentCount] = finalGrade;
    }
    printf("Final grades calculated successfully.\n");
}

void generateReports(Course courses[], int numCourses, Student students[], int numStudents) {
    // Report on individual student performance
    printf("Student Performance Report:\n");
    for (int i = 0; i < numStudents; i++) {
        printf("Student ID: %d, Name: %s, Final Grade: %.2f\n", students[i].id, students[i].name, students[i].finalGrade);
    }
    printf("\n");

    // Report on class averages
    printf("Class Averages Report:\n");
    for (int i = 0; i < numCourses; i++) {
        float totalGrade = 0;
        for (int j = 0; j < numStudents; j++) {
            totalGrade += courses[i].weights[j];
        }
        float classAverage = totalGrade / numStudents;
        printf("Course: %s, Class Average: %.2f\n", courses[i].name, classAverage);
    }
    printf("\n");

    // Report on grade distribution
    printf("Grade Distribution Report:\n");
    int gradeCounts[5] = {0}; // Assuming grading scale of 5 levels
    for (int i = 0; i < numStudents; i++) {
        if (students[i].finalGrade >= 90) {
            gradeCounts[0]++;
        } else if (students[i].finalGrade >= 80) {
            gradeCounts[1]++;
        } else if (students[i].finalGrade >= 70) {
            gradeCounts[2]++;
        } else if (students[i].finalGrade >= 60) {
            gradeCounts[3]++;
        } else {
            gradeCounts[4]++;
        }
    }
    printf("A (90-100): %d\n", gradeCounts[0]);
    printf("B (80-89): %d\n", gradeCounts[1]);
    printf("C (70-79): %d\n", gradeCounts[2]);
    printf("D (60-69): %d\n", gradeCounts[3]);
    printf("F (<60): %d\n", gradeCounts[4]);
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LEN 100

#define FILE_USERS "users.csv"
#define FILE_BOOKS "books.csv"
#define FILE_STUDENTS "students.csv"
#define FILE_STUDENTS_BOOKS "student_books.csv"


#define LOGIN_SUCCSESFULLY 0
#define LOGIN_FAILED 1

#define EXIT -1

typedef struct User
{
    char login[MAX_LEN];
    char password[MAX_LEN];
    int accessBooks;
    int accessStudents;
} User;
typedef struct Book
{
    char isbn[MAX_LEN];
    char author[MAX_LEN];
    char name[MAX_LEN];
    int quantAll;
    int quantTaken;
} Book;
typedef struct Student
{
    char num[MAX_LEN];
    char name[MAX_LEN];
    char surname[MAX_LEN];
    char sec_name[MAX_LEN];
    char fac[MAX_LEN];
    char kaf[MAX_LEN];
} Student;
typedef struct StudentsBook
{
    char isbn[MAX_LEN];
    char num[MAX_LEN];
    char date[MAX_LEN];
} StudentsBook;

User *users = NULL;
Book *books = NULL;
Student *students = NULL;
StudentsBook *studentsbooks = NULL;

int sizeOfUsers;
int sizeOfBooks;
int sizeOfStudents;
int sizeOfStudentsBook;

void PrintUsers(int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("User %d\n", i+1);
        printf("Login: %s\n", users[i].login);
        printf("Password: %s\n", users[i].password);
        printf("AccessBooks: %d\n", users[i].accessBooks);
        printf("AccessStudents: %d\n", users[i].accessStudents);
    }
}
void PrintBooks()
{
    for (int i = 0; i < sizeOfBooks; i++)
    {
        printf("%s\n", books[i].isbn);
        printf("%s\n", books[i].author);
        printf("%s\n", books[i].name);
        printf("%d\n", books[i].quantAll);
        printf("%d\n", books[i].quantTaken);
    }
}
void PrintStudents()
{
    for (int i = 0; i < sizeOfStudents; i++)
    {
        printf("%s\n", students[i].num);
        printf("%s\n", students[i].name);
        printf("%s\n", students[i].surname);
        printf("%s\n", students[i].sec_name);
        printf("%s\n", students[i].fac);
        printf("%s\n", students[i].kaf);
    }
}
int GetSizeOfFile(FILE *f)
{
    int k = 0;
    char s[MAX_LEN];

    while (!feof(f))
        if (fgets(s, MAX_LEN, f))
            if (s[0] != '\n')
                k++;
    fseek(f, 0, SEEK_SET);
    return k;
}

User * LoadUsers()
{
    FILE *usersFile = fopen(FILE_USERS, "r");
    if(usersFile == NULL){
        printf("No file: %s\n", FILE_USERS);
        exit(9);
    }

    sizeOfUsers = GetSizeOfFile(usersFile);

    User cur;
    char s[MAX_LEN];

    User *us;
    void *ptr = malloc((sizeOfUsers) * sizeof(User));
    us = (User *)ptr;

    char aB[5], aS[5];

    int i = 0;
    while (!feof(usersFile))
    {
        if (fgets(s, MAX_LEN, usersFile))
        {
            if (s[0] != '\n')
            {
                strcpy(cur.login, strtok(s, ";"));
                strcpy(cur.password, strtok(NULL, ";"));
                strcpy(aB, strtok(NULL, ";"));
                strcpy(aS, strtok(NULL, ";"));

                cur.accessBooks = (int) strtol(aB, (char **)NULL, 10);
                cur.accessStudents = (int) strtol(aS, (char **)NULL, 10);

                us[i] = cur;
                i++;
            }
        }
    }
    fclose(usersFile);
    return us;
}
StudentsBook * LoadStudentsBooks()
{
    FILE *StudentsBookFile = fopen(FILE_STUDENTS_BOOKS, "r");
    if(StudentsBookFile == NULL){
        printf("No file: %s\n", FILE_STUDENTS_BOOKS);
        exit(9);
    }

    sizeOfStudentsBook = GetSizeOfFile(StudentsBookFile);

    StudentsBook cur;
    char s[MAX_LEN];

    StudentsBook *us;
    void *ptr = malloc((sizeOfStudentsBook) * sizeof(StudentsBook));
    us = (StudentsBook *)ptr;


    int i = 0;
    while (!feof(StudentsBookFile))
    {
        if (fgets(s, MAX_LEN, StudentsBookFile))
        {
            if (s[0] != '\n')
            {
                strcpy(cur.isbn, strtok(s, ";"));
                strcpy(cur.num, strtok(NULL, ";"));
                strcpy(cur.date, strtok(NULL, "\n"));

                us[i] = cur;
                i++;
            }
        }
    }
    fclose(StudentsBookFile);
    return us;
}
Student * LoadStudents()
{
    FILE *studentsFile = fopen(FILE_STUDENTS, "r");
    if(studentsFile == NULL){
        printf("No file: %s\n", FILE_STUDENTS);
        exit(9);
    }
    sizeOfStudents = GetSizeOfFile(studentsFile);

    Student cur;
    char s[MAX_LEN];

    Student *stud;
    void *ptr = malloc((sizeOfStudents) * sizeof(Student));
    stud = (Student *)ptr;

    int i = 0;
    while (!feof(studentsFile))
    {
        if (fgets(s, MAX_LEN, studentsFile))
        {
            if (s[0] != '\n')
            {
                strcpy(cur.num, strtok(s, ";"));
                strcpy(cur.name, strtok(NULL, ";"));
                strcpy(cur.surname, strtok(NULL, ";"));
                strcpy(cur.sec_name, strtok(NULL, ";"));
                strcpy(cur.fac, strtok(NULL, ";"));
                strcpy(cur.kaf, strtok(NULL, "\n"));

                stud[i] = cur;
                i++;
            }
        }
    }

    fclose(studentsFile);
    return stud;
}
Book * LoadBooks()
{
    FILE *booksFile = fopen(FILE_BOOKS, "r");
    if(booksFile == NULL){
        printf("No file: %s\n", FILE_BOOKS);
        exit(9);
    }
    sizeOfBooks = GetSizeOfFile(booksFile);

    Book cur;
    char s[MAX_LEN];

    Book *b;
    void *ptr = malloc((sizeOfBooks) * sizeof(Book));
    b = (Book *)ptr;

    char qA[5], qT[5];

    int i = 0;
    while (!feof(booksFile))
    {
        if (fgets(s, MAX_LEN, booksFile))
        {
            if (s[0] != '\n')
            {
                strcpy(cur.isbn, strtok(s, ";"));
                strcpy(cur.author, strtok(NULL, ";"));
                strcpy(cur.name, strtok(NULL, ";"));
                strcpy(qA, strtok(NULL, ";"));
                strcpy(qT, strtok(NULL, ";"));

                cur.quantAll = (int) strtol(qA, (char **)NULL, 10);
                cur.quantTaken = (int) strtol(qT, (char **)NULL, 10);

                b[i] = cur;
                i++;
            }
        }
    }
    fclose(booksFile);
    return b;
}

int Authentication(int *permission)
{
    char login[MAX_LEN];
    char password[MAX_LEN];
    printf("Login: ");
    scanf("%s", login);
    printf("Password: ");
    scanf("%s", password);

    for (int i = 0; i < sizeOfUsers; i++)
    {
        if (!strcmp(login, users[i].login) &&
            !strcmp(password, users[i].password))
            {
                permission[0] = users[i].accessBooks;
                permission[1] = users[i].accessStudents;
                return LOGIN_SUCCSESFULLY;
            }
    }
    return LOGIN_FAILED;
}
void AddBook()
{
    Book cur;
    char isbn[MAX_LEN];
    char author[MAX_LEN];
    char name[MAX_LEN];
    int q;

    printf("Input isbn: ");
    scanf("%s", isbn);
    strcpy(cur.isbn, isbn);
    for(int i=0; i<sizeOfBooks; i++)
    {
        if(strcmp(books[i].isbn, isbn) == 0){
            printf("This ISBN exist\n");
            return;
        }
    }

    printf("Input author: ");
    scanf("%s", author);
    strcpy(cur.author, author);

    printf("Input name: ");
    scanf("%s", name);
    strcpy(cur.name, name);

    printf("Input quantity: ");
    scanf("%d", &q);
    cur.quantAll = q;
    cur.quantTaken = 0;

    books = (Book *) realloc(books, sizeof(books) + sizeof(Book));
    books[sizeOfBooks] = cur;
    sizeOfBooks++;
}
void DeleteBook()
{
    char isbn[MAX_LEN];
    printf("Input isbn: ");
    scanf("%s", isbn);

    int index = -1;
    for (int i = 0; i < sizeOfBooks; i++)
    {
        if (!strcmp(books[i].isbn, isbn))
        {
            index = i;
            break;
        }
    }
    if (index != -1)
    {
        Book *newBooks = (Book *) malloc(sizeof(Book) * (sizeOfBooks - 1));
        for (int i = 0, j = 0; i < sizeOfBooks; i++)
        {
            if (i != index)
            {
                newBooks[j++] = books[i];
            }
        }
        free(books);
        books = newBooks;
        sizeOfBooks--;
    }
    else
        printf("\nThe book hasn't found!\n");

}
void GiveBookToStudent()
{
    char isbn[MAX_LEN];
    printf("Input isbn: ");
    scanf("%s", isbn);
    
    char student[MAX_LEN];
    printf("Input number of student: ");
    scanf("%s", student);

    for (int i = 0; i < sizeOfBooks; i++)
    {
        if (!strcmp(books[i].isbn, isbn))
        {
            if (books[i].quantAll - books[i].quantTaken != 0)
            {
                for(int j=0; j<sizeOfStudents; j++)
                {
                    if (!strcmp(students[j].num, student))
                    {
                        FILE *studentbooksFile = fopen(FILE_STUDENTS_BOOKS, "a+");
                        if(studentbooksFile == NULL)
                        {
                            printf("No file: %s\n", FILE_STUDENTS_BOOKS);
                            exit(9);
                        }
//                        char date[MAX_LEN] = {0};
//                        long int s_time = time(NULL);
//                        struct tm *m_time = localtime(&s_time);
//                        strftime(date, MAX_LEN, "%d.%m.%Y", m_time);
                        char date[MAX_LEN];
                        printf("Input date (format dd.mm.yyyy): ");
                        scanf("%s", date);


                        fprintf(studentbooksFile, "%s;%s;%s\n", isbn, student, date);
                        fclose(studentbooksFile);
                        
                        
                        books[i].quantTaken++;
                        return;
                    }
                }
                printf("\nThe student hasn't found!\n");
                return;
            }
            else
                printf("\nAll books are taken! Come back later!\n");
            break;
        }
    }
    printf("\nThe book hasn't found!\n");
}
void GetBookFromStudent()
{
    char isbn[MAX_LEN];
    printf("Input isbn: ");
    scanf("%s", isbn);

    for (int i = 0; i < sizeOfBooks; i++)
    {
        if (!strcmp(books[i].isbn, isbn))
        {
            if (books[i].quantTaken != 0)
            {
                char student[MAX_LEN];
                printf("Input number of student: ");
                scanf("%s", student);

                for(int j = 0; j < sizeOfStudents; j++)
                {
                    if (!strcmp(students[j].num, student))
                    {
                        studentsbooks = LoadStudentsBooks();
                        FILE *StudentsBookFile = fopen(FILE_STUDENTS_BOOKS, "w");
                        if(StudentsBookFile == NULL){
                            printf("No file: %s\n", FILE_STUDENTS_BOOKS);
                            exit(9);
                        }
                        setbuf(StudentsBookFile, NULL); 
                        int one_time_to_do = 0;
                        for (int i = 0; i < sizeOfStudentsBook; i++)
                        {
                            if(!(strcmp(studentsbooks[i].isbn, isbn) == 0 && strcmp(studentsbooks[i].num, student) == 0 && one_time_to_do == 0))
                            {
                                fprintf(StudentsBookFile, "%s;%s;%s\n", studentsbooks[i].isbn,
                                                                    studentsbooks[i].num,
                                                                    studentsbooks[i].date);
                            }
                            else
                            {
                                one_time_to_do = 1;
                            }
                        }

                        fclose(StudentsBookFile);

                        books[i].quantTaken--;
                        return;
                    }
                }
                printf("\nThis student not exist\n");
                return;
            }
            else
            {
                printf("\nThis book is not taken!\n");
            }
            return;
        }
    }
    printf("\nThis student not exist\n");
}
void CloseBooks()
{
    FILE *booksFile = fopen(FILE_BOOKS, "w");
    if(booksFile == NULL){
        printf("No file: %s\n", FILE_BOOKS);
        exit(9);
    }
    setbuf(booksFile, NULL); 

    for (int i = 0; i < sizeOfBooks; i++)
    {
        fprintf(booksFile, "%s;%s;%s;%d;%d\n", books[i].isbn,
                                                books[i].author,
                                                books[i].name,
                                                books[i].quantAll,
                                                books[i].quantTaken);
    }

    fclose(booksFile);
}
void AddStudent()
{
    Student cur;
    char s[MAX_LEN];

    printf("Input number of student: ");
    scanf("%s", s);
    strcpy(cur.num, s);
    for(int i=0; i<sizeOfStudents; i++)
    {
        if(strcmp(students[i].num, s) == 0){
            printf("This student exist\n");
            return;
        }
    }


    printf("Input name: ");
    scanf("%s", s);
    strcpy(cur.name, s);

    printf("Input surname: ");
    scanf("%s", s);
    strcpy(cur.surname, s);

    printf("Input second name: ");
    scanf("%s", s);
    strcpy(cur.sec_name, s);

    printf("Input faculty: ");
    scanf("%s", s);
    strcpy(cur.fac, s);

    printf("Input kafedra: ");
    scanf("%s", s);
    strcpy(cur.kaf, s);

    students = (Student *) realloc(students, sizeof(students) + sizeof(Student));
    students[sizeOfStudents] = cur;
    sizeOfStudents++;
}
void DeleteStudent()
{
    char num[MAX_LEN];
    printf("Input number of student: ");
    scanf("%s", num);

    int index = -1;
    for (int i = 0; i < sizeOfStudents; i++)
    {
        if (!strcmp(students[i].num, num))
        {
            index = i;
            break;
        }
    }
    if (index != -1)
    {
        Student *newStudents = (Student *) malloc(sizeof(Student) * (sizeOfStudents - 1));
        for (int i = 0, j = 0; i < sizeOfStudents; i++)
        {
            if (i != index)
            {
                newStudents[j++] = students[i];
            }
        }
        free(students);
        students = newStudents;
        sizeOfStudents--;
    }
    else
        printf("\nThe student hasn't found!\n");

}
void DoBackupStudent()
{
    char date[MAX_LEN] = {0};
    long int s_time = time(NULL);
    struct tm *m_time = localtime(&s_time);
    strftime(date, MAX_LEN, "%d.%m.%Y_%H.%M.%S", m_time);
    
    char filename[MAX_LEN] = {0};
    sprintf(filename, "student_%s.csv", date);
    
    FILE* Backup = fopen(filename, "w");
    if(Backup == NULL){
        printf("Can't create file: %s\n", filename);
        return;
    }

    setbuf(Backup, NULL);

    for (int i = 0; i < sizeOfStudents; i++)
    {
        fprintf(Backup, "%s;%s;%s;%s;%s;%s\n", students[i].num,
                                                students[i].name,
                                                students[i].surname,
                                                students[i].sec_name,
                                                students[i].fac,
                                                students[i].kaf);
    }

    fclose(Backup);
}
void TakeBackupStudent()
{
    char filename[MAX_LEN];
    printf("Input file name: ");
    scanf("%s", filename);

    FILE *Backup = fopen(filename, "r");
    if(Backup == NULL){
        printf("No file: %s\n", filename);
        return;
    }
    FILE *ToPrint = fopen(FILE_STUDENTS, "w");
    if(ToPrint == NULL){
        printf("Can't create file: %s\n", FILE_STUDENTS);
        return;
    }
    char c;
    while((c=fgetc(Backup)) != EOF){
        fputc(c, ToPrint);
    }
    printf("Backup istall sucsessful... RESTART PROGRAMM...");
    exit(0);
    
}
void SearchStudent()
{
    char surname[MAX_LEN];
    printf("Input surname: ");
    scanf("%s", surname);

    for (int i = 0; i < sizeOfStudents; i++)
    {
        if (!strcmp(students[i].surname, surname))
        {
            printf("Number: %s\n ", students[i].num);
            printf("Name: %s\n ", students[i].name);
            printf("Surname: %s\n ", students[i].surname);
            printf("Second name: %s\n ", students[i].sec_name);
            printf("Faculty: %s\n ", students[i].fac);
            printf("Kafedra: %s\n ", students[i].kaf);
            printf("\n");
        }
    }
}
void CloseStudents()
{
    FILE *studentsFile = fopen(FILE_STUDENTS, "w");
    if(studentsFile == NULL){
        printf("No file: %s\n", FILE_STUDENTS);
        exit(9);
    }
    setbuf(studentsFile, NULL);

    for (int i = 0; i < sizeOfStudents; i++)
    {
        fprintf(studentsFile, "%s;%s;%s;%s;%s;%s\n", students[i].num,
                                                students[i].name,
                                                students[i].surname,
                                                students[i].sec_name,
                                                students[i].fac,
                                                students[i].kaf);
    }

    fclose(studentsFile);
}
void BookHandler(int c)
{
    switch(c)
    {
    case 1:
        AddBook();
        break;
    case 2:
        DeleteBook();
        break;
    case 3:
        GiveBookToStudent();
        break;
    case 4:
        GetBookFromStudent();
        break;
    case 5:
        CloseBooks();
        break;
    }
}
void StudentHandler(int c)
{
    switch(c)
    {
    case 1:
        AddStudent();
        break;
    case 2:
        DeleteStudent();
        break;
    case 3:
        DoBackupStudent();
        break;
    case 4:
        TakeBackupStudent();
        break;
    case 5:
        SearchStudent();
        break;
    case 6:
        CloseStudents();
        break;
    }
}
int BookMenu(int flag)
{
    int c;
    printf("1. Add new book\n");
    printf("2. Delete book\n");
    printf("3. Give book to student\n");
    printf("4. Get book from student\n");
    printf("5. Close and save\n");
    if (flag == 1)
        printf("0. Go back\n");
    printf("Input: ");
    scanf("%d", &c);

    return c;
}
int StudentMenu(int flag)
{
    int c;
    printf("1. Add student\n");
    printf("2. Delete student\n");
    printf("3. Save backup\n");
    printf("4. Update from backup\n");
    printf("5. Search student\n");
    printf("6. Close and save\n");
    if (flag == 1)
        printf("0. Go back\n");
    printf("Input: ");
    scanf("%d", &c);

    return c;
}
int Menu()
{
    int c;
    printf("1. Books\n");
    printf("2. Students\n");
    printf("3. Exit\n");
    printf("Input: ");
    scanf("%d", &c);

    if (c == 1)
    {
        while(c != 0 && c != 5)
        {
            c = BookMenu(1);
            BookHandler(c);
        }
    }
    else if (c == 2)
    {
        while(c != 0 && c != 6)
        {
            c = StudentMenu(1);
            StudentHandler(c);
        }
    }
    else if (c == 3)
        c = EXIT;
    else
    {
        printf("\nWrong input!!!\n");
    }
    return c;
}

void ChoiceMenu(int aBooks, int aStudents)
{
    int c = 1;
    if (aBooks == 1 && aStudents == 1)
    {
        while(c != 5 && c != 6)
        {
            c = Menu();
            if (c == EXIT)
            {
                CloseBooks();
                CloseStudents();
                break;
            }

        }
    }
    else if (aBooks == 0 && aStudents == 1)
    {
        while(c != 6)
        {
            c = StudentMenu(0);
            StudentHandler(c);
        }

    }
    else if (aBooks == 1 && aStudents == 0)
    {
        while(c != 5)
        {
            c = BookMenu(0);
            BookHandler(c);
        }

    }
    else if (c == 0) {}
    else
    {
        c = 0;
        printf("\nPermission denied!!!\n");
    }
}

void LoadDataByPermission(int aBooks, int aStudents)
{
    if (aBooks == 1 && aStudents == 1)
    {

        books = LoadBooks();
        students = LoadStudents();

    }
    else if (aBooks == 0 && aStudents == 1)
    {
        students = LoadStudents();
    }
    else if (aBooks == 1 && aStudents == 0)
    {
        books = LoadBooks();
    }
    else
    {
        printf("\nPermission denied!!!\n");
    }
}

int main()
{
    users = LoadUsers();

    int permission[2];

    int a = Authentication(permission);

    if (a == LOGIN_SUCCSESFULLY)
        printf("LOGIN_SUCCSESFULLY\n");
    else
        printf("LOGIN_FAILED\n");

    LoadDataByPermission(permission[0], permission[1]);
    ChoiceMenu(permission[0], permission[1]);

    //free(books);
    //free(users);
    //free(students);
    printf("CLOSING PROGRAM..... INPUT SOME NUMBER");
    int d;
    scanf("%d", &d);
    return 0;
}

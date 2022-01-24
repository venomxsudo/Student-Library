#include <stdio.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#define max_year 9999
#define min_year 1900
#define max_size_user_name 30
#define max_size_psw 20
#define pass_file_name "HSH_Library.bin"
#define max_book_name 50
#define max_author_name 50
#define max_student_name 50
#define max_student_add 300
#define file_header_size sizeof(sFileHeader)

typedef struct
{
    int mm;
    int dd;
    int yyyy;
} Date;

typedef struct
{
    char username[max_size_user_name];
    char password[max_size_psw];
} sFileHeader;
typedef struct // to call in program
{
    unsigned int books_id;              
    char bookName[max_book_name];       
    char authorName[max_author_name];   
    char studentName[max_student_name]; 
    char studentAddr[max_student_add];  
    Date bookIssueDate;                 
} s_BooksInfo;
void printMessageCenter(const char *message)
{
    int len = 0;
    int pos = 0;

    len = (78 - strlen(message)) / 2;
    printf("\t\t\t");
    for (pos = 0; pos < len; pos++)
    {
        // print space
        printf(" ");
    }
    // print message
    printf("%s", message);
}
void headMessage(const char *message)
{
    // system("clear");
    printf("\033[0;37m\n\t\t\t###########################################################################");
    printf("\n\t\t\t############                                                   ############");
    printf("\n\t\t\t############ \033[0;32m     Library management System Project in C  \033[0;37m     ############");
    printf("\n\t\t\t############                                                   ############");
    printf("\n\t\t\t###########################################################################");
    printf("\n\t\t\t---------------------------------------------------------------------------\033[0;37m\n");
    printMessageCenter(message);
    printf("\n\t\t\t---------------------------------------------------------------------------");
}
int welcomeMessage()
{
    headMessage("\033[33m        www.harshmavani.com \033[0;37m");
    printf("\n\n\n\n\n");
    printf("\n\t\t\t   *------------------------------------------------------*\n");
    printf("\n\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    printf("\n\t\t\t        =\033[36m                   WELCOME          \033[0;37m       =");
    printf("\n\t\t\t        =\033[36m                     TO            \033[0;37m        =");
    printf("\n\t\t\t        =\033[36m                   LIBRARY         \033[0;37m        =");
    printf("\n\t\t\t        =\033[36m                 MANAGEMENT       \033[0;37m         =");
    printf("\n\t\t\t        =\033[36m                   SYSTEM         \033[0;37m         =");
    printf("\n\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    printf("\n\t\t\t  *-------------------------------------------------------*\n");
    return 0;
}
int isNameValid(const char *name)
{
    int validName = 1;
    int len = 0;
    int index = 0;
    len = strlen(name);
    for (index = 0; index < len; ++index)
    {

        if (!(isalpha(name[index])) && (name[index] != '\n') && (name[index] != ' '))
        {
            validName = 0;
            break;
        }
    }
    return validName;
}
int IsLeapYear(int year)
{
    return (((year % 4 == 0) &&
             (year % 100 != 0)) ||
            (year % 400 == 0));
}
int isValidDate(Date *validDate)
{
    if (validDate->yyyy > max_year ||
        validDate->yyyy < min_year)
        return 0;
    if (validDate->mm < 1 || validDate->mm > 12)
        return 0;
    if (validDate->dd < 1 || validDate->dd > 31)
        return 0;
    // Handle feb days in leap year
    if (validDate->mm == 2)
    {
        if (IsLeapYear(validDate->yyyy))
            return (validDate->dd <= 29);
        else
            return (validDate->dd <= 28);
    }
    if (validDate->mm == 4 || validDate->mm == 6 ||
        validDate->mm == 9 || validDate->mm == 11)
        return (validDate->dd <= 30);
    return 1;
}
void addBookInDataBase()
{
    int days;
    s_BooksInfo addBookInfoInDataBase = {0};
    FILE *fp = NULL;
    int status = 0;
    fp = fopen(pass_file_name, "ab+");
    if (fp == NULL)
    {
        printf("\033[0;31mFile is not opened\n");
        printf("Please Try With Super User\033[0;37m");
        exit(1);
    }
    headMessage("""\033[1;32m""ADD NEW BOOKS \033[0;37m""");
    printf("\n\n\t\t\t""\033[1;32m"" ENTER YOUR DETAILS BELOW:");
    printf("\n\t\t\t---------------------------------------------------------------------------\n");
    printf("\n\t\t\t""\033[1;33m""Book ID NO  = ");
    scanf("%u", &addBookInfoInDataBase.books_id);
    fflush(stdin);
    fgets(addBookInfoInDataBase.bookName, max_book_name, stdin);
    fflush(stdin);
    printf("\n\t\t\t""\033[1;35m""Book Name  = ");
    fflush(stdin);
    fgets(addBookInfoInDataBase.bookName, max_book_name, stdin);
    fflush(stdin);
    status = isNameValid(addBookInfoInDataBase.bookName);
    if (!status)
    {
        printf("\n\t\t\t""\033[1;31m""Name contain invalid character. Please enter again.");
    }

    while (!status)
        ;
    do
    {
        printf("\n\t\t\t""\033[1;36m""Author Name  = ");
        fflush(stdin);
        fgets(addBookInfoInDataBase.authorName, max_author_name, stdin);
        status = isNameValid(addBookInfoInDataBase.authorName);
        if (!status)
        {
        printf("\n\t\t\t""\033[1;31m""Name contain invalid character. Please enter again.");
        }
    } while (!status);
    do
    {
        printf("\n\t\t\t""\033[1;32m""Student Name  = ");
        fflush(stdin);
        fgets(addBookInfoInDataBase.studentName, max_student_name, stdin);
        status = isNameValid(addBookInfoInDataBase.studentName);
        if (!status)
        {
            printf("\n\t\t\tName contain invalid character. Please enter again.");
        }
    } while (!status);
    do
    {
        printf("\n\t\t\t""\033[1;33m""Enter date in format (day/month/year):");
        scanf("%d/%d/%d\033[0;37m""", &addBookInfoInDataBase.bookIssueDate.dd, &addBookInfoInDataBase.bookIssueDate.mm, &addBookInfoInDataBase.bookIssueDate.yyyy);
        // check date validity
        status = isValidDate(&addBookInfoInDataBase.bookIssueDate);
        if (!status)
        {
            printf("\n\t\t\t""\033[1;31m""Please enter a valid date.\033[0;37m""\n");
        }
    } while (!status);
    fwrite(&addBookInfoInDataBase, sizeof(addBookInfoInDataBase), 1, fp);
    fclose(fp);
}
void searchBooks()
{
    int found = 1;
    char bookName[max_book_name] = {0};
    s_BooksInfo addBookInfoInDataBase = {0};
    FILE *fp = NULL;
    int status = 0;
    fp = fopen(pass_file_name, "rb");
    if (fp == NULL)
    {
        printf("\n\t\t\t\033[0;31m""File is not opened\n");
        printf("Please Try With Super User \033[0;37m""");
        exit(1);
    }
    headMessage("\033[0;33m""SEARCH BOOKS\033[0;37m");
    if (fseek(fp, file_header_size, SEEK_SET) != 0)
    {
        fclose(fp);
        printf("\n\t\t\t\033[0;31m""Facing issue while reading file\033[0;37m""\n");
        exit(1);
    }
    fflush(stdin);
    fgets(bookName, max_book_name, stdin);
    printf("\n\n\t\t\t\033[0;35m""Enter Book Name to search:");
    fflush(stdin);
    fgets(bookName, max_book_name, stdin);
    printf("\033[0;37m");
    while (fread(&addBookInfoInDataBase, sizeof(addBookInfoInDataBase), 1, fp))
    {
        
        if (!strcmp(addBookInfoInDataBase.bookName, bookName))
        {
            found = 1;
            break;
        }
        if (strcmp(addBookInfoInDataBase.bookName, bookName))
        {
            found = 0;
            break;
        }
        
    }
    if (found)
    {
        printf("\n\t\t\t\033[0;32mBook id = %u\n", addBookInfoInDataBase.books_id);
        printf("\t\t\t\033[0;33mBook name = %s", addBookInfoInDataBase.bookName);
        printf("\t\t\t\033[0;35mBook authorName = %s", addBookInfoInDataBase.authorName);
        printf("\t\t\t\033[0;36mBook issue date(day/month/year) =  (%d/%d/%d)\033[0;37m", addBookInfoInDataBase.bookIssueDate.dd,
               addBookInfoInDataBase.bookIssueDate.mm, addBookInfoInDataBase.bookIssueDate.yyyy);

        printf("\n\t\t\t\033[0;31m""At That Time You Will Get Only One Book Record Try To View Books\033[0;37m");
    }
    else
    {
        printf("\n\t\t\t\033[0;31mNo Record\033[0;37m");
    }
    fclose(fp);
    printf("\n\n\n\t\t\t\033[0;32mPress Enter key to Go main menu.....\033[0;37m");
    getchar();
}
void viewBooks()
{
    int found = 0;
    char bookName[max_book_name] = {0};
    s_BooksInfo addBookInfoInDataBase = {0};
    FILE *fp = NULL;
    int status = 0;
    unsigned int countBook = 1;
    headMessage("\033[0;35m""VIEW BOOKS DETAILS \033[0;37m");
    fp = fopen(pass_file_name, "rb");
    if (fp == NULL)
    {
        printf("\n\t\t\t\033[0;31m""File is not opened\n");
        printf("Please Try With Super User \033[0;37m""");
        exit(1);
    }
    if (fseek(fp, file_header_size, SEEK_SET) != 0)
    {
        fclose(fp);
        printf("\n\t\t\t\033[0;31m""Facing issue while reading file\033[0;37m""\n");
        exit(1);
    }
    fflush(stdin);

    while (fread(&addBookInfoInDataBase, sizeof(addBookInfoInDataBase), 1, fp))
    {
        printf("\n\t\t\t\033[0;31mBook Count = %d\n\n\033[0;37m", countBook);
        printf("\t\t\t\033[0;32mBook id = %u\033[0;37m", addBookInfoInDataBase.books_id);
        printf("\n\t\t\t\033[0;33mBook name = %s\033[0;37m", addBookInfoInDataBase.bookName);
        printf("\t\t\t\033[0;35mBook authorName = %s\033[0;37m", addBookInfoInDataBase.authorName);
        printf("\t\t\t\033[0;36mBook issue date(day/month/year) =  (%d/%d/%d)\n\033[0;37m", addBookInfoInDataBase.bookIssueDate.dd,
               addBookInfoInDataBase.bookIssueDate.mm, addBookInfoInDataBase.bookIssueDate.yyyy);
        found = 1;
        ++countBook;
    }
    fclose(fp);
    if (!found)
    {
        printf("\n\t\t\t\033[0;31mNo Record\033[0;37m");
    }
    printf("\n\n\n\t\t\t\033[0;32mPress Enter key to Go main menu.....\033[0;37m");
    fflush(stdin);
    getc(stdin);
}
void deleteBooks()
{
    int found = 0;
    int bookDelete = 0;
    sFileHeader fileHeaderInfo = {0};
    char bookName[max_book_name] = {0};
    s_BooksInfo addBookInfoInDataBase = {0};
    FILE *fp = NULL;
    FILE *tmpFp = NULL;
    int status = 0;
    headMessage("\033[0;31mDelete Books Details\033[0;37m");
    fp = fopen(pass_file_name, "rb");
    if (fp == NULL)
    {
        printf("\n\t\t\t\033[0;31m""File is not opened\n");
        printf("Please Try With Super User \033[0;37m""");
        exit(1);
    }
    tmpFp = fopen("tmp.bin", "wb");
    if (tmpFp == NULL)
    {
        fclose(fp);
        printf("\n\t\t\t\033[0;31m""File is not opened\n");
        printf("Please Try With Super User \033[0;37m""");
        exit(1);
    }
    fread(&fileHeaderInfo, file_header_size, 1, fp);
    fwrite(&fileHeaderInfo, file_header_size, 1, tmpFp);
    printf("\n\t\t\t\033[0;31mEnter Book ID NO. for delete:");
    scanf("%d\033[0;37m", &bookDelete);
    while (fread(&addBookInfoInDataBase, sizeof(addBookInfoInDataBase), 1, fp))
    {
        if (addBookInfoInDataBase.books_id != bookDelete)
        {
            fwrite(&addBookInfoInDataBase, sizeof(addBookInfoInDataBase), 1, tmpFp);
        }
        else
        {
            found = 1;
        }
    }
    (found) ? printf("\n\t\t\t\033[0;32mRecord deleted successfully.....\033[0;37m") : printf("\n\t\t\t\033[0;31mRecord not found\033[0;37m");
    fclose(fp);
    fclose(tmpFp);
    remove(pass_file_name);
    rename("tmp.bin", pass_file_name);
}
int updateCredential(void)
{
    sFileHeader fileHeaderInfo = {0};
    FILE *fp = NULL;
    unsigned char userName[max_size_user_name] = {0};
    unsigned char password[max_size_psw] = {0};
    headMessage("Update Credential");
    fp = fopen(pass_file_name, "rb+");
    if (fp == NULL)
    {
        printf("\n\t\t\t\033[0;31m""File is not opened\n");
        printf("Please Try With Super User \033[0;37m""");
        exit(1);
    }
    fread(&fileHeaderInfo, file_header_size, 1, fp);
    if (fseek(fp, 0, SEEK_SET) != 0)
    {
        fclose(fp);
        printf("\n\t\t\t\033[0;31mFacing issue while updating password\033[0;37m\n");
        exit(1);
    }
    printf("\n\n\t\t\t\033[1;36m New Username:");

    fgets(userName, max_size_user_name, stdin);
    fflush(stdin);
    fgets(userName, max_size_user_name, stdin);
    fflush(stdin);
    printf("\033[0;37m");
    printf("\n\n\t\t\t \033[1;36m New Password:");
    fflush(stdin);
    fgets(password, max_size_psw, stdin);
    printf("\033[0;37m");
    strncpy(fileHeaderInfo.username, userName, sizeof(userName));
    strncpy(fileHeaderInfo.password, password, sizeof(password));
    fwrite(&fileHeaderInfo, file_header_size, 1, fp);
    fclose(fp);
    printf("\n\t\t\t \033[0;32m Your Password has been changed successfully \033[0;37m");
    printf("\n\t\t\t\t \033[1;31m Login Again: \033[0;37m"); 
    fflush(stdin);
    return 0;
    exit(1);
}
void menu()
{
    int choice = 0;
    do
    {
        headMessage("""\033[1;36m""MAIN MENU");
        printf("\n\n\n\t\t\t""\033[1;32m""1.Add Books");
        printf("\n\t\t\t""\033[1;33m""2.Search Books");
        printf("\n\t\t\t""\033[1;35m""3.View Books");
        printf("\n\t\t\t""\033[1;36m""4.Delete Book");
        printf("\n\t\t\t""\033[1;32m""5.Update Password");
        printf("\n\t\t\t""\033[1;35m""0.Exit");
        printf("\n\n\n\t\t\t""\033[1;36m""Enter choice => ");
        scanf("%d\033[0;37m", &choice);
        switch (choice)
        {
        case 1:
            addBookInDataBase();
            break;
        case 2:
            searchBooks();
            break;
        case 3:
            viewBooks();
            break;
        case 4:
            deleteBooks();
            break;
        case 5:
            updateCredential();
            break;
        case 0:
            printf("\n\n\n\t\t\t\tThank you, Please Visit Again!!!\n\n\n\n\n");
            exit(1);
            break;
        default:
            printf("\n\n\n\t\t\tINVALID INPUT!!! Try again...");
        }                  
    } while (choice != 0); 
}
int login()
{
    unsigned char userName[max_size_user_name] = {0};
    unsigned char password[max_size_psw] = {0};
    int L = 0;
    sFileHeader fileHeaderInfo = {0};
    FILE *fp = NULL;
    headMessage("\033[0;32m\t   Login\033[0;37m ");
    fp = fopen(pass_file_name, "rb");
    if (fp == NULL)
    {
        printf("\033[0;31mFile is not opened\n");
        printf("Please Try With Super User\033[0;37m");
        exit(1);
    }
    fread(&fileHeaderInfo, file_header_size, 1, fp);
    fclose(fp);
    do
    {
        printf("\n\n\n\t\t\t\t\033[0;36mUsername:");
        fgets(userName, max_size_user_name, stdin);
        printf("\n\t\t\t\tPassword:");
        fgets(password, max_size_psw, stdin);
        printf("\033[0;37m");
        if ((!strcmp(userName, fileHeaderInfo.username)) && (!strcmp(password, fileHeaderInfo.password)))
        {
            menu();
        }
        else
        {
            printf("\t\t\t\t	\033[31m Login Failed Enter Again Username & Password \033[0;37m\n\n");
            L++;
        }
    } while (L <= 3);
    if (L > 3)
    {
        headMessage("\033[31m Login Failed \033[0;37m");
        printf("\033[31m \t\t\t\tSorry,Unknown User. \033[0;37m");
        return 0;
    }
}
int isFileExists(const char *path)
{
    FILE *fp = fopen(path, "rb");
    int status = 0;
    if (fp != NULL)
    {
        status = 1;
        fclose(fp);
    }
    return status;
}
void init()
{
    FILE *fp = NULL;
    int status = 0;
    const char defaultUsername[] = "G26\n";
    const char defaultPassword[] = "G26\n";
    sFileHeader fileHeaderInfo = {0};
    status = isFileExists(pass_file_name);
    if (!status)
    {
        fp = fopen(pass_file_name, "wb");
        if (fp != NULL)
        {
            strncpy(fileHeaderInfo.password, defaultPassword, sizeof(defaultPassword));
            strncpy(fileHeaderInfo.username, defaultUsername, sizeof(defaultUsername));
            fwrite(&fileHeaderInfo, file_header_size, 1, fp);
            fclose(fp);
        }
    }
}
int main()
{
    init();
    welcomeMessage();
    login();
    return 0;
}

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <conio.h>
#include <iomanip>

using namespace std;
int main()
{
    FILE *fp, *ft;
    char another, choice;

    struct employee
    {
        char first_name[50], last_name[50];
        int Age;
        long Salary;
    };

    struct employee e;
    char xfirst_name[50], xlast_name[50];
    long int recsize;

    fp=fopen("users.txt","rb+");

    if (fp == NULL)
    {
        fp = fopen("users.txt","wb+");

        if (fp==NULL)
        {
            puts("Cannot open file");
            return 0;
        }
    }



    recsize = sizeof(e);

    while(1)
    {
        system("cls");

        cout << "\t\t  ####### Simple Employee System(CRUD) #######";
        cout <<"\n\n                                          ";
        cout << "\n\n";
        cout << "\n \t\t\t 1. CREATE EMPLOYEE";
        cout << "\n \t\t\t 2. READ RECORD";
        cout << "\n \t\t\t 3. UPDATE RECORD";
        cout << "\n \t\t\t 4. DELETE RECORD";
        cout << "\n \t\t\t 5. Exit";
        cout << "\n\n";
        cout << "\t\t\t Select Your Choice : ";
        fflush(stdin);
        choice = getche();
        switch(choice)
        {
        case '1' :
            fseek(fp,0,SEEK_END);
            another ='Y';
            while(another == 'Y' || another == 'y')
            {
                system("cls");
                cout << "Enter the Firt Name : ";
                cin >> e.first_name;
                cout << "Enter the Last Name : ";
                cin >> e.last_name;
                cout << "Enter the Age     : ";
                cin >> e.Age;
                cout << "Enter the Salary   : ";
                cin >> e.Salary;
                fwrite(&e,recsize,1,fp);
                cout << "\n Add Another Record (Y/N) ";
                fflush(stdin);
                another = getchar();
            }
            break;
        case '2':
            system("cls");
            rewind(fp);
            cout << "=== View the list in the Database ===";
            cout << "\n";
            while (fread(&e,recsize,1,fp) == 1)
            {
                cout << "\n";
                cout <<"\n" << e.first_name << setw(10)  << e.last_name;
                cout << "\n";
                cout <<"\n" <<e.Age <<  setw(8)  << e.Salary;
            }
            cout << "\n\n";
            system("pause");
            break;

        case '3' :
            system("cls");
            another = 'Y';
            while (another == 'Y'|| another == 'y')
            {
                cout << "\n Enter the last name of the Employee : ";
                cin >> xlast_name;

                rewind(fp);
                while (fread(&e,recsize,1,fp) == 1)
                {
                    if (strcmp(e.last_name,xlast_name) == 0)
                    {
                        cout << "Enter new the Firt Name : ";
                        cin >> e.first_name;
                        cout << "Enter new the Last Name : ";
                        cin >> e.last_name;
                        cout << "Enter new Age     : ";
                        cin >> e.Age;
                        cout << "Enter new Salary   : ";
                        cin >> e.Salary;
                        fseek(fp, - recsize, SEEK_CUR);
                        fwrite(&e,recsize,1,fp);
                        break;
                    }
                    else
                        cout<<"record not found";
                }
                cout << "\n Modify Another Record (Y/N) ";
                fflush(stdin);
                another = getchar();
            }
            break;


        case '4':
            system("cls");
            another = 'Y';
            while (another == 'Y'|| another == 'y')
            {
                cout << "\n Enter the last name of the Employee to delete : ";
                cin >> xlast_name;

                ft = fopen("temp.dat", "wb");

                rewind(fp);
                while (fread (&e, recsize,1,fp) == 1)

                    if (strcmp(e.last_name,xlast_name) != 0)
                    {
                        fwrite(&e,recsize,1,ft);
                    }
                fclose(fp);
                fclose(ft);
                remove("users.txt");
                rename("temp.dat","users.txt");

                fp=fopen("users.txt","rb+");

                cout << "\n Delete Another Record (Y/N) ";
                fflush(stdin);
                another = getchar();
            }

            break;

        case '5':
            fclose(fp);
            cout << "\n\n";
            cout << "\t\t     THANK YOU!";
            cout << "\n\n";
            exit(0);
        }
    }


    system("pause");
    return 0;
}

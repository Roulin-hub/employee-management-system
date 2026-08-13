#include <stdio.h>

struct Employee
{
    int id;
    char name[20];
    float salary;
};

void create()
{
    FILE *fp;
    struct Employee e;

    fp = fopen("data/employee.dat", "ab");

    printf("Enter ID: ");
    scanf("%d", &e.id);

    printf("Enter Name: ");
    scanf("%s", e.name);

    printf("Enter Salary: ");
    scanf("%f", &e.salary);

    fwrite(&e, sizeof(e), 1, fp);

    fclose(fp);

    printf("Employee added.\n");
}

void read()
{
    FILE *fp;
    struct Employee e;

    fp = fopen("data/employee.dat", "rb");

    if (fp == NULL)
    {
        printf("No file found.\n");
        return;
    }

    while (fread(&e, sizeof(e), 1, fp))
    {
        printf("%d %s %.2f\n",
               e.id, e.name, e.salary);
    }

    fclose(fp);
}

void update()
{
    FILE *fp;
    struct Employee e;
    int id;

    fp = fopen("data/employee.dat", "rb+");

    if (fp == NULL)
    {
        printf("No file found.\n");
        return;
    }

    printf("Enter ID: ");
    scanf("%d", &id);

    while (fread(&e, sizeof(e), 1, fp))
    {
        if (e.id == id)
        {
            printf("Enter New Name: ");
            scanf("%s", e.name);

            printf("Enter New Salary: ");
            scanf("%f", &e.salary);

            fseek(fp, -sizeof(e), SEEK_CUR);
            fwrite(&e, sizeof(e), 1, fp);

            printf("Updated.\n");

            fclose(fp);
            return;
        }
    }

    printf("Employee not found.\n");
    fclose(fp);
}

void delete()
{
    FILE *fp, *temp;
    struct Employee e;
    int id;

    fp = fopen("data/employee.dat", "rb");
    temp = fopen("data/temp.dat", "wb");

    if (fp == NULL)
    {
        printf("No file found.\n");
        return;
    }

    printf("Enter ID: ");
    scanf("%d", &id);

    while (fread(&e, sizeof(e), 1, fp))
    {
        if (e.id != id)
            fwrite(&e, sizeof(e), 1, temp);
    }

    fclose(fp);
    fclose(temp);

    remove("data/employee.dat");
    rename("data/temp.dat", "data/employee.dat");

    printf("Deleted.\n");
}

int main()
{
    int choice;

    while (1)
    {
        printf("\n1. Create");
        printf("\n2. Read");
        printf("\n3. Update");
        printf("\n4. Delete");
        printf("\n5. Exit");
        printf("\nEnter choice: ");
        scanf("%d", &choice);

        if (choice == 1)
            create();
        else if (choice == 2)
            read();
        else if (choice == 3)
            update();
        else if (choice == 4)
            delete();
        else if (choice == 5)
            break;
        else
            printf("Invalid choice.\n");
    }

    return 0;
}

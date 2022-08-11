#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

typedef struct Account
{
    int accno;
    int pin;
    char name[20];
    int credit;
    int debit;
    int balance;
} Acc;

void create()
{
    Acc *A;
    int temp_num;
    A = (Acc *)calloc(1, sizeof(Acc));
    FILE *fp;
    fp = fopen("Banking Accounts.txt", "a");
    printf("Enter your name \n");
    scanf("%s", &A[0].name);
    srand(time(NULL));

    temp_num = rand();
    printf("Your Account Number is : %d \n", temp_num);
    A[0].accno = temp_num;
    printf("Enter the Pin u want \n");
    scanf("%d", &A[0].pin);
    printf("Enter the amount you want to deposit \n");
    scanf("%d", &A[0].credit);
    A[0].debit = 0;
    A[0].balance = A[0].credit - A[0].debit;
    fwrite(&A[0], sizeof(Acc), 1, fp);
    fclose(fp);
}

void display()
{
    Acc A;
    FILE *fp;
    fp = fopen("Banking Accounts.txt", "r");
    char name_t[20];
    int temp_check;
    getchar();
    printf("Enter your name : ");
    scanf("%s", &name_t);
    printf("Showing Results for %s\n", name_t);

    while (fread(&A, sizeof(Acc), 1, fp))
    {

        if (*A.name == *name_t)
        {
            temp_check = 1;
            printf("Name : %s \nAccount No. : %d \n", A.name, A.accno);
            printf("\n\n");
        }
        else
        {
            continue;
        }
    }
    if (temp_check != 1)
    {
        printf("No Result Found!!!\n\n");
    }
}

void deposit()
{
    FILE *fp, *fp1, *fp2;
    Acc A;

    fp = fopen("Banking Accounts.txt", "r");

    fp1 = fopen("Temp.txt", "w");

    fp2 = fopen("Banking Transactions.txt", "a");

    int acc, money, piin, check = 0;

    printf("\033[3;37mEnter the Account Number\033[0m\n");

    scanf("%d", &acc);

    int i = 0, m = 0;
    printf("\033[2;35mchecking");

    for (m; m < 5; m++)
    {
        sleep(1);
        printf(".");
    }
    printf("\033[0m");
    printf("\n");

    while (fread(&A, sizeof(Acc), 1, fp))
    {
        if (A.accno == acc)
        {
            check = 1;
            printf("\033[3;37m");
            printf("Enter the Amount you wamt to deposit \n");
            printf("\033[0m");
            scanf("%d", &money);
            printf("\033[3;37mEnter the Pin \n");
            printf("\033[0m");
            scanf("%d", &piin);
            printf("\033[0m");
            if (A.pin == piin)
            {
                printf("\033[2;35mDepositing");

                for (m; m < 5; m++)
                {
                    sleep(1);
                    printf(".");
                }

                printf("\033[0m\n");
                A.credit = money;
                A.debit = 0;
                A.balance = A.balance + money;
                printf("\033[1;36mMoney Depositted Successfully\n");
                printf("Updated Balance is : Rs. %d \n", A.balance);
                i = 1;
                printf("\033[0m");
                fwrite(&A, sizeof(Acc), 1, fp2);
                fwrite(&A, sizeof(Acc), 1, fp1);
            }
            else
            {
                printf("\033[4;31m");
                printf("Entered Wrong Pin\n");
                printf("\033[0m");
            }
        }
        else
        {
            fwrite(&A, sizeof(Acc), 1, fp2);
            fwrite(&A, sizeof(Acc), 1, fp1);
            continue;
        }
    }
    if (check != 1)
    {
        printf("Account Doesnt exsist\nPlease check the entered Account Number.\n\n");
    }

    fclose(fp);
    fclose(fp1);
    fclose(fp2);
    if (i == 1)
    {
        fp = fopen("Banking Accounts.txt", "w");
        fp1 = fopen("Temp.txt", "r");
        while (fread(&A, sizeof(Acc), 1, fp1))
        {
            fwrite(&A, sizeof(Acc), 1, fp);
        }
        fclose(fp);
        fclose(fp1);
    }
}

void withdraw()
{
    FILE *fp, *fp1, *fp2;
    Acc A;

    fp = fopen("Banking Accounts.txt", "r");

    fp1 = fopen("Temp.txt", "w");

    fp2 = fopen("Banking Transactions.txt", "a");

    int acc, money, piin, check = 0;

    printf("\033[3;37mEnter the Account Number\033[0m\n");

    scanf("%d", &acc);

    int i = 0, m = 0;
    printf("\033[2;35mchecking");

    for (m; m < 5; m++)
    {
        sleep(1);
        printf(".");
    }
    printf("\033[0m");
    printf("\n");

    while (fread(&A, sizeof(Acc), 1, fp))
    {
        if (A.accno == acc)
        {
            check = 1;
            printf("\033[3;37m");
            printf("Enter the Amount you want to withdraw\n");
            printf("\033[0m");
            scanf("%d", &money);
            printf("\033[3;37mEnter the Pin \n");
            printf("\033[0m");
            scanf("%d", &piin);

            if (A.pin == piin)
            {

                printf("\033[0m\n");

                if (A.balance - money >= 0)
                {
                    printf("\033[2;35mWithdrawing..");
                    for (m; m < 5; m++)
                    {
                        sleep(1);
                        printf(".");
                    }
                    printf("\n");

                    A.credit = 0;

                    A.debit = money;

                    A.balance = A.balance - money;

                    printf("\033[1;36mMoney Withdrawn Successfully\n");
                    printf("Updated Balance is : Rs. %d \n", A.balance);

                    i = 1;

                    printf("\033[0m");

                    fwrite(&A, sizeof(Acc), 1, fp2);
                    fwrite(&A, sizeof(Acc), 1, fp1);
                }
                else
                {
                    printf("Insufficient Funds\n");
                    printf("You withdraw limit is %d\n\n", A.balance);
                }
            }
            else
            {
                printf("\033[4;31m");
                printf("Entered Wrong Pin\n");
                printf("\033[0m");
            }
        }
        else
        {
            fwrite(&A, sizeof(Acc), 1, fp2);
            fwrite(&A, sizeof(Acc), 1, fp1);
            continue;
        }
    }
    if (check != 1)
    {
        printf("Account Doesnt exsist\nPlease check the entered Account Number.\n\n");
    }

    fclose(fp);
    fclose(fp1);
    fclose(fp2);
    if (i == 1)
    {
        fp = fopen("Banking Accounts.txt", "w");
        fp1 = fopen("Temp.txt", "r");
        while (fread(&A, sizeof(Acc), 1, fp1))
        {
            fwrite(&A, sizeof(Acc), 1, fp);
        }
        fclose(fp);
        fclose(fp1);
    }
}

void lasttransac()
{
    FILE *fp2;
    Acc A;

    fp2 = fopen("Banking Transactions.txt", "r");

    int acc, piin;

    printf("\033[3;37mEnter the Account Number\033[0m\n");

    scanf("%d", &acc);

    printf("\033[3;37mEnter the Pin \n");
    printf("\033[0m");
    scanf("%d", &piin);
    printf("\033[0m");

    int i = 1, m = 0, n = 1;

    while (fread(&A, sizeof(Acc), 1, fp2))
    {
        if (A.accno == acc)
        {
            m++;
        }
    }

    if (m < 10)
    {
        m = 0;
    }
    else
    {
        m = m - 10;
    }

    fclose(fp2);

    fp2 = fopen("Banking Transactions.txt", "r");
    printf("\033[2;35mShowing Last Transactions ");
    for (int i = 0; i < 4; i++)
    {
        sleep(1);
        printf(".");
    }
    printf("\n\n");

    printf("\033[0m");
    while (fread(&A, sizeof(Acc), 1, fp2))
    {
        if (A.accno == acc && A.pin == piin)
        {

            if (n > m)
            {
                printf("%d .  %d   Cr %d Rs.   Db %d Rs.  Bl. %d Rs. \n", i, A.accno, A.credit, A.debit, A.balance);
                i++,
                    n++;
            }

            else
            {
                printf("Something Went Wrong.\nCheck the Enter Details make sure that it is correct.");
            }
        }
        else
        {
            continue;
        }
    }
    fclose(fp2);
    printf("\n \n");
}

int main(int argc, char *argv[])
{
    printf("\033[4;37m");
    printf("\t\tBanking System\n\n\n");
    printf("\033[0m");
    int i;

    do
    {
        printf("\033[1;32m");
        printf("1. Create Account\n");
        printf("2. Check Details\n");
        printf("3. Deposit Money\n");
        printf("4. Withdraw Money\n");
        printf("5. Show last 10 Transactions\n");
        printf("0. To Exit\n");
        printf("Enter the number what u wanna do\n\n");
        printf("\033[0m");
        scanf("%d", &i);
        switch (i)
        {
        case 1:
            create();
            break;

        case 2:
            display();
            break;

        case 3:
            deposit();
            break;

        case 4:
            withdraw();
            break;

        case 5:
            lasttransac();
            break;
        }
    } while (i != 0);


    printf("Thank you for banking with us!!!!");
}
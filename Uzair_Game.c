#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include<windows.h>

//Introduction to Game

void intro()
{
    char start;
    printf("\n\tWelcome to the Game ");
    printf("\n\n\t\tTASK");
    printf("\n\tARRANGE THE MATRIX IN INCREMENT ORDER");
    printf("\n\n\tFollowing are the rules of the Game :");
    printf("\n\n\t1.You have 3 chances to win the Game");
    printf("\n\t2.You can use following keys");
    printf("\n\t\tUP key : To move the number up");
    printf("\n\t\tDOWN key : To move the number down");
    printf("\n\t\tRIGHT key : To move the number right");
    printf("\n\t\tLEFT key : To move the number left");
    printf("\n\t3.You can move number only to the empty space");
    printf("\n\t4.You have limited number of moves");
    printf("\n\t5.To Exit any time press 'E' or 'e'");
    printf("\n\n\tTry to win the game in minimum number of moves");
    printf("\n\tGood Luck\n");
    printf("\n\tPress Enter Key to continue : ");
    start = getch();
    while(start != 13 && start != 'e' && start == 'E')
        start=getch();

    if(start == 'E' || start == 'e')
        exit(0);
      
}

//To Check Solvability, wethere arrangement is solvable or not!
int Solvability_Check(int a[])
{
    int i,j,sum=0;
    for(i=0;i<14;i++)
    {
        for(j=i+1;j<15;j++)
        {
            if(a[j]<a[i])
                sum++;
        }
    }
    if(sum%2==0)
        return 1;
    else
        return 0;
}

//To Generate solvable numbers
void GenerateNumbers(int a[])
{
    int i,j,num;
   srand(time(0));

    do
    {
        for(i=0;i<15;i++)
        {
            num=rand()%15+1;
            for(j=0;j<i;j++)
                if(num==a[j])
                    break;
            if(j==i)
            a[i]=num;
            else
            i--;
        }
        a[15]=16;
    }
   while (!Solvability_Check(a));
  
}

//To print the matrix and changes
void Print(int a[], char name[],int n, int N)
{
    int i;
    system("cls");
    system("COLOR 02");
    printf("\n\tPlayer -> %s\tMoves left = %d\tChance No. = %d\n\n",name,n,N);
    system("COLOR 03");
    printf("\t\t\t-------------------------");
    for(int i=0;i<16;i++)
    {
        if(i%4==0)
        printf("\n\t\t\t|     |     |     |     |\n\t\t\t|");
        if(a[i]==16)
            printf("     |");
        else
            printf("%4d |",a[i]);
    }
    printf("\n\t\t\t-------------------------\n\t\t\t");
}

//To move the numbers in an Array
int MoveNumber(int a[],char ch, int index)
{
    switch(ch)
    {
        case 72:
            a[index]=a[index+4];
            a[index+4]=16;
            index=index+4;
            break;

        case 80:
            a[index]=a[index-4];
            a[index-4]=16;
            index=index-4;
            break;
        
        case 77:
            a[index]=a[index-1];
            a[index-1]=16;
            index=index-1;
            break;
        
        case 75:
            a[index]=a[index+1];
            a[index+1]=16;
            index=index+1;
            break;
    }
    return index;
}

//To check weather move is valid or not
int Check_move(int p, int ch)
{
    if(p>11 && ch==72)
    return 0;
    else if(p<4 && ch==80)
    return 0;
    else if(p%4==0 && ch==77)
    return 0;
    else if(p%4==3 && ch==75)
    return 0;
    else
    return 1;
}

//To check if matrix is solved or not 
int Check_Win(int a[])
{
    int i;
    for(i=0;i<16;i++)
    {
        if(a[i]!=i+1)
        break;
    }
    if(i==16)
        return 1;
    else 
        return 0;
}

//If matrix is not solved 
void Print_Loose()
{
    int key;
    system("COLOR 04");
    printf("\n\n\n\n\n\t\t\t\t Your movers are over !!!");
    printf("\n\n\t\t\t\tPress Enter key : ");
    key=getch();
    while (key!=13)
    {
        key=getch();
    }
    
}

//Main function starts here//

int main()
{
    char name[15];
    system("COLOR 02");
    printf("\n\n\t\tHello \n\n\t\tEnter your name : ");
    fgets(name,15,stdin);

    system("cls");
    system("COLOR 06");

    int a[16],i,move,position,n,N=3,Exit;

    intro();


    while (N>0)
    {
        system("COLOR 01");
        n=140;
        GenerateNumbers(a);
        for(i=0;i<16;i++)
            if(a[i]==16)
                position=i;

        Print(a,name,n,N);
        while (n>0)
        {  
            Exit=getch();
            if(Exit=='E' || Exit=='e')
                    exit(0);
            move=getch();
            while(move!=72 && move!=75 && move!=77 && move!=80)
                move=getch();
            n--;
            if(Check_move(position,move))
            {
                position=MoveNumber(a,move,position);
                Print(a,name,n,N);
                if(Check_Win(a))
                {
                    system("COLOR 02");
                    printf("\n\n\t\tCongratulations you have solved the Matrix");
                    printf("\n\n\t\tThanks for playing my Game sir, See you Soon %c",2);
                    getch();
                    exit(0);
                }
            }
            else
                n++;

            if(n==0)
                Print_Loose();
        }
        N--;
    }
    system("COLOR 04");
    printf("\n\n\tYou could not solve the Game in 5 chances\n\n\tBetter Luck Next Time");

    return 0;

}

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//admin mode - set number of voters and the voting options. Allow access with a password you can generate
//voting mode - allow users to vote, then clear the terminal, store info

typedef struct Voter
{
    char name[100];
    int vote;
}voter;

typedef struct Candidate
{
    char name[100];
    int number;
}candidate;

char password[20];
char ll[100][1000];
int num_voters,num_candidates;
int admin_f=0,voter_f=0;
candidate *candidates;
voter *voters;

void AdminMode()
{
    int fail=0;
    char ch;
    system("cls");
    if(admin_f)
    {
        char ps1[20];
        printf("\nEntering admin mode...\nEnter password:");
        scanf("%s",ps1);
        if(strcmp(ps1,password))
        {
            printf("incorrect password! try again\n");
            fflush(stdin);
            printf("Press any key to continue ");
            scanf("%c");
            fail=1;
        }
    }
    else
    {
        printf("\nEntering admin mode...\nEnter password:");
        scanf("%s",password);
    }
    if(fail==0)
    {
        printf("\nEnter number of voters: ");
        scanf("%d",&num_voters);
        printf("Enter number of candidates: ");
        scanf("%d",&num_candidates);

        voters=(voter*)malloc(num_voters*sizeof(voter));
        candidates=(candidate*)malloc(num_candidates*sizeof(candidate));

        printf("\nEnter voting candidates:\n");
        for(int i=1;i<=num_candidates;i++)
        {
            printf("%d. ",i);
            fflush(stdin);
            scanf("%[^\n]s",candidates[i-1].name);
            candidates[i-1].number=0;
            printf("\n");
        }
        printf("The details are:\n");
        printf("The number of voters are: %d \n",num_voters);
        printf("Candidates are: \n");
        for(int i=1;i<=num_candidates;i++)
        {
            printf("%d. %s\n",i,candidates[i-1].name);
        }
        printf("Press any key to continue");
        fflush(stdin);
        scanf("%c",&ch);
        admin_f=1;
    }
    system("cls");
}

void VotingMode()
{
    char ch;
    system("cls");
    printf("\n");
    for(int no=0;no<num_voters;no++)
    {
        system("cls");
        printf("\nEnter your name: ",voters[no].name);
        scanf("%s",voters[no].name);
        printf("Enter your vote out of the following candidates:\n");
        for(int i=0;i<num_candidates;i++)
        {
            printf("%d. %s\n",i+1,candidates[i].name);
        }
        printf("Your vote here: ");
        scanf("%d",&voters[no].vote);
        printf("Press Y to confirm vote, or n to redo vote: ");
        fflush(stdin);
        scanf("%c",&ch);
        if(ch=='n')
        {
            no--;
            continue;
        }
        else 
        {
            candidates[voters[no].vote-1].number++;
            int ii=0;
            while(ll[ii][]!="\0"){
                ii++;
            }
            for(int ij=0;ij<strlen(voters[no].name);ij++)
            {
                ll[ii][ij]=voters[no].name[ij];
            }
            for(int ij=0;ij<strlen(voters[no].name);ij++)
            {
                ll[ii+1][ij]=candidates[voters[no].vote-1].name[ij];
            }
            
        }
    }
    voter_f=1;
    system("cls");
}

void DisplayResults()
{
    system("cls");
    for(int i=0;i<num_candidates;i++)
    {
        printf("\n%d. %s - %d votes",i+1,candidates[i].name,candidates[i].number);
    }
    printf("\n");
    fflush(stdin);
    printf("Press any key to continue ");
    scanf("%c");
    system("cls");
}

void DV()
{
    int jj=0;
    while(ll[jj]!="\0")
    {
        printf("%s",ll[jj]);
        if(jj%2==1) printf("\n");
    }
}
void main()
{
    system("cls");
    while(1)
    {
        int choice;
        printf("\n1.Admin mode\n2.Voting mode\n3.Results display\n4.Detailed View\n5.Exit\n");
        printf("Enter your choice: ");
        scanf("%d",&choice);
        if(choice==5) break;
        switch(choice)
        {
            case 1:
            AdminMode();
            break;
            case 2:
            if(admin_f) VotingMode();
            else 
            {
                printf("Admin not initialized!");
                fflush(stdin);
                printf("Press any key to continue ");
                scanf("%c");
            }
            break;
            case 3:
            if(admin_f && voter_f) DisplayResults();
            else 
            {
                printf("Admin or voting not done!");
                fflush(stdin);
                printf("Press any key to continue ");
                scanf("%c");
            }
            break;
            case 4:
            if(admin_f && voter_f) DV();
            else 
            {
                printf("Admin or voting not done!");
                fflush(stdin);
                printf("Press any key to continue ");
                scanf("%c");
            }
            break;
            default:
            printf("error! %d",choice);
        }
    }
}

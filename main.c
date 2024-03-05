#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<math.h>

typedef struct
{
    int month;
    int year;

} publication_date;


typedef struct
{

    char ISBN[14];
    char Title[100];
    char Author_name[100];
    int quantity;
    float price;

    publication_date X;

} book;


typedef struct
{
    char name[100];
    char pass[50];

} user_info;


int isValid(char month[3])
{
    int i;
    for(i=0; i<3; i++)
    {
        if((month[i]>='a'&&month[i]<='z') || (month[i]>='A'&& month[i]<='Z'))
        {
            printf("INAVLID ENTRY!! Enter The Month as a number\n");
            return 0;
        }



    }
    return 1;
}


int initialmenue()
{
    char loq[1];
    int z;
    printf("For Logging in  please enter L and for quitting the program please enter Q :");
    gets(loq);
    for (;;)
    {

        if (loq[0] == 'l' || loq[0] == 'L')
        {
            z=login();



            return z;
        }
        else if (loq[0] == 'q' || loq[0] == 'Q')
        {
            printf("\t\t\t\t\t\t\t\t\t\tTHANK YOU FOR USING OUR PROGRAM \n");
            return 0;

        }
        else
        {
            printf("\n\aPLEASE ENTER THE RIGHT LETTER FOR YOUR SERVICE :");
            gets(loq);



        }
    }
}



int login()
{
    char name_user[100];
    char password[50];
    user_info user[100];


    FILE *fuser;
    printf("\nPlease Enter Your Username:");

    scanf("%s",name_user);

    printf("\nPlease Enter Your Password:");
    scanf("%s",password);

    fuser = fopen("credentials.txt","r");

    if(fuser == NULL)
    {
        printf("FILE DOES NOT EXIT!!!");
        exit(1);
    }
    char string[100];
    int i=0,l=0;
    char *start;
    char names[100];
    int flag=0;
    while(!feof(fuser))
    {
        fgets(string,100,fuser);
        sscanf(string,"%s",user[i].name);
        fgets(string,100,fuser);
        sscanf(string,"%s",user[i].pass);
        i++;
        l++;

    }

    for(i=0; i<l; i++)
    {

        if (strcmp(user[i].name,name_user)==0&& strcmp(password,user[i].pass)==0)
        {
            printf("LOGIN SUCCESSFULL!!\n");
            flag++;
            return 1;


        }

    }

    if(flag==0)
    {
        printf("USER DOESN'T EXIST\n");
        printf("PLEASE LOGIN AGAIN\n");

        return (login());
    }







    fclose(fuser);
}




void SortByTitle (book  x[], int n)
{
    int i,j;

    book hold;
    for( i = 0; i < n-1; i++)
    {
        for(int j = i + 1; j < n; j++)
        {
            if(strcmp(x[i].Title,x[j].Title)==1)
            {
                hold = x[i];
                x[i] = x[j];
                x[j] = hold;
            }
        }
    }

}


void SortByPrice (book x[], int n)
{
    book hold;
    for(int i = 0; i < n - 1; i++)
    {
        for(int j = i + 1; j < n; j++)
        {
            if(x[i].price > x[j].price)
            {
                hold = x[i];
                x[i] = x[j];
                x[j] = hold;
            }
        }
    }
}


void SortByDate (book x[], int n)
{
    int y[n];
    book hold;
    for(int i = 0; i < n - 1; i++)
    {
        y[i] = (x[i].X.year * 100) + x[i].X.month;

        for(int j = i + 1; j < n; j++)
        {
            y[j] = (x[j].X.year * 100) + x[j].X.month;
            if(y[i] < y[j])
            {
                hold = x[j];
                x[j] = x[i];
                x[i] = hold;
            }
        }
    }
}


void print(book x[100],int n)
{
    int done=0;
    int s;
    printf("Do you want to sort based on Title , Price or Date of publication ?\nPlease choose:\n1. Title\n2. Price\n3. Date of publication.\n");
    printf("Enter here:");
    scanf("%d", &s);
    printf("\n");

    while(!done)
    {
        if(s ==1 || s== 2 || s== 3)
        {
            if(s == 1)
            {
                SortByTitle(x,n);
                done=1;
            }

            if(s == 2)
            {
                SortByPrice(x,n);
                done=1;
            }

            if(s == 3)
            {
                SortByDate(x,n);
                done=1;
            }
        }

        else
        {
            printf("Invalid number!!\nPlease enter your number again\nEnter here:");
            scanf("%d", &s);
            printf("\n");

        }


    }

    int i;
    for(i=0; i<n; i++)
    {
        printf("ISBN:%s\n",x[i].ISBN);
        printf("Title:%s\n",x[i].Title);
        printf("Author:%s\n",x[i].Author_name);
        printf("Quantity:%d\n",x[i].quantity);
        printf("Price:%.2f$\n",x[i].price);
        printf("Published:%d-%d\n\n",x[i].X.month,x[i].X.year);


    }
}




int validISBN(char isbn[100])
{

    int i;


    if(strlen(isbn)==13)
    {

        for(i=0; i<13; i++)
        {
            if((isbn[i]>='a'&&isbn[i]<='z') || (isbn[i]>='A'&&isbn[i]<='Z'))
            {

                return 0;
            }



        }
        return 1;

    }
    else return 0;
}



int LOAD(book x[100])
{
    FILE*file2;

    file2=fopen("books.txt","r");

    if(file2==NULL)
    {
        printf("File doesn't exist");
        exit(1);
    }
    int i=0;
    char *token;
    char s[200];


    while(!feof(file2))
    {
        fgets(s,200,file2);
        token=strtok(s,",");
        strcpy(x[i].ISBN,token);

        token=strtok(NULL,",");
        strcpy(x[i].Title,token);
        token=strtok(NULL,",");
        strcpy(x[i].Author_name,token);
        token=strtok(NULL,",");
        sscanf(token,"%d",&x[i].quantity);
        token=strtok(NULL,",");
        sscanf(token,"%f",&x[i].price);
        token=strtok(NULL,"-");
        x[i].X.month=atoi(token);
        token=strtok(NULL," ");
        sscanf(token,"%d",&x[i].X.year);

        i++;
    }





    fclose(file2);

    return i;
}


void Save(book x[100],int *n)
{

    int i;
    FILE *S;
    S=fopen("books.txt","w");
    for(i=0; i<*n; i++)
    {


        fprintf(S,"%s,%s,%s,%d,%.2f,%d-%d",x[i].ISBN,x[i].Title,x[i].Author_name,x[i].quantity,x[i].price,x[i].X.month,x[i].X.year);
        if(!(i==(*n)-1))
            fprintf(S,"\n");

    }

    fclose(S);
}

void add(book x[100],int*N)
{
    int flag=0;
    char array[100];
    char month[3];
    int m;

    printf("\nEnter the ISBN you want to add:");
    getchar();
    gets(x[*N].ISBN);

    while(flag==0)
    {
        strcpy(array,x[*N].ISBN);
        if(validISBN(array)==1)
        {
            flag=1;
            printf("\nEnter The TITLE of the book:");
            gets(x[*N].Title);
            printf("\nEnter Author name:");
            gets(x[*N].Author_name);
            printf("\nThe Quantity of the books=");

            scanf("%d",&x[*N].quantity);
            printf("\nThe Price of the book=");
            scanf("%f",&x[*N].price);
            printf("\nMonth of publication=");
            getchar();
            do
            {

                gets(month);

            }
            while(isValid(month)==0);

            x[*N].X.month=atoi(month);

            printf("\nIn year=");
            scanf("%d",&x[*N].X.year);



            (*N)++;
        }
        else
        {
            printf("INVALID ISBN!!ENTER AGAIN\n");
            gets(x[*N].ISBN);

        }
    }
}


void deletebook(book x[],int* n)
{
    char check[14];
    int flag=0;
    int i,j,hold,hold2=1;
    printf("Enter ISBN of the book you want to delete :\n");

    getchar();
    gets(check);
    while(flag==0)
    {
        if(validISBN(check)==1)
        {
            flag=1;

            while(hold2)
            {


                for(i=0; i<(*n); i++)
                {
                    if(strcmp(x[i].ISBN,check)==0)
                    {
                        printf("Are you sure you want to delete this book?\n");
                        printf("Enter 0 to confirm.\n\nEnter any digit to cancel. \n");
                        scanf("%d",&hold);
                        if(hold==0)
                        {
                            printf("Book deleted successfully!\n");
                            for(j=i; j<(*n); j++)
                            {
                                strcpy(x[j].ISBN,x[j+1].ISBN);
                                strcpy(x[j].Title,x[j+1].Title);
                                strcpy(x[j].Author_name,x[j+1].Author_name);
                                x[j].quantity = x[j+1].quantity;
                                x[j].price = x[j+1].price;
                                x[j].X.month = x[j+1].X.month;
                                x[j].X.year = x[j+1].X.year;
                            }
                            (*n)--;
                            hold2=0;
                            break;
                        }
                        else
                        {
                            printf("Cancellation Complete. \n");
                            hold2=0;
                            break;
                        }

                    }
                }
                if(hold2==1)
                {
                    printf("The ISBN you entered is not found!!\nEnter again\n");
                    printf("Enter here:");

                    gets(check);
                    printf("\n");

                    continue;



                }
            }
        }
        else
        {
            printf("INVALID ISBN!!ENTER AGAIN\n");
            gets(check);
        }
    }
}

void modifybook(int n, book x[])
{
    int i;
    int flag=0;
    char mod[14];
    int hold=1;
    char month[3];
    printf("enter ISBN :");

    getchar();
    gets(mod);

    while(flag==0)
    {
        if(validISBN(mod)==1)
        {
            flag=1;

            while(hold)
            {
                for(i = 0; i < n; i++)
                {
                    if(strcmp(x[i].ISBN, mod)==0)
                    {
                        printf("\n\n\t\t\tENTER THE FOLLOWING DATA\n\n");
                        printf("Enter new title:\n");
                        gets(x[i].Title);
                        printf("Enter author name:\n");
                        getchar();
                        gets(x[i].Author_name);
                        printf("Quantity of the book:\n");
                        scanf("%d",&x[i].quantity);
                        printf("Price of the book:\n");
                        scanf("%f",&x[i].price);
                        printf("The month in which the book was published:\n");
                        getchar();
                        do
                        {

                            gets(month);

                        }
                        while(isValid(month)==0);

                        x[i].X.month=atoi(month);
                        printf("The year :\n");
                        scanf("%d",&x[i].X.year);
                        hold=0;
                        break;

                    }
                }

                if(hold==1)
                {
                    printf("ISBN you entered is not found\nEnter again\n");
                    getchar();
                    gets(mod);
                    continue;


                }
            }
        }
        else
        {
            printf("INVALID ISBN!!ENTER AGAIN\n");
            gets(mod);

        }
    }
}



void SEARCH(book x[100],int *N)
{
    char isbn[14],i=0;
    int flag=0;
    int flag2=0;
    printf("Enter the ISBN of the book \n");

   getchar();
   gets(isbn);

    while(flag==0)
    {
        if(validISBN(isbn)==1 )
        {
            flag=1;

            printf("\n\n");
            for(i=0; i<*N  ; i++)
            {
                if(strcmp(isbn,x[i].ISBN)==0)
                {
                    printf("ISBN:%s\n",isbn);
                    printf("Title:%s\n",x[i].Title);
                    printf("Author:%s\n",x[i].Author_name);
                    printf("Quantity: %d\n",x[i].quantity);
                    printf("Price:%.2f\n",x[i].price);
                    printf("Published:%d-%d\n",x[i].X.month,x[i].X.year);
                    flag2=1;
                    break;

                }}

                if (flag2==0)
                {
                    printf("the specified ISBN is not found.\n\n");
                    break;
                }

        }
        else
        {

            printf("Invalid ISBN!! Enter again\n");
            gets(isbn);

        }


    }

}


void ADVANCED_SEARCH(book x[100],int N)
{
    char user[100];
    int i=0;
    printf("Please Enter Your Keyword\n");
    scanf("%s",user);
    int found=0;

    for(i=0; i<N; i++)
    {
        if(strstr(x[i].Title,user))
        {
            printf("ISBN:%s\n",x[i].ISBN);
            printf("Title:%s\n",x[i].Title);
            printf("Author:%s\n",x[i].Author_name);
            printf("Quantity: %d\n",x[i].quantity);
            printf("Price:%.2f\n",x[i].price);
            printf("Published:%d %d\n\n\n",x[i].X.month,x[i].X.year);
            found=1;
        }





    }
    if(found==0)
        printf("NO MATCHES FOUND\n");



}





int main()
{
    int n;
    book x[100];
    int func=1;
    int ret;
    printf("\t\t\t\t\t\t\t\t\t\t\aWELCOME TO OUR LIBRARY MANAGMENT SYSTEM \n\n");
    ret=initialmenue();


    if( ret==0)
    {
        exit(1);
    }

    else if (ret==1)
    {
        n=LOAD(x);

    }



    while (func!=0)
    {
        printf("\n\n\t\t\t<<<MENU>>>\n\n");
        printf("\nTo ADD Enter 1\t\t\t\tTo DELETE Enter 2\nTo MODIFY Enter 3\t\t\tTo SEARCH Enter 4\nFor ADVANCED SEARCH Enter 5");
        printf("\t\tTo PRINT Enter 6\nTo SAVE Enter 7\t\t\t\tTo QUIT PROGRAM Enter 0");
        printf("\nENTER HERE :");
        scanf("%d",&func);

        switch(func)
        {
        case 1:
            add(x,&n);
            break;
        case 2:
            deletebook(x,&n);
            break;
        case 3:
            modifybook(n,x);
            break;

        case 4:
            SEARCH(x,&n);
            break;
        case 5:
            ADVANCED_SEARCH(x,n);
            break;
        case 6:
            print(x,n);
            break;
        case 7:
            Save(x,&n);
            break;


        }


        int str;

        if (func==0)
        {
            printf("\a\t\t\t\t\t\t\t\t\t\t\YOU ARE ABOUT TO QUIT AND ALL YOUR CHANGES WILL BE DISCARDED!!\n");
            printf("Please confirm with 1 if you want to Quit and 0 to continue\n");
            scanf("%d",&str);
            if(str==1)
                exit(1);
            else if (str==0)
                func=1;

        }
    }





    return 0;
}

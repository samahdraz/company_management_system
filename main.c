#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
typedef struct
{
    int day;
    int month;
    int year;
} Date;
typedef struct
{
    int id;
    char lastname[50];
    char firstname[50];
    float salary;
    Date birth;
    char adress[30];
    char phonenumber[12];
    char email[20]
} Employee;
int isemail(char email[20])
{
    int i,a=0,b=0;
    for (i=0; i<20; i++)
    {
        if (email[i]=='@')
            a=i;
        else if (email[i]=='.')
            b=i;
    }
    if (a==0 || b==0 || b<a)
        return 0;
    else if (a<b)
        return 1;
}
int isphonenumber(char arr [12])
{
    int i,digit=0;;
    for (i=0; i<12; i++)
    {
        if ( arr[i]>='0' && arr[i]<='9')
            digit++;
    }
    if (digit==11)
        return 1;
    else
        return 0;

}
int isdate(int day,int month,int year)
{
    if (day>=1 && day<=31 && month>=1 && month<=12 &&year>=1970 && year<=2022)
        return 1;
    else
        return 0;
}
int isid(char b[20])
{
    int i, n=strlen(b);
    for (i=0; i<n; i++)
    {
        if (!(b[i]>='0' && b[i]<='9'))
            return 0;
    }
    return 1;
}
int isname(char a [50])
{
    int i, n=strlen(a);
    for (i=0; i<n; i++)
    {
        if (!(a[i]>='A' && a[i]<='Z' || a[i]>='a' && a[i]<='z'))
            return 0;
    }
    return 1;
}
int issalary(float c)
{
    if (c<=0)
        return 0;
    return 1;
}
int n;
Employee e[100];
FILE*fp;
void load (char *name)
{
    int i,j,h,k;
    char str[100][200];
    char time[100][200];
    char id[100][20];
    fp= fopen(name,"r");
    if (fp==NULL)
        printf("File not found");
    n=0;
    while (!feof(fp))
    {
        fgets(str[n],200,fp);
        n++;
    }
    for (i=0; i<n; i++)
    {
        char *p=strtok(str[i],",");
        j=0;
        while(p!=NULL)
        {
            if (j==0)
                strcpy(id[i],p);
            else if (j==1)
                strcpy(e[i].lastname,p);
            else if (j==2)
                strcpy(e[i].firstname,p);
            else if (j==3)
                e[i].salary=atof(p);
            else if (j==4)
                strcpy(time[i],p);
            else if (j==5)
                strcpy(e[i].adress,p);
            else if (j==6)
                strcpy(e[i].phonenumber,p);
            else if (j==7)
                strcpy(e[i].email,p);
            p=strtok(NULL,",");
            j++;
        }
    }
    for (i=0; i<n; i++)
    {
        char *f=strtok(time[i],"-");
        j=0;
        while(f!=NULL)
        {
            if (j==0)
                e[i].birth.day=atoi(f);
            else if (j==1)
                e[i].birth.month=atoi(f);
            else if (j==2)
                e[i].birth.year=atoi(f);
            f=strtok(NULL,"-");
            j++;
        }
    }
    for (i=0; i<n; i++)
    {
        if (isid(id[i]))
            e[i].id=atoi(id[i]);
    }
    fclose(fp);
    h=n;
    n=0;
    k=0;
    for (i=0; i<h; i++)
    {
        if (e[i].id!=0)
        {
            e[i-k]=e[i];
            n++;
        }
        else
            k++;
    }
    // for (i=0; i<n; i++)
    //   printf("%d\n %s\n%s\n%f\n%d\n%d\n%d\n%s\n%s\n%s",e[i].id,e[i].lastname,e[i].firstname,e[i].salary,e[i].birth.day,e[i].birth.month,e[i].birth.year,e[i].adress,e[i].phonenumber,e[i].email);


}
void search ()
{
    int i,flag=0;
    char a [40];
    printf("Enter last name you want to search about: \n");
    getchar();
    gets(a);
    while(!isname(a))
    {
        printf("Enter a valid name:");
        getchar();
        gets(a);
    }
    for (i=0; i < n; i++)
    {
        if(strcasecmp(a,e[i].lastname)==0)
        {
            flag++;
            printf("the employee id:%d\n",e[i].id);
            printf("the employee first name:%s\n",e[i].firstname);
            printf("the employee salary:%f\n",e[i].salary);
            printf("the employee day:%d\n",e[i].birth.day);
            printf("the employee month:%d\n",e[i].birth.month);
            printf("the employee year:%d\n",e[i].birth.year);
            printf("the employee address:%s\n",e[i].adress);
            printf("the employee phone number:%s\n",e[i].phonenumber);
            printf("the employee email:%s\n",e[i].email);

        }
    }
    if (flag==0)
        printf("There are no employees with this last name \n");
}
void addtofile ()
{
    int x;
    printf("How much additions are there? \n ");
    scanf("%d",&x); //number of added employees
    char arr[100][200];
    int i;
    for (i=0; i<x; i++)//for loop to scan the information to be added
    {
        printf("Enter employee ID:\n");
        scanf("%s",arr[i]);
        while(!isid(arr[i]))
        {
            printf("Enter a valid id:\n");
            scanf("%s",arr[i]);
        }
        e[i+n].id=atoi(arr[i]);
        printf("Enter employee last name:\n");
        getchar( );
        gets(e[n+i].lastname);
        while(!isname(e[n+i].lastname))
        {
            printf("Enter a valid name:\n");
            gets(e[n+i].lastname);
        }
        printf("Enter employee first name:\n");
        gets(e[n+i].firstname);
        while(!isname(e[n+i].firstname))
        {
            printf("Enter a valid name:\n");
            gets(e[n+i].firstname);
        }
        printf("Enter employee salary:\n");
        scanf("%f",&e[n+i].salary);
        while(!issalary(e[n+i].salary))
        {
            printf("Enter a valid salary:\n");
            scanf("%f",&e[n+i].salary);
        }
        printf("Enter employee day of birth:\n");
        scanf("%d",&e[n+i].birth.day);
        printf("Enter employee month of birth:\n");
        scanf("%d",&e[n+i].birth.month);
        printf("Enter employee year of birth:\n");
        scanf("%d",&e[n+i].birth.year);
        while(!isdate(e[n+i].birth.day,e[n+i].birth.month,e[n+i].birth.year))
        {
            printf("Enter a valid date\n");
            printf("Enter employee day of birth: \n");
            scanf("%d",&e[n+i].birth.day);
            printf("Enter employee month of birth: \n");
            scanf("%d",&e[n+i].birth.month);
            printf("Enter employee year of birth: \n");
            scanf("%d",&e[n+i].birth.year);
        }
        printf("Enter employee address: \n");
        getchar();
        gets(e[n+i].adress);
        printf("Enter employee phone number: \n");
        gets(e[n+i].phonenumber);
        while(!isphonenumber(e[n+i].phonenumber))
        {
            printf("Enter a valid phone number:\n");
            gets(e[n+i].phonenumber);
        }
        printf("Enter employee E-mail:\n");
        gets(e[n+i].email);
        while(!isemail(e[n+i].email))
        {
            printf("Enter a valid email:\n");
            gets(e[n+i].email);
        }
    }
    n=n+x;//universal array counter addition
    // for (i=0; i<n; i++)
    //printf("%d %s  %s  %f %d %d %d  %s  %s  %s\n",e[i].id,e[i].lastname,e[i].firstname,e[i].salary,e[i].birth.day,e[i].birth.month,e[i].birth.year,e[i].adress,e[i].phonenumber,e[i].email);
}
void modifyfile ()
{
    char c1[20];
    int modid,flag=0,i=0;
    char c[20];
    printf("Enter id required to modify: ");
    scanf("%s",c);//id input for required to modify entry
    while(!isid(c))
    {
        printf("Enter a valid id:");
        scanf("%s",c);
    }
    modid=atoi(c);
    for (i=0; i<n; i++)//for loop for checking which element of the array has this id
    {
        if (e[i].id==modid)
        {
            flag=1;//means that the id was found successfully
            printf("Enter new ID: ");
            scanf("%s",c1);
            while(!isid(c1))
            {
                printf("Enter a valid id:");
                scanf("%s",c1);
            }
            e[i].id=atoi(c1);
            printf("Enter employee last name: ");
            getchar( );
            gets(e[i].lastname);
            while(!isname(e[i].lastname))
            {
                printf("Enter a valid name:");
                gets(e[i].lastname);
            }
            printf("Enter employee first name: ");
            getchar();
            gets(e[i].firstname);
            while(!isname(e[i].firstname))
            {
                printf("Enter a valid name:");
                gets(e[i].firstname);
            }
            printf("Enter employee salary: ");
            scanf("%f",&e[i].salary);
            while(!issalary(e[i].salary))
            {
                printf("Enter a valid salary:");
                scanf("%f",&e[i].salary);
            }
            printf("Enter employee day of birth: ");
            scanf("%d",&e[i].birth.day);
            printf("Enter employee month of birth: ");
            scanf("%d",&e[i].birth.month);
            printf("Enter employee year of birth: ");
            scanf("%d",&e[i].birth.year);
            while(!isdate(e[i].birth.day,e[i].birth.month,e[i].birth.year))
            {
                printf("Enter a valid date\n");
                printf("Enter employee day of birth: ");
                scanf("%d",&e[i].birth.day);
                printf("Enter employee month of birth: ");
                scanf("%d",&e[i].birth.month);
                printf("Enter employee year of birth: ");
                scanf("%d",&e[i].birth.year);
            }
            printf("Enter employee address: ");
            getchar();
            gets(e[i].adress);
            printf("Enter employee phone number: ");
            gets(e[i].phonenumber);
            while(!isphonenumber(e[i].phonenumber))
            {
                printf("Enter a valid phone number:");
                gets(e[i].phonenumber);
            }
            printf("Enter employee E-mail:");
            gets(e[i].email);
            while(!isemail(e[i].email))
            {
                printf("Enter a valid email:");
                gets(e[i].email);

            }
            break;
        }
    }
    if (flag==0)//means that the id was not found in the array
    {
        printf("Id does not exist\n");
        modifyfile();

    }
}
void print ()
{
    int x ;
    printf(" 1 last name\n 2 salary\n 3 date of birth\n");
    scanf("%d",&x);
    if (x==1)
        sortByLname();
    else if (x==2)
        SortBySalary();
    else if (x==3)
        SortByDOB();
}
void SortBySalary ()
{
    int x, i, j;
    Employee b ;
    for (i = 1 ; i < n; i++)
    {
        j = i;
        while ( j > 0 && e[j-1].salary < e[j].salary)
        {
            b    = e[j];
            e[j]  = e[j-1];
            e[j-1] = b;
            j--;
        }
    }
    for (int i=0; i<n; i++)
        printf("ID:%d\nLast name:%s\nFirst name:%s\nSalary:%f\nBirthday:%d-%d-%d\nAddress:%s\nPhone number:%s\nE-mail:%s\n",e[i].id,e[i].lastname,e[i].firstname,e[i].salary,e[i].birth.day,e[i].birth.month,e[i].birth.year,e[i].adress,e[i].phonenumber,e[i].email);
}
void SortByDOB()
{
    int x, i, j;
    Employee b ;
    for (i = 1 ; i < n; i++)
    {
        j = i;
        while ( j > 0 &&  e[j-1].birth.year >= e[j].birth.year )
        {

            b    = e[j];
            e[j]  = e[j-1];
            e[j-1] = b;


            if (e[j].birth.year==e[j-1].birth.year)
            {
                if (e[j-1].birth.month >= e[j].birth.month)
                {
                    b    = e[j];
                    e[j]  = e[j-1];
                    e[j-1] = b;
                }
            }
            if (e[j-1].birth.month == e[j].birth.month)
            {
                if (e[j-1].birth.day >= e[j].birth.day)
                {
                    b    = e[j];
                    e[j]  = e[j-1];
                    e[j-1] = b;
                }

            }

            j--;
        }
    }
    for (int i=0; i<n; i++)
        printf("ID:%d\nLast name:%s\nFirst name:%s\nSalary:%f\nBirthday:%d-%d-%d\nAddress:%s\nPhone number:%s\nE-mail:%s\n",e[i].id,e[i].lastname,e[i].firstname,e[i].salary,e[i].birth.day,e[i].birth.month,e[i].birth.year,e[i].adress,e[i].phonenumber,e[i].email);
}
void sortByLname()
{
    int x,i,j;
    Employee b ;
    for ( j=0; j<n-1; j++)
    {
        for ( i=j+1; i<n; i++)

        {
            if(strcasecmp(e[j].lastname,e[i].lastname)> 0)
            {
                b=e[j];
                e[j]=e[i];
                e[i]=b;
            }
        }
    }

    for (int i=0; i<n; i++)
        printf("ID:%d\nLast name:%s\nFirst name:%s\nSalary:%f\nBirthday:%d-%d-%d\nAddress:%s\nPhone number:%s\nE-mail:%s\n",e[i].id,e[i].lastname,e[i].firstname,e[i].salary,e[i].birth.day,e[i].birth.month,e[i].birth.year,e[i].adress,e[i].phonenumber,e[i].email);
}

void deleteemp ()
{
    char firstname[50],lastname[50];
    int j,z=0;
    printf("Enter employee first name: ");
    getchar( );
    gets(firstname);
    while(!isname(firstname))
    {
        printf("Enter a valid name:");
        gets(firstname);
    }
    printf("Enter employee last name: ");
    getchar( );
    gets(lastname);
    while(!isname(lastname))
    {
        printf("Enter a valid name:");
        gets(lastname);
    }
    for(j=0; j<n; j++)
    {
        if (strcasecmp(e[j].firstname,firstname)==0 && strcasecmp(e[j].lastname,lastname)==0)
        {
            e[j].id=0 ;
            z++ ;
            n--;
        }
    }
    if (z==0)
        printf("Trying to delete an employee that is not in the file\n");

}
void exitprogram(char*name,char x[3])
{
    if (strcasecmp(x,"yes")==0)
        save(name);
    exit(-1);
}
void save (char*name)
{
    int h,k ;
    fp= fopen(name,"w");
    int i ;
    char str[100][10000];
    h=n;
    n=0;
    k=0;
    for (i=0; i<h; i++)
    {
        if (e[i].id!=0)
        {
            e[i-k]=e[i];
            n++;
        }
        else
            k++;
    }
    for (i=0; i<n; i++)
    {
        snprintf(str[i],10000,"%d,%s,%s,%.2f,%d-%d-%d,%s,%s,%s\n",e[i].id,e[i].lastname,e[i].firstname,e[i].salary,e[i].birth.day,e[i].birth.month,e[i].birth.year,e[i].adress,e[i].phonenumber,e[i].email);
        fprintf(fp,"%s\n",str[i]);
    }
    fclose(fp);

}
int main()
{
    char filename[20],a[50],x[3];
    int y,c=0;
    printf("Enter file name:");
    scanf("%s",filename);
    load(filename);
    while (1)
    {
        printf("If you want to add press 1\nIf you want to search press 2\nIf you want to modify press 3\nIf you want to delete press 4\nIf you want to sort press 5\nIf you want to save press 6 \nIf you want to quit press 7\n");
        scanf("%d",&y);

        switch(y)
        {
        case 1 :
            addtofile();
            c++;
            break ;
        case 2 :
            search();
            c++;
            break ;
        case 3 :
            modifyfile();
            c++;
            break ;
        case 4 :
            c++;
            deleteemp();
            break ;
        case 5 :
            print ();
            c++;
            break;
        case 6 :
            save(filename);
            if(c==0)
                printf("nothing changed");
            exitprogram(filename,x);
            break ;
        case 7 :
            if (c>0)
            {
                printf("Changes will not be saved\nDo you want to save the changes?\n");
                scanf("%s",x);
            }
            exitprogram(filename,x);
            break ;
        }
    }
    return 0;
}

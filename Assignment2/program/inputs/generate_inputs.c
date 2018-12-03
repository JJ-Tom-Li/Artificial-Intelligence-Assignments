#include <stdio.h>
#include <stdlib.h>
//#include <ctime>
int main(int argc, char *argv[])
{
    FILE *fp=fopen(argv[1],"w");
    int number = strtol(argv[2], NULL, 10);
    double x[number],y[number],tmpxy;
    srand(time(NULL));


    x[0]=0.0;
    y[0]=0.0;
    int i,tmp;
    /*for(i=1;i<number/2;i++)
    {
        x[i]=x[i-1]+0.5;
        y[i]=0.0;
    }
    x[number/2]=0.0;
    y[number/2]=1;
    for(i=number/2+1;i<number;i++)
    {
        x[i]=x[i-1]+0.5;
        y[i]=1;
    }*/
    for(i=1;i<number;i++)
    {
        x[i]=x[i-1]+0.5+0.5*(rand()%2);
        y[i]=y[i-1]+0.5+0.5*(rand()%2);
    }

    /*shuffle*/
    for(i=0;i<number;i++)
    {
        tmp=rand()%number;
        if(tmp!=i)
        {
            tmpxy=x[i];
            x[i]=x[tmp];
            x[tmp]=tmpxy;
            tmpxy=y[i];
            y[i]=y[tmp];
            y[tmp]=tmpxy;
        }
    }

    for(i=0;i<number;i++)
    {
        printf("(%.2lf,%.2lf)\n",x[i],y[i]);
    }
    for(i=0;i<number;i++)
        fprintf(fp,"%.2lf ",x[i]);
    fprintf(fp,"\n");
    for(i=0;i<number;i++)
        fprintf(fp,"%.2lf ",y[i]);
}
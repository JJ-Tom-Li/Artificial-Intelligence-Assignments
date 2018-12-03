#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ts.h"
/*
    系級:資工四
    學號:4104056004
    姓名:李家駿

    Assignment #2: Travelling Salesman
    4 steps:
        1.Get the city coordinates
        2.Hill Climbing
        3.Imporved Algorithm
        4.Print results
*/

int main(int argc, char *argv[])
{
    
    int i,number_of_cities=-1;
    clock_t t1,t2,t3,t4;    //Declare timers      

    char *filename=argv[1];                     //Get the input file name.
    FILE *fp=fopen(filename,"r");               //open the file
    //FILE *fp_out=fopen("outputs/output.csv","w");       //output to csv file

    /*1.Get the city coordinates*/
    if(!fp)
    {
        //file open error
        printf("Can't open file.Please check if the filename is correct or the file exists.\n");
        return 0;
    }

    double tmp[MAX_NUMBER_OF_CITIES*2];
    while(fscanf(fp,"%lf ",&tmp[++number_of_cities])!=EOF); //read the city coordinates from file and counting the number of cities.

    if(number_of_cities%2!=0) 
    {
        //The number of inputs is not even.
        printf("Number of cities error.\n");
        return 0;
    }
    else
        number_of_cities /=2;//Divide 2 to get the real number of cities.

    City cities[number_of_cities+1];      //declare the cities
    for(i=0;i<number_of_cities;i++)
    {
        cities[i].x=tmp[i];
        cities[i].y=tmp[number_of_cities+i];
        //printf("city %d:(%.2lf,%.2lf)\n",i+1,cities[i].x,cities[i].y);
    }

    /*first store the original path*/
    /*for(i=0;i<number_of_cities;i++)
        fprintf(fp_out,"%.2lf,%.2lf\n",cities[i].x,cities[i].y);
    fprintf(fp_out,"%.2lf,%.2lf\n",cities[0].x,cities[0].y);
    fprintf(fp_out,"\n");*/

    /*Make a copy of cities*/
    City cities_tmp[number_of_cities];
    for(i=0;i<number_of_cities;i++)
    {
        cities_tmp[i].x=cities[i].x;
        cities_tmp[i].y=cities[i].y;
    }


    /*2.Hill Climbing*/
    t1=clock();
    traveling_salesman_by_hill_climbing(cities,number_of_cities);
    t2=clock();

    /*check the result*/
    //for(i=0;i<number_of_cities;i++)
    //    fprintf(fp_out,"%.2lf,%.2lf\n",cities[i].x,cities[i].y);
    //fprintf(fp_out,"%.2lf,%.2lf\n",cities[0].x,cities[0].y);
    
    /*3.Imporved Algorithm*/
    t3=clock();
    traveling_salesman_by_hill_climbing_improved(cities_tmp,number_of_cities);
    t4=clock();

    /*4.Print results*/
    printf("Total running time of Hill Climbing is: %lf secs.Result length is:%.4lf\n",(t2-t1)/(double)(CLOCKS_PER_SEC),get_path_length(cities,number_of_cities));
    print_path(cities,number_of_cities);
    printf("Total running time of Hill Climbing Improved is: %lf secs.Result length is:%.4lf\n",(t4-t3)/(double)(CLOCKS_PER_SEC),get_path_length(cities_tmp,number_of_cities));
    print_path(cities_tmp,number_of_cities);

    /*check the result*/
    //for(i=0;i<number_of_cities;i++)
    //    fprintf(fp_out,"%.2lf,%.2lf\n",cities[i].x,cities[i].y);
    //fprintf(fp_out,"%.2lf,%.2lf\n",cities[0].x,cities[0].y);
    
    return 0;
}
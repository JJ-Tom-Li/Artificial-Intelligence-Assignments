#include <math.h>
#define MAX_NUMBER_OF_CITIES 1000

typedef struct city{
    /*The data structure of city coordinate*/
    double x;
    double y;
}City;

/*通用 Functions*/
void print_path(City cities[MAX_NUMBER_OF_CITIES],int number_of_cities);
void city_swap(City cities[MAX_NUMBER_OF_CITIES],int city1,int city2);
double get_path_length(City cities[MAX_NUMBER_OF_CITIES],int number_of_cities);

/*Hill climbing*/
void traveling_salesman_by_hill_climbing(City cities[MAX_NUMBER_OF_CITIES],int number_of_cities);
int hill_climbing(City cities[MAX_NUMBER_OF_CITIES],int number_of_cities);

/*Improved Hill climbing*/
void traveling_salesman_by_hill_climbing_improved(City cities[MAX_NUMBER_OF_CITIES],int number_of_cities);
int hill_climbing_improved(City cities[MAX_NUMBER_OF_CITIES],int number_of_cities);
double difference_after_swap(City cities[MAX_NUMBER_OF_CITIES],int number_of_cities,int city1,int city2);


//Function Implements
void print_path(City cities[MAX_NUMBER_OF_CITIES],int number_of_cities)
{
    /*Print the all coordinates of cities*/
    int i;
    printf("Path:\n");
    for(i=0;i<number_of_cities;i++) printf("%.2lf ",cities[i].x);
    printf("\n");
    for(i=0;i<number_of_cities;i++) printf("%.2lf ",cities[i].y);
    printf("\n");
}

double get_path_length(City cities[MAX_NUMBER_OF_CITIES],int number_of_cities)
{
    /*Return the path length of cities.*/
    int i;
    double length = 0.0;
    for(i=1;i<number_of_cities;i++)
        length+=sqrt(pow(abs(cities[i].x-cities[i-1].x),2)+pow(abs(cities[i].y-cities[i-1].y),2));

    //Back to the start.
    length+=sqrt(pow(abs(cities[0].x-cities[number_of_cities-1].x),2)+pow(abs(cities[0].y-cities[number_of_cities-1].y),2));
    return length;
}

void city_swap(City cities[MAX_NUMBER_OF_CITIES],int city1,int city2)
{
    /*swap city1 and city2*/
    City tmp;
    tmp.x = cities[city1].x;
    cities[city1].x = cities[city2].x;
    cities[city2].x = tmp.x;
    tmp.y = cities[city1].y;
    cities[city1].y = cities[city2].y;
    cities[city2].y = tmp.y;
}

//Hill climbing-----------------------------------------------------------------------
void traveling_salesman_by_hill_climbing(City cities[MAX_NUMBER_OF_CITIES],int number_of_cities)
{
    print_path(cities,number_of_cities);
    printf("\n");
    printf("\nLength:%lf\n\n",get_path_length(cities,number_of_cities));

    /*Hill climbing the best result.*/
    hill_climbing(cities,number_of_cities);

    printf("End of hill climbing.\n"); 
}

int hill_climbing(City cities[MAX_NUMBER_OF_CITIES],int number_of_cities)
{
    int i,j,changed=1,min_swap_city1=0,min_swap_city2=0;
    double min_length=get_path_length(cities,number_of_cities);

    /*Swap all the possibilities to get the minimun length*/
    while(changed == 1)
    {
        for(i=0;i<number_of_cities-1;i++)
            for(j=i+1;j<number_of_cities;j++)
            {
                city_swap(cities,i,j);
                if(get_path_length(cities,number_of_cities)<min_length)
                {
                    /*Found shorter path.*/
                    min_swap_city1=i;
                    min_swap_city2=j;
                    min_length = get_path_length(cities,number_of_cities);
                }
                city_swap(cities,j,i);
            }
        changed = (min_swap_city1==0&&min_swap_city2==0)?0:1;   //If the two value haven't been changed,that means no swapping.
        if (changed==1)
        {
            //Swap the cities to get the best path.
            city_swap(cities,min_swap_city1,min_swap_city2);
            printf("\nSwap %d and %d\n",min_swap_city1+1,min_swap_city2+1);

            /*Restore the min value.*/
            min_swap_city1=0;
            min_swap_city2=0;
            /*Print the swap result.*/
            print_path(cities,number_of_cities);
            printf("\n");
            printf("\nLength:%.4lf\n\n",min_length);
        }
    }
    return changed;
}

//improved---------------------------------------------------------------------------------

void traveling_salesman_by_hill_climbing_improved(City cities[MAX_NUMBER_OF_CITIES],int number_of_cities)
{
    print_path(cities,number_of_cities);
    printf("\n");
    printf("\nLength:%lf\n\n",get_path_length(cities,number_of_cities));

    /*Hill climbing the best result.*/
    hill_climbing_improved(cities,number_of_cities);

    printf("End of hill climbing improved.\n"); 
}

int hill_climbing_improved(City cities[MAX_NUMBER_OF_CITIES],int number_of_cities)
{
    int i,j,changed=1,min_swap_city1=0,min_swap_city2=0;
    double diff=0.0,min_diff=10000;

    /*Swap all the possibilities to get the minimun length*/
    while(changed == 1)
    {
        for(i=0;i<number_of_cities-1;i++)
            for(j=i+1;j<number_of_cities;j++)
            {
                diff=difference_after_swap(cities,number_of_cities,i,j);
                if(diff<0&&min_swap_city1==0&&min_swap_city2==0)
                {
                    /*Found first shorter path.*/
                    min_swap_city1=i;
                    min_swap_city2=j;
                    min_diff=diff;
                }
                else if(diff<0&&diff<min_diff)
                {
                    /*Found shorter path.*/
                    min_swap_city1=i;
                    min_swap_city2=j;
                    min_diff=diff;
                }
            }
        changed = (min_swap_city1==0&&min_swap_city2==0)?0:1;
        if (changed==1)
        {
            //Swap the city into best path.
            city_swap(cities,min_swap_city1,min_swap_city2);
            printf("\nSwap %d and %d\n",min_swap_city1+1,min_swap_city2+1);

            /*Restore the min value.*/
            min_swap_city1=0;
            min_swap_city2=0;
            /*Print the swap result.*/
            print_path(cities,number_of_cities);
            printf("\n");
            printf("\nLength:%.4lf\n\n",get_path_length(cities,number_of_cities));
        }
    }
    return changed;
}

double difference_after_swap(City cities[MAX_NUMBER_OF_CITIES],int number_of_cities,int city1,int city2)
{
    double before_after[2]={0.0,0.0};//[0]:before [1]:after
    int left,right,i;

    if(city2-city1==1)
    {
        /*Two city are in sequence*/
        for(i=0;i<2;i++)
        {
            //calclulate the length between left and city1 
            //(x+n-1)%n=left,(x+n+1)%n=right
            left=(city1+number_of_cities-1)%number_of_cities;
            before_after[i]+=sqrt(pow(abs(cities[left].x-cities[city1].x),2)+pow(abs(cities[left].y-cities[city1].y),2));
    
            //calclulate the length between right and city2
            right=(city2+number_of_cities+1)%number_of_cities;
            before_after[i]+=sqrt(pow(abs(cities[right].x-cities[city2].x),2)+pow(abs(cities[right].y-cities[city2].y),2));

            //Swap cities
            city_swap(cities,city1,city2);
        }
    }
    else if(city1==0&&city2==number_of_cities-1)
    {
        /*Exception:first and last*/
        for(i=0;i<2;i++)
        {
            before_after[i]+=sqrt(pow(abs(cities[city1+1].x-cities[city1].x),2)+pow(abs(cities[city1+1].y-cities[city1].y),2));
            before_after[i]+=sqrt(pow(abs(cities[city2-1].x-cities[city2].x),2)+pow(abs(cities[city2-1].y-cities[city2].y),2));

            //Swap cities
            city_swap(cities,city1,city2);
        }
    }
    else
    {
        /*Two city are not in sequence*/
        for(i=0;i<2;i++)
        {
            //calclulate the length on left and right of city1 before swap
            left=(city1+number_of_cities-1)%number_of_cities;
            right=(city1+number_of_cities+1)%number_of_cities;
            before_after[i]+=sqrt(pow(abs(cities[left].x-cities[city1].x),2)+pow(abs(cities[left].y-cities[city1].y),2));
            before_after[i]+=sqrt(pow(abs(cities[right].x-cities[city1].x),2)+pow(abs(cities[right].y-cities[city1].y),2));
            
            //calclulate the length on left and right of city1 before swap
            left=(city2+number_of_cities-1)%number_of_cities;
            right=(city2+number_of_cities+1)%number_of_cities;
            before_after[i]+=sqrt(pow(abs(cities[left].x-cities[city2].x),2)+pow(abs(cities[left].y-cities[city2].y),2));
            before_after[i]+=sqrt(pow(abs(cities[right].x-cities[city2].x),2)+pow(abs(cities[right].y-cities[city2].y),2));
            
            //Swap cities
            city_swap(cities,city1,city2);
        }
    }

    double diff = before_after[1]-before_after[0];
    return diff;
}
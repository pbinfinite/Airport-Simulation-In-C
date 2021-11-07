/*NAME: PRAGNA BHARGAVA
SRN: PES1UG19CS332
SECTION: R
ROLL.NO.5
Problem Solving With C ASSIGNMENT

QUESTION 5
a2_pragna_q5.c (the second c file)*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#include <limits.h>
#include "server.h"
#define MAX 10

/*In this program, we use pseudo random numbers to generate the no.of expected arrivals and departures per unit time.
Pseudo random which are numbers which are found after some arithmetic operations on the previous number.

The function randomize() is used to provide a different starting point each time srand() is run.
After using randomize(), the no.of planes arriving is generated randomly using poisson distribution in the randomnumber() function.*/

void randomize()
{
    srand((time(NULL)%10000));
}

int randomfuel(int maxfuel)         //to randomly decide the fuel of each plane
{
    int num;
    num=(rand()%maxfuel)+1;        //num = ( rand()%(upper-lower+1)) + 1;
    return num;
}

int randomnumber(float expect)  //to randomly generate number of planes joining the queue in each unit of time
{                               //poisson function to generate random numbers
    int n = 0 ;
    float x=1, em = exp(-expect);
    x =x*(rand()/(float)RAND_MAX) ;
    while(x>em)
    {
        n++;
        x =x*(rand()/(float)RAND_MAX) ;
    }
    return n;
}

struct plane * addtoq(struct plane *front, struct plane *ptemp)   // to add to a queue at the end
{
    struct plane *track;
    if(front!=NULL)
    {
        for(track=front;track->next!=NULL;track=track->next);
            track->next=ptemp;
        return front;
    }
    else
        return ptemp;
}

void sortland(struct qqq *pq)                                       //to sort the queue based on fuel levels of the plane
{                                                                   //such that the planes with lowest fuel remaining are at the front
    struct plane *p1;
    struct plane *p2;
    int idt, fuelt, timet;
    for(p1=pq->front; p1!=NULL; p1=p1->next){
        for(p2=p1->next; p2!=NULL; p2=p2->next){
            if(p1->fuel > p2->fuel){
                fuelt = p1->fuel;       idt = p1->id;      timet = p1->tm;
                p1->fuel = p2->fuel;    p1->id = p2->id;   p2->tm = p2->tm;
                p2->fuel = fuelt;       p2->id = idt;      p2->tm = timet;
            }
        }
    }
    //return front;
}

struct plane * delq(struct plane *front)                    //to delete a plane from the front of the queue.
{
    struct plane *ptemp;
    if(front==NULL)
    {
        printf("List is empty\n\n");
        return front;
    }
    else
    {
        ptemp=front->next;
        front=ptemp;
        return front;
    }
}

void qsetzero(struct qqq *pq)               //to initialize the members of qqq structure.
{
    pq->front=NULL;
    pq->count=0;
    pq->rear=NULL;
}

void setairport(struct airport *ap)         //to initialize the members of airport structure
{
    ap->idletm=0;
    ap->nplanes=0;
    ap->ntakeoff=0;
    ap->nland=0;
    ap->nrefuse=0;
    ap->nwait_take=0;
    ap->nwait_land=0;
    ap->ncrash=0;
}

void start_sim(float *expectland,float *expecttake,int *maxfuel,int *maxsim)  //start the simulation, obtain user input, state the assumptions made.
{
    int flag=1;
    printf("\nThis is an airport simulation.\n");
    printf("The airport consists of only one runway which is used for both landing and takeoff.\n");
    printf("Only one plane can land or takeoff in 1 unit of time.\n");
    printf("Therefore, the airport has 2 queue's: Landing queue and the Takeoff queue which planes join when they arrive.\nThe maximum queue size is taken as %d.\n",MAX);
    printf("Each plane, when it arrives, has a randomly generated fuel value, calculated in units of time remaining.\n");
    printf("In this program, the randomly generated fuel lies between 1 and %d units of time remaining.\n",*maxfuel);
    printf("It is assumed (as per the question) better to keep a plane waiting on the ground than waiting in the air. So, landing is given priority over takeoff.\n");
    printf("The planes in the landing queue are such that the plane having lesser fuel remaining is allowed to land first. The other planes are made to wait.\n");
    printf("Hence a plane may crash when waiting in the landing queue due to insufficient fuel.\n");
    printf("\nIn this program, the simulation ends when a plane crashes due to insufficient fuel.\n");
    printf("The statistics are then printed and give information about the how busy the airport can become before a plane crashes.\n");
    printf("\nIf no planes have crashed after %d units of time, the simulation stops and the statistics is printed.\n",*maxsim);
    printf("This can happen as the plane arrival and departures and the fuel level is randomly generated.\n");
    printf("\nThe user is expected to enter the expected number of arrivals(to land) and departures(to takeoff) per unit time,");
    printf("\nsuch that the sum of expected number of arrivals and departures is less than or equal to 1.0\n");
    printf("\n");
    do
    {
        flag=1;
        printf("How many arrivals to land per unit of time: ");
        scanf("%f",expectland);
        printf("How many departures to takeoff per unit of time: ");
        scanf("%f",expecttake);
        if((*(expectland) + *(expecttake))>1.0)
        {
            printf("The airport will be saturated.Enter again...\n\n");
            flag=0;
        }
        else if(*(expectland)<0.0 || *(expecttake)<0.0)
        {
            printf("The number should be a non-negative number. Enter again...\n\n");
            flag=0;
        }
    }while(flag==0);
    randomize();
}

struct plane * fuelupdate(struct plane *front)   // to update the fuel level of planes in the queue after each unit of time
{
    struct plane *track;
    for(track=front;track!=NULL;track=track->next)
    {
        track->fuel=track->fuel-1;
    }
    return front;
}

void displayq(struct qqq *land)                 //to display the planes in the queue
{
    struct plane *track;
    for(track=land->front;track!=NULL;track=track->next)
        {
            printf("Plane %d( f=%d )---",track->id,track->fuel);
        }
}

void conclude(struct airport *ap,int currsim)                       //to display the statistics after the conclusion of the simulation(if no plane has crashed)
{
    printf("\n\nSimulation has concluded after %d units of time.\n",(currsim-1));
    printf("Total number of planes processed = %d \n",ap->nplanes);
    printf("Total number of planes landed = %d\n",ap->nland);
    printf("Total number of planes taken off = %d\n",ap->ntakeoff);
    printf("Total number of planes refused = %d\n",ap->nrefuse);
    printf("Total number of planes crashed = %d\n",ap->ncrash);
    printf("Total number of planes left to land in queue = %d\n",ap->land.count);
    printf("Total number of planes left to take off in queue = %d\n",ap->takeoff.count);
    printf("The runway was idle for %d units of time.\n",ap->idletm);

    if(currsim >0)
        printf("Percentage of time runway idle: %0.2f \n",((float)(ap->idletm/currsim))*100.0);

    if(ap->nland >0)
        printf("Average wait time to land: %0.2f units of time\n",((float)(ap->nwait_land/ap->nland)));

    if(ap->ntakeoff >0)
        printf("Average wait time to take off: %0.2f units of time\n",((float)(ap->nwait_take/ap->ntakeoff)));
    printf("\n\n");
}

void landingfn(struct airport *cr,int currsim)                                      //to print statistics after a plane has crashed.
{
        struct airport *ln;
        ln =(struct airport*)malloc(sizeof(struct airport)*1);
        ln = cr;
        printf("\nHow busy was the airport before the crash ?\n");
        printf("\nThe first plane crashed after %d number of simulations.\n",currsim);
        printf("Total number of planes processed = %d \n",ln->nplanes);
        printf("Total number of planes landed = %d\n",ln->nland);
        printf("Total number of planes taken off = %d\n",ln->ntakeoff);
        printf("Total number of planes refused = %d\n",ln->nrefuse);
        printf("Total number of planes crashed = %d\n",ln->ncrash);
        printf("Total number of planes left to land in queue = %d\n",ln->land.count);
        printf("Total number of planes left to take off in queue = %d\n",ln->takeoff.count);
        printf("The runway was idle for %d units of time.\n",ln->idletm);
        if(currsim >0)
        printf("Percentage of time runway idle: %0.2f \n",((float)ln->idletm/currsim)*100.0);

        if(ln->nland >0)
            printf("Average wait time to land: %0.2f units of time\n",((float)(ln->nwait_land/ln->nland)));

        if(ln->ntakeoff >0)
            printf("Average wait time to take off: %0.2f units of time\n",((float)(ln->nwait_take/ln->ntakeoff)));
}

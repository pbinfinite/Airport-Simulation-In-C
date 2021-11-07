#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#include <limits.h>
#include "server.h"
#define MAX 10


int main()
{
    struct airport *ap;
    struct qqq *land;
    struct qqq *takeoff;
    land=(struct qqq*)malloc(sizeof(struct qqq)*1);                 //allocating memory for 2 queue's and the airport
    takeoff=(struct qqq*)malloc(sizeof(struct qqq)*1);
    ap=(struct airport*)malloc(sizeof(struct airport)*1);

    land= &(ap->land);                                             //let the landing queue of the airport be named as land.
    takeoff = &(ap->takeoff);                                      //let the takeoff queue of the airport be named as takeoff.
    struct plane *ptemp;
    int currsim,i;
    int rd1,rd2;
    int crsh=0;
    int maxfuel=3;                  //this is the maximum fuel value. It has been set to 3 units of time remaining. Therefore, the fuel is in the range 1 to 3.
    int maxsim=1000;                //this is the maximum no.of simulations. It has been set to 1000 simulations.
				    //The simulation after 1000 simulations if no plane has crashed.
    char disp='n';
    float expectland,expecttake;                        //expectland and expecttake are the expected number of planes arriving to land/takeoff per unit time.

    setairport(ap);                                     //set airport variables
    qsetzero(land);                                     //set land and takeoff queue variables
    qsetzero(takeoff);
    start_sim(&expectland,&expecttake,&maxfuel,&maxsim);            //start the simulation, take user input
    int chrr;
    while( (chrr = getchar() ) != EOF && chrr != '\n' ){;}
    
    printf("Would you like to display the landing and takeoff queue's( y or n ) ?\n");
    scanf("%c",&disp);
    currsim=1;
    while(currsim<=maxsim)
    {
      rd1=randomnumber(expectland); printf("\n");       //getting random number for number of planes to arrive to join landing queue.
      if((rd1)!=0)
      {
        for(i=0;i<rd1;i++)
        {
            //a plane arrives to join landing queue;
            ap->nplanes++;
            ptemp=(struct plane*)malloc(sizeof(struct plane)*1);        //initializing a plane
            ptemp->id=ap->nplanes;
            ptemp->tm=currsim;
            ptemp->fuel=randomfuel(maxfuel);                    //random value for fuel level of plane
            ptemp->next=NULL;

            if( land->count <MAX){
                (land->front) = addtoq(land->front,ptemp);                  //plane joined landing queue
                land->count++;
                printf("\tPlane %d waiting to land. Fuel = %d units of time remaining.",ptemp->id,ptemp->fuel);
                printf("  ; In landing queue: %d planes\n",land->count);
                sortland(land);                                                    //the planes sorted according to fuel level
            }
            else
            {
                printf("\tLanding Queue is full. Plane %d has to try later.\n",ptemp->id);      //a plane is refused when the landing queue is full
                (ap->nrefuse)++;
            }
        }
      }
      rd2=randomnumber(expecttake);                             //getting random number for number of planes to arrive to join takeoff queue.
      if((rd2)!=0)
      {
        for(i=0;i<(rd2);i++)
        {
            //a plane arrives to join takeoff queue;
            ap->nplanes++;
            ptemp=(struct plane*)malloc(sizeof(struct plane)*1);                //a plane arrives to join takeoff queue
            ptemp->id=ap->nplanes;
            ptemp->tm=currsim;
            ptemp->fuel=randomfuel(maxfuel);
            ptemp->next=NULL;

            if(takeoff->count <MAX){
                (takeoff->front) = addtoq((takeoff->front),ptemp);
                (takeoff->count)++;
                printf("\tPlane %d waiting to takeoff. Fuel = full capacity",ptemp->id);
                printf("  ; In takeoff queue: %d planes\n",takeoff->count);
            }
            else
            {
                printf("\tTakeoff Queue is full. Plane %d has to try later.\n",ptemp->id); // a plane is refused when the takeoff queue is full.
                ap->nrefuse++;
            }
        }
      }
        //display
        if(disp=='y'){
            if(land->count==0)
                printf("\tLanding Queue is empty.");
            else{
                printf("\tLanding: ");
                displayq(land);             //to display queue
            }
            printf("\n");
            if(takeoff->count==0)
                printf("\tTakeoff Queue is empty.");
            else{
                printf("\tTakeoff: ");
                displayq(takeoff);
            }
            printf("\n");
        }
        //operation
        printf("\n");
        printf("%d: ",currsim);
        if(land->count !=0){
            ap->nwait_land = ap->nwait_land + currsim - land->front->tm;      //the sum of waiting time in the queue before a plane lands.(Used to find average time).
        }
        if(takeoff->count!=0){
            ap->nwait_take = ap->nwait_take + currsim - takeoff->front->tm;   //the sum of waiting time in the queue before a plane takes off.(Used to find average time).
        }

        if(land->count==0 && takeoff->count>0){
            printf("Plane %d took off.",takeoff->front->id);
            printf("  ; In takeoff queue %d planes.\n",takeoff->count-1);
            (takeoff->front) = delq(takeoff->front);                            //a plane takes off if the landing queue is empty(and takeoff queue is not empty)
            ap->ntakeoff++;
            (takeoff->count)--;
        }
        else if(land->count>0)
        {
            struct plane *track;
            track= (land->front);
            //checking for crash
            if(track->fuel<1)
            {
                crsh=1;
                struct plane *ct;
                for(ct=track;ct!=NULL;ct=ct->next){
                    if(ct->fuel<1){
                        printf("Plane %d crashed due to insufficient fuel.\n",ct->id);
                        land->front = delq(ct);                                         //a plane crashed
                        (land->count)--;
                        ap->ncrash++;
                        break;                                                 //whenever a plane crashes, the simulation ends as the aim of this program is
                    }                                                          //to find out how busy the airport can become before a planes start to crash.
                }
            }
            else
            {
                printf("Plane %d landed. Fuel = %d units of time remaining.",track->id,track->fuel-1);
                land->front = delq(track);                                                  // a plane landed from landing queue
                (land->count)--;
                ap->nland++;
                printf("  ; In landing queue %d planes\n",land->count);
            }

        }
        else if(land->count ==0 && takeoff->count==0){
            printf("The runway is idle.\n");                //if no planes are available to takeoff or land, the runway is idle
            ap->idletm++;
        }
        if(land->count !=0){
            land->front = fuelupdate(land->front);          //the fuel of the planes is updated after every unit of time(simulation)
        }
        if(crsh==1){
            break;
            break;
        }
        currsim++;
    }
    if(crsh==0)
        conclude(ap,currsim);           //if no plane has crashed after 1500 units of time, the simulation ends and the statistics are printed.
    if(crsh==1)
        landingfn(ap,currsim);          //If a plane crashes, the simulation ends and the statistics are printed as to how busy the airport can become
                                        //before a plane crashes
    return 0;
}

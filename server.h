#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#include <limits.h>
#define MAX 10


struct plane            //the structure plane
{
    int id;
    int tm;
    int fuel;
    struct plane *next;
};

struct qqq              //the structure queue(landing and takeoff queue)containing planes
{
    struct plane *front;
    struct plane *rear;
    int count;
    struct plane *parr;
};

struct airport          //the structure airport containing the landing and takeoff queue and other airport variables;
{
    struct qqq land;
    struct qqq takeoff;
    int idletm;
    int nplanes;
    int ntakeoff;
    int nland;
    float nwait_take;
    float nwait_land;
    int ncrash;
    int nrefuse;
    struct plane *ptemp;
};
//functions
void randomize();
int randomfuel(int maxfuel);
int randomnumber(float expect);
struct plane * addtoq(struct plane *front, struct plane *ptemp);
void sortland(struct qqq *pq);
struct plane * delq(struct plane *front);
void qsetzero(struct qqq *pq);
void setairport(struct airport *ap);
void start_sim(float *expectarrive,float *expectdepart,int *maxfuel,int *maxsim);
struct plane * fuelupdate(struct plane *front);
void displayq(struct qqq *land);
void conclude(struct airport *ap,int currsim);
void landingfn(struct airport *cr,int currsim);




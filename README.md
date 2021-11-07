# Airport-Simulation-In-C
Airport simulation using priority queue and linked lists

Question:
Let us consider a small but busy airport with only one runway. In each unit of time, one plane can land or takeoff, but not both. Planes arrive ready to land or ready to 
takeoff at random times, so at any given unit of time, the runway may be idle or a plane may be taking off and there may be several planes waiting either to land or 
takeoff. We therefore need two queues, called landing and takeoff, to hold these planes. It is better to keep a plane waiting on the ground than in air, so a small airport
allows a plane to takeoff only if there are no planes waiting to land. When each plane arrives to land, it will (as part of its data) have a (randomly generated) fuel level,
measures in units of time remaining. If the plane does not have enough fuel to wait in the queue, it is allowed to land immediately.
Hence the planes in the landing queue may be kept waiting additional units and so may run out of fuel themselves. Check this out as part of the landing function and 
find out how busy the airport can become before planes start to crash from running out of fuel.  Please use queue's for this project. Please use singly linked lists.
Whenever you need to add, add to the end of the list and whenever you need to delete, delete from the beginning of the list (FIFO).

Assumptions made:
- It has been assumed as per the question that takeoff can happen only if the landing queue is empty.   
- The expected number of planes arriving at the aiport (to land) and departures (to takeoff), per unit of time is obtained as user input. It is such that the sum of number of 
   planes arriving at the airport to land and to takeoff is less than or equal to 1. This is because only one plane can land or takeoff per unit of time. 
- The number of planes arriving to land and takeoff in each unit of time is determined using poisson distribution function (pseudo random numbers) as per the user input
   (expected number of arrivals to land or takeoff per unit time).
- The fuel level, measured in units of time remaining is obtained randomly within a range. The upper limit has been set in the code and can be changed within the code.
- When a plane crashes, the simulation ends and the statistics are printed. This tells us how busy the airport can become before a plane crashes.
- The maximum number of simuations has been set to 1000. The simulation ends after 1000 units of time, if no crash happened till then. For example, if the expected 
   number of arrivals and departures has been set to 0.1 each, the planes joining the queue decreases and the runway remains idle for a longer units of time. This decreases
   the probability of a crash. Therefore, we set a limit to the number of units of time the simultion runs (though the simulation is random every time the program is executed).
   This value has been set in the code and can be changed within the code.

Execution:
- The program can be executed using the makefile. It has 2 c (.c) files and a header file (.h).          
- To execute in Windows command prompt:
-   mingw32-make -f makefile.mk
-   a.exe
- To execute in Ubuntu terminal:
-   make -f makefile.mk
-   ./a.out       

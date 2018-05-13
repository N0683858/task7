#include <iostream>
#include <fstream>


#include "logs.h"
#include "route.h"
#include "track.h"
#include "gridworld_route.h"
#include "gridworld_track.h"


using namespace GPS;


using std::cout;
using std::endl;


void testRoute(std::string fileName)
{

    const std::string filePath = LogFiles::GPXRoutesDir + fileName + ".gpx";
    const bool isFileName = true;


    Route route = Route(filePath, isFileName);
    Route route = Route(filePath,isFileName);


    cout << "Route name: " << route.name() << endl;

    cout << "Net Height Gain: " << route.netHeightGain() << endl;
    cout << "Min elevation: " << route.minElevation() << endl;
    cout << "Max elevation: " << route.maxElevation() << endl;

    cout << "Total route length: " << route.totalLength() << endl;
    cout << "total Height gain: " << route.totalHeightGain() << endl;

    cout << "Total route length: " << route.totalLength() << endl;
    cout << "total Height gain: " << route.totalHeightGain() << endl;

    cout << endl;
}



int main()
{
	    testRoute("NorthYorkMoors");
	    testRoute("ABCD");
}

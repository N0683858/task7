#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "route.h"
#include "track.h"

using namespace GPS;

BOOST_AUTO_TEST_SUITE (Route_numPositions)

const bool isFileName = true;



//1) At least 1 Position

// This tests that there is at least 1 position in the file "n0719388data1.gpx"
// 
//

BOOST_AUTO_TEST_CASE(MinimumNumberOfPositions)_END()
{


Route route = Route(LogFiles::GPXRoutesDir + "n0719388data1.gpx", isFileName);
unsigned int numOfPositions = route.numPositons();
BOOST_CHECK_GT ( numOfPositions,1);

}



//2) Correct number of positions output

// Test that the number of positions outputs the same value as intended.

BOOST_AUTO_TEST_CASE(CorrectNoOfPositions)

{

Route route = Route(LogFiles::GPXRoutesDir + "n0719388data1.gpx", isFileName);
unsigned int numOfPositions = route.numPositions();
unsigned int ActualNumberOfPositions = "2";
BOOST_CHECK_EQUAL(NumOfPositions, ActualNumberOfPositions);

}



//3)(distancebetween above granularity threshold)

//   sqrt((x2-x1)^2+(y2-y1)^2) =distance
//-62.372262972335676068
//-63.925960253788176146
// 

// distance between points in "n0719388data1.gpx" is 2109.329m, exceed granularity by far
// set a granularity of 50 for sake of test
// Test that when the distance between two points exeeds the granularity limit, no changes are made to the number of positions.

BOOST_AUTO_TEST_CASE(GradularityDoesntOccur)
{

Route route = Route(LogFiles::GPXRoutesDir + "n0719388data1.gpx", isFileName,50); 
unsigned int ActualNumberOfPositions = "2";
BOOST_CHECK_EQUAL(route.numPositions(), ActualNumberOfPositions);
}



//4)(distance between below granularity threshold)
//Similar test to the above except graularity has now been set so that the distance between the two points no longer exceeds the granularity limit, hence a position should be thrown.
//2109.329 < 2500

BOOST_AUTO_TEST_CASE(GradularityDoesOccur)

{
Route route = Route(LogFiles::GPXRoutesDir + "n0719388data1.gpx", isFileName,2500); 
unsigned int ActualNumberOfPositions = "1";
BOOST_CHECK_EQUAL(route.numPositions(), ActualNumberOfPositions);

}

//Longitude   -180   +180
//Latitude    -90     +90

//5) Granularity Edge Values Upper (Largest value)
//111km per degree /2 19980, granularity wont be any larger than this.
// should not throw any positions


BOOST_AUTO_TEST_CASE(GranularityUpperEdge)

{

Route route = Route(LogFiles::GPXRoutesDir + "n0719388data1.gpx", isFileName,19980)
unsigned int ActualNumberOfPositions = "2";
BOOST_CHECK_EQUAL(route.numPositions(), ActualNumberOfPositions);

}


// Lower edge value for granularity should throw one position due to distance being over 1m_END()
//6) Granularity Edge Values Lower (Small Value)

BOOST_AUTO_TEST_CASE(GranularityLowerEdge)

{
Route route = Route(LogFiles::GPXRoutesDir + "n0719388data1.gpx", isFileName,1)
unsigned int ActualNumberOfPositions = "1";
BOOST_CHECK_EQUAL(route.numPositions(), ActualNumberOfPositions);
}


BOOST_AUTO_TEST_SUITE_END()

#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "route.h"
#include "track.h"

using namespace GPS;

BOOST_AUTO_TEST_SUITE( Route_MaxLat )

const bool isFileName = true;

// Checking that the MaxLatitude function can find the highest Latitude within the ABCD.gpx given route log
BOOST_AUTO_TEST_CASE( RouteABCD )
{
   Route route = Route(LogFiles::GPXRoutesDir + "ABCD.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.maxLatitude(), 0.179964);
}

// Checking that the MaxLatitude function can find the highest Latitude within the A1B3C.gpx given track log
BOOST_AUTO_TEST_CASE( TrackA1B3C )
{
   Track track = Track(LogFiles::GPXTracksDir + "A1B3C.gpx", isFileName);
   BOOST_CHECK_EQUAL( track.maxLatitude(), 0.179964);
}

// Checking that the MaxLatitude function can find the highest Latitude within the NorthYorkMoors.gpx given route log.
BOOST_AUTO_TEST_CASE( RouteNorthYorkMoors )
{
   Route route = Route(LogFiles::GPXRoutesDir + "NorthYorkMoors.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.maxLatitude(), 54.50918734073639);
}


//MY TESTS

// Checking that the MaxLatitude function can find the highest Latitude within the RouteStationaryPoints.gpx route log.
//This Route contains 5 points, all containing the same Latitude, this will test that the function MaxLatitude will be able
//to get the highest latitude out of the points
BOOST_AUTO_TEST_CASE( RouteStationaryPoints )
{
   Route route = Route(LogFiles::GPXRoutesDir + "RouteStationaryPoints.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.maxLatitude(), 53.1381);
}



//Checking function can handle negative numbers with stationary points in a Route
BOOST_AUTO_TEST_CASE( RouteStationaryNegativePoints )
{
   Route route = Route(LogFiles::GPXRoutesDir + "RouteStationaryNegativePoints.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.maxLatitude(), -29.82);
}


//This test checks that the function can still get the correct MaxLattiude from a route with points that increase in longitude, but latitude stay the same
BOOST_AUTO_TEST_CASE( RouteChangingLongitude )
{
   Route route = Route(LogFiles::GPXRoutesDir + "RouteChangingLongitude.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.maxLatitude(), 53.1381);
}

//This test checks if the function MaxLat can find the maximum latitude when Route has points with negative latitude, and changing negative longitude
BOOST_AUTO_TEST_CASE( RouteNegativeChangingLongitude )
{
   Route route = Route(LogFiles::GPXRoutesDir + "RouteNegativeChangingLongitude.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.maxLatitude(), -11.32);
}

//To see if MaxLatitude can find the correct maximum latitude when the first point has the highest latitude, and then all points after decrease in latitude
BOOST_AUTO_TEST_CASE ( RouteLatiudeDecreases )
{
    Route route = Route(LogFiles::GPXRoutesDir + "RouteLatiudeDecreases.gpx", isFileName);
    BOOST_CHECK_EQUAL( route.maxLatitude(), 51.68);
}

//Route file with a Negative Latitude that decreases
BOOST_AUTO_TEST_CASE ( RouteNegativeLatiudeDecreases )
{
    Route route = Route(LogFiles::GPXRoutesDir + "RouteNegativeLatiudeDecreases.gpx", isFileName);
    BOOST_CHECK_EQUAL( route.maxLatitude(), -34.82);
}

//Route file with a Latitude that increases
BOOST_AUTO_TEST_CASE ( RouteLatitudeIncreases )
{
    Route route = Route(LogFiles::GPXRoutesDir + "RouteLatiudeIncreases.gpx", isFileName);
    BOOST_CHECK_EQUAL( route.maxLatitude(), 65.18 );
}

//Route file with a negativev Latitude that increases
BOOST_AUTO_TEST_CASE ( RouteNegativeLatiudeIncreases )
{
    Route route = Route(LogFiles::GPXRoutesDir + "RouteNegativeLatiudeIncreases.gpx", isFileName);
    BOOST_CHECK_EQUAL( route.maxLatitude(), -41.94 );
}

//Route log  with latitude decreasing and then increasing
BOOST_AUTO_TEST_CASE ( RouteLatDecreaseThenIncrease )
{
    Route route = Route(LogFiles::GPXRoutesDir + "RouteLatDecreaseThenIncrease.gpx", isFileName);
    BOOST_CHECK_EQUAL( route.maxLatitude(), 24.46 );
}

//Route log with Increasing latitude then decreasing
BOOST_AUTO_TEST_CASE ( RouteLatIncreaseThenDecrease )
{
    Route route = Route(LogFiles::GPXRoutesDir + "RouteLatIncreaseThenDecrease.gpx", isFileName);
    BOOST_CHECK_EQUAL( route.maxLatitude(), 35.18 );
}

//Route With Latitude of 89.9 testing edge cases. As lat can only be between -90 and 90
BOOST_AUTO_TEST_CASE ( RouteLatAt89 )
{
    Route route = Route(LogFiles::GPXRoutesDir + "RouteLatAt89.gpx", isFileName);
    BOOST_CHECK_EQUAL( route.maxLatitude(), 89.9818 );
}

//Testing the other edge case of -89 in a route log to see if the function can handle this number
BOOST_AUTO_TEST_CASE ( RouteLatAtNegative89 )
{
    Route route = Route(LogFiles::GPXRoutesDir + "RouteLatAtNegative89.gpx", isFileName);
    BOOST_CHECK_EQUAL( route.maxLatitude(), -62.8436 );
}

//Test case to see if the Maximum latitude was able to be identified in a Route log with only 1 position
BOOST_AUTO_TEST_CASE ( RouteSinglePosition )
{
    Route route = Route(LogFiles::GPXRoutesDir + "RouteSinglePosition.gpx", isFileName);
    BOOST_CHECK_EQUAL( route.maxLatitude(), 42.74 );
}

//Test case to see if MaximumLatitude can find the correct value of lattitude when there is 30 different points within the route log
BOOST_AUTO_TEST_CASE ( Route30Positions )
{
    Route route = Route(LogFiles::GPXRoutesDir + "Route30Positions.gpx", isFileName);
    BOOST_CHECK_EQUAL( route.maxLatitude(), 60.7364 );
}

//Test case to check if a route log with a latitude over 90 (Out of range) is selected as the maximum latitude
//Even though a number over 90 is not valid, the function should still return that number, as it is the
//route constructors job to Reject invalid information
BOOST_AUTO_TEST_CASE ( RouteLatitudeGreater90 )
{
    Route route = Route(LogFiles::GPXRoutesDir + "RouteLatitudeGreater90.gpx", isFileName);
    BOOST_CHECK_EQUAL ( route.maxLatitude(), 90.0001);
}

//Test case to check if a latitude smaller than -90 does not stop the function from working
//the function should still send back the highest latitude in the log, even if one of the points
//latitude is out of range. It is the route constructors to reject invalid data
BOOST_AUTO_TEST_CASE ( RouteLatitudeSmallerNegative90 )
{
    Route route = Route(LogFiles::GPXRoutesDir + "RouteLatitudeSmaller90.gpx", isFileName);
    BOOST_CHECK_EQUAL ( route.maxLatitude(), -62.1736);
}

//Test designed to see if the MaxLatitude function still works when 0 is the highest lat in the Route log
BOOST_AUTO_TEST_CASE ( RouteLatAt0 )
{
    Route route = Route(LogFiles::GPXRoutesDir + "RouteLatAt0.gpx", isFileName);
    BOOST_CHECK_EQUAL( route.maxLatitude(), 0 );
}


//Testing if the Max lat function can detect changes of latitude between points of 0.0001 difference
BOOST_AUTO_TEST_CASE ( RouteLatitudeDiff0001 )
{
    Route route = Route(LogFiles::GPXRoutesDir + "RouteLatitudeDiff0001.gpx", isFileName);
    BOOST_CHECK_EQUAL( route.maxLatitude(), 10.0002);
}


BOOST_AUTO_TEST_SUITE_END()


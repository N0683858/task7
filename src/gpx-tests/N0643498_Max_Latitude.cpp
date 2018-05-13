#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "route.h"
#include "track.h"

using namespace GPS;

BOOST_AUTO_TEST_SUITE(Route_Max_Latitude)

const bool isFileName = true;

// Testing whether the function works with the regular pre-made GPX log named NorthYorkMoors.gpx.
BOOST_AUTO_TEST_CASE( Route_NorthYorkMoors_Test )
{
   Route route = Route(LogFiles::GPXRoutesDir + "NorthYorkMoors.gpx", isFileName);
   BOOST_CHECK_EQUAL(route.maxLatitude(), 54.50918734073639);
}

//Testing to see how the function deals with a log file where all of the latitude positions are set to zero
BOOST_AUTO_TEST_CASE ( Route_Latitude_At_Zero_Test )
{
    Route route = Route(LogFiles::GPXRoutesDir + "Route_Latitude_At_Zero_Log.gpx", isFileName);
    BOOST_CHECK_EQUAL( route.maxLatitude(), 0 );
}

//Testing to see whether the function correctly gives a correct value when there is only one position within the log
BOOST_AUTO_TEST_CASE ( Route_One_Position_Test )
{
    Route route = Route(LogFiles::GPXRoutesDir + "Route_One_Position_Log.gpx", isFileName);
    BOOST_CHECK_EQUAL( route.maxLatitude(), 63.47589375938599 );
}

//Testing to see whether the function can tell the difference between positions with a difference of less than 1
BOOST_AUTO_TEST_CASE ( Route_Minute_Differences_Test )
{
    Route route = Route(LogFiles::GPXRoutesDir + "Route_Minute_Differences_Log.gpx", isFileName);
    BOOST_CHECK_EQUAL( route.maxLatitude(), 23.42204773426059);
}

// Testing whether the function can find the correct latitude within a log of unchanging points.
BOOST_AUTO_TEST_CASE( Route_Unchanging_Points_Test )
{
   Route route = Route(LogFiles::GPXRoutesDir + "Route_Unchanging_Points_Log.gpx", isFileName);
   BOOST_CHECK_EQUAL(route.maxLatitude(), 54.42204773426058);
}

//Testing whether the function can still produce the correct latitude when the only part that changes is longitude
BOOST_AUTO_TEST_CASE( Route_Different_Longitude_Test )
{
   Route route = Route(LogFiles::GPXRoutesDir + "Route_Different_Longitudes_Log.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.maxLatitude(), 54.42204773426058);
}

//Testing to see if the function can find the correct value with a log of negative latitudes
BOOST_AUTO_TEST_CASE( Route_Negative_Latitude_Test )
{
   Route route = Route(LogFiles::GPXRoutesDir + "Route_Negative_Latitudes_Log.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.maxLatitude(), -34.42204773426058);
}

//Testing whether the function can correctly give the correct value when the highest lat is at the edge of its positive boundary
BOOST_AUTO_TEST_CASE ( Route_Positive_Edge_Test)
{
    Route route = Route(LogFiles::GPXRoutesDir + "Route_Positive_Edge_Log.gpx", isFileName);
    BOOST_CHECK_EQUAL( route.maxLatitude(), 89.99999999999999);
}

//Testing whether the function can correctly give the correct value when the highest lat is at the edge of its negative boundary
BOOST_AUTO_TEST_CASE ( Route_Negative_Edge_Test )
{
    Route route = Route(LogFiles::GPXRoutesDir + "Route_Negative_Edge_Log.gpx", isFileName);
    BOOST_CHECK_EQUAL( route.maxLatitude(), -89.99999999999999 );
}

//Testing whether the function can return the correct value when the latitudes are in ascending order
BOOST_AUTO_TEST_CASE ( Route_Ascending_Order_Test )
{
    Route route = Route(LogFiles::GPXRoutesDir + "Route_Ascending_Order_Log.gpx", isFileName);
    BOOST_CHECK_EQUAL( route.maxLatitude(), 89.10856639294758);
}

//Testing whether the function can return the correct value when the latitudes are in descending order
BOOST_AUTO_TEST_CASE ( Route_Descending_Order_Test )
{
    Route route = Route(LogFiles::GPXRoutesDir + "Route_Descending_Order_Log.gpx", isFileName);
    BOOST_CHECK_EQUAL( route.maxLatitude(), 88.10856639294758);
}

//Testing to see how the function deals with a latitude position that is over the positive boundary of 90
BOOST_AUTO_TEST_CASE ( Route_Over_Positive_Boundary_Test )
{
    Route route = Route(LogFiles::GPXRoutesDir + "Route_Over_Positive_Boundary_Log.gpx", isFileName);
    BOOST_CHECK_THROW( route.maxLatitude(), std::out_of_range);
}

//Testing to see how the function deals with a latitude position that is over the negative boundary of -90
BOOST_AUTO_TEST_CASE ( Route_Over_Negative_Boundary_Test )
{
    Route route = Route(LogFiles::GPXRoutesDir + "Route_Over_Negative_Boundary_Log.gpx", isFileName);
    BOOST_CHECK_THROW( route.maxLatitude(), std::out_of_range);
}

BOOST_AUTO_TEST_SUITE_END()

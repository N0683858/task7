#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "route.h"
#include "track.h"

using namespace GPS;

BOOST_AUTO_TEST_SUITE( Route_TotalLength )

const bool isFileName = true;

// Check if the function can find the total length within the ABCD.gpx
BOOST_AUTO_TEST_CASE( RouteABCD )
{
    Route route = Route(LogFiles::GPXRoutesDir + "ABCD.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.totalLength(), 82.6);
}

// Check if the function can find the total length within the RouteNorthYorkMoors.gpx
BOOST_AUTO_TEST_CASE( RouteNorthYorkMoors )
{
    Route route = Route(LogFiles::GPXRoutesDir + "NorthYorkMoors.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.totalLength(), 56.8113);
}

// Check if the function can find the total length within the RouteLatitudeGreater90.gpx
BOOST_AUTO_TEST_CASE( RouteLatitudeGreater90 )
{
    Route route = Route(LogFiles::GPXRoutesDir + "RouteLatitudeGreater90.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.totalLength(), 142.7);
}

//Check if the function can handle stationary negative points in a route file
BOOST_AUTO_TEST_CASE( RouteStationaryNegativePoints )
{
   Route route = Route(LogFiles::GPXRoutesDir + "RouteStationaryNegativePoints.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.totalLength(), -19.32);
}

//Check if the function can handle stationary negative points in a track file
BOOST_AUTO_TEST_CASE( TrackStationaryNegativePoints )
{
   Track track = Track(LogFiles::GPXTracksDir + "TrackStationaryNegativePoints.gpx", isFileName);
   BOOST_CHECK_EQUAL( track.totalLength(), -41.56);
}


BOOST_AUTO_TEST_SUITE_END()

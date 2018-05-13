#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "route.h"
#include "track.h"

using namespace GPS;

BOOST_AUTO_TEST_SUITE( Route_MinElev )

const bool isFileName = true;

//Test to see if the minElevation function can find the lowest elevation in the ABCD route
//Also shows that function can finf elevation of zero
BOOST_AUTO_TEST_CASE( MinElevationABCD)
{
   Route route = Route(LogFiles::GPXRoutesDir + "ABCD.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.minElevation(), 0.000000 );
}

//Test to see if the minElevation function can find the lowest elevation in the NorthYorkMoors route
BOOST_AUTO_TEST_CASE( MinElevationNorthYorkMoors )
{
   Route route = Route(LogFiles::GPXRoutesDir + "NorthYorkMoors.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.minElevation(), 135 );
}

//Testing function to find lowest elevation when route has only negative elevation
//This test uses AllBelowSeaLevel.gpx which is a three point route through the North Sea
BOOST_AUTO_TEST_CASE( AllBelowSeaLevel )
{
   Route route = Route(LogFiles::GPXRoutesDir + "N0719715-AllBelowSeaLevel.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.minElevation(), -120);
}

//Testing function to find lowest elevation
//When route goes from above sea level to below sea level making elevation negative
//This test uses AboveBelowSeaLevel.gpx which is a three point route from Stoke-on-Trent to the North Sea
BOOST_AUTO_TEST_CASE( AboveBelowSeaLevel )
{
   Route route = Route(LogFiles::GPXRoutesDir + "N0719715-AboveBelowSeaLevel.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.minElevation(), -120);
}

//Testing function to find lowest elevation in the one of the deepest parts of the ocean testing extreme data
BOOST_AUTO_TEST_CASE( DeepestElev )
{
   Route route = Route(LogFiles::GPXRoutesDir + "N0719715-DeepestElev.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.minElevation(), -13000 );
}

//Testing function to find lowest elevation in the one of the highest parts of the Earth testing extreme data
BOOST_AUTO_TEST_CASE( LargeElev )
{
   Route route = Route(LogFiles::GPXRoutesDir + "N0719715-LargeElev.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.minElevation(), 8458);
}

//Testing function to find lowest elevation when there is only one position in the log
BOOST_AUTO_TEST_CASE( OnePositionElev )
{
   Route route = Route(LogFiles::GPXRoutesDir + "N0719715-OnePosition.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.minElevation(), 120);
}

//Testing function to find lowest elevation when there is a very small change in elevation
BOOST_AUTO_TEST_CASE( SmallChangeElev )
{
   Route route = Route(LogFiles::GPXRoutesDir + "N0719715-SmallChange.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.minElevation(), 119.999998);
}

//Testing function to find lowest elevation when there is a very large change in elevation
BOOST_AUTO_TEST_CASE( LargeChangeElev )
{
   Route route = Route(LogFiles::GPXRoutesDir + "N0719715-LargeChange.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.minElevation(), -7000);
}


//Testing function to find lowest elevation when there is a very no change in elevation
BOOST_AUTO_TEST_CASE( NoChangeElev )
{
   Route route = Route(LogFiles::GPXRoutesDir + "N0719715-NoChange.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.minElevation(), 120);
}




BOOST_AUTO_TEST_SUITE_END()

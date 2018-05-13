#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "route.h"
#include "track.h"

using namespace GPS;

BOOST_AUTO_TEST_SUITE( Route_minLongitude )

const bool isFileName = true;


// The function i have chose is Route::minLongitude(). The function should find the minimum longitude in the points in a gpx files.
// The test cases will consist of finding the longitude on a positve and negative stationary points where both longitude and latitude points are static
// and doesnt not change. Then the gpx will be a horizontal and vertical line where either the longitude or latitude will not change and we will see
// if the function will still run and return the minimum longitude. There will be another test to see if the function can return the minimum longitude
// where the points will be unsorted and finally, there will a test case to see if it can detect small minuscule changes in the millionth and bigger numbers.
// These tests will ensure that the function is functionable and that can find the minimum longitude without having to worry about the order or the points,
// repeated points and with little or large changes.

// RouteStationaryPoints has 5 points all stationary and positive
// This test case is to find out if it can still return the minimum longitude

BOOST_AUTO_TEST_CASE( CheckPostiveStationaryPoints )
{
        Route route = Route(Logfiles::GPXRoutesDir + "RouteStationaryPoints.gpx", isFileName);
        BOOST_CHECK_EQUAL( route.minLongitude(), -1.45248);
}

// RouteStationaryNegativePoints has 5 points all stationary and negative
// This will find out if the test can still return the minimum longitude even when its negative

BOOST_AUTO_TEST_CASE( CheckNegativeStationaryPoints )
{
        Route route = Route(Logfiles::GPXRoutesDir + "RouteStationaryNegativePoints.gpx", isFileName);
        BOOST_CHECK_EQUAL( route.minLongitude(), -0.207456);
}

// In CliftonStraightVerticalLine gpx file, the points are going vertical therefore, the longitude
// should be the same throughout the points

BOOST_AUTO_TEST_CASE( CheckLongitudeVerticalLine )
{
        Route route = Route(Logfiles::GPXRoutesDir + "CliftonStraightVerticalLine.gpx", isFileName);
        BOOST_CHECK_EQUAL( route.minLongitude(), -1.19);
}

// In CliftonStraightLineIncreasingLong gpx file, the latitude points are static and only the longitude
// has changed.

BOOST_AUTO_TEST_CASE( CheckLongitudeVerticalLine )
{
        Route route = Route(Logfiles::GPXRoutesDir + "CliftonStraightLineIncreasingLong.gpx", isFileName);
        BOOST_CHECK_EQUAL( route.minLongitude(), -1.19);
}

// In RouteChangingLongitude gpx file, the points are going horizontal and the longitude
// are all negative, the test case should return the minimum longitude

BOOST_AUTO_TEST_CASE( CheckLongitudeHorizontalLine )
{
        Route route = Route(Logfiles::GPXRoutesDir + "RouteChangingLongitude.gpx", isFileName);
        BOOST_CHECK_EQUAL( route.minLongitude(), -1.45248);
}

// In Route_Different_Longitudes_Log gpx file, the longitude points are not in order, the test
// should return the minimum longitude if the function is working as intended
BOOST_AUTO_TEST_CASE( CheckLongitudeUnsorted )
{
        Route route = Route(Logfiles::GPXRoutesDir + "Route_Different_Longitudes_Log.gpx", isFileName);
        BOOST_CHECK_EQUAL( route.minLongitude(), 7.12765439876543);
}

// The gpx has the longitude change by 50 each time
// This test is to try and find out if it can still return the minimum longitude.

BOOST_AUTO_TEST_CASE( CheckLongitudeWithBigChange)
{
        Route route = Route(Logfiles::GPXRoutesDir + "LongitudeChangeOf50.gpx", isFileName);
        BOOST_CHECK_EQUAL( route.minLongitude(), 1);
}

// The gpx has the longitude change by 0.0000001 each time
// This test is to try and find out if it can still return the minimum longitude even with a minuscule change.

BOOST_AUTO_TEST_CASE( CheckLongitudeWithMinusculeChange)
{
        Route route = Route(Logfiles::GPXRoutesDir + "LongitudeChangeOf0000001.gpx", isFileName);
        BOOST_CHECK_EQUAL( route.minLongitude(), 1.0000000);
}

BOOST_AUTO_TEST_SUITE_END()

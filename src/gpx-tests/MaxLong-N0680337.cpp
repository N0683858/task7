//N0680337
#include <boost/test/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>

#include "logs.h"
#include "route.h"
#include "track.h"

using namespace GPS;

BOOST_AUTO_TEST_SUITE( Route_maxLongitude )

const bool isFileName = true;
// More test details in DesignOfUnitTests.pdf
// Used boost check close to allow a tolerance when using floating points
// Test increasing longitude values to identify that max longitude works
BOOST_AUTO_TEST_CASE( MaxLongHorizontalLine )
{
   Route route = Route(LogFiles::GPXRoutesDir + "IncreaseInLongitude-N0680337.gpx", isFileName);
   BOOST_CHECK_CLOSE( route.maxLongitude(), 51.3975, 0.1);
}


// Test if very small changes are detected
BOOST_AUTO_TEST_CASE( VerySmallChange )
{
   Route route = Route(LogFiles::GPXRoutesDir + "VerySmallChange-N0680337.gpx", isFileName);
   BOOST_CHECK_CLOSE( route.maxLongitude(), 10.0000002, 0.0000001 );
}


// Test that the function works with only one longitude value
BOOST_AUTO_TEST_CASE( MaxLongVerticalLine )
{
   Route route = Route(LogFiles::GPXRoutesDir + "ConstantLongitude-N0680337.gpx", isFileName);
   BOOST_CHECK_CLOSE( route.maxLongitude(), -50, 0.1);
}


// Test a constant value with the maximum possible longitude
BOOST_AUTO_TEST_CASE( MaxPossibleConstantLongitude )
{
   Route route = Route(LogFiles::GPXRoutesDir + "MaxPossibleConstantLongitude-N0680337.gpx", isFileName);
   BOOST_CHECK_CLOSE( route.maxLongitude(), 180, 0.1);
}


// Test the function against negative values only (A, G, F gridworld points)

BOOST_AUTO_TEST_CASE( NegativeMaxLongHorizontalLine )
{
   Route route = Route(LogFiles::GPXRoutesDir + "NegativeMaxLong-N0680337.gpx", isFileName);
   BOOST_CHECK_CLOSE( route.maxLongitude(), -51.3975, 0.01);
}


// Test the function works with the Prime Meridian as the max longitude (0 longitude, C, H, M gridworld points)

BOOST_AUTO_TEST_CASE( PrimeMeridianVerticalLine )
{
   Route route = Route(LogFiles::GPXRoutesDir + "PrimeMeridianVerticalLine-N0680337.gpx", isFileName);
   BOOST_CHECK_CLOSE( route.maxLongitude(), 0, 0.1);
}


// Test the function against negative values, 0, and positive values to find the max longitude
BOOST_AUTO_TEST_CASE( NegativeToPositiveLong )
{
   Route route = Route(LogFiles::GPXRoutesDir + "ThroughPrimeMeridian-N0680337.gpx", isFileName);
   BOOST_CHECK_CLOSE( route.maxLongitude(), 27.9505, 0.1);
}


// Test the maximum positive longitude to the maximum negative longitude
BOOST_AUTO_TEST_CASE( MaxPositiveToMaxNegativeLong )
{
   Route route = Route(LogFiles::GPXRoutesDir + "MaxPositiveToMaxNegative-N0680337.gpx", isFileName);
   BOOST_CHECK_CLOSE( route.maxLongitude(), 180, 0.1);
}


BOOST_AUTO_TEST_SUITE_END()

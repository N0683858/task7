#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "route.h"

using namespace GPS;

/*
The following test suite was designed to test the function route::maxElevation to ensure it works as intended.
*/

BOOST_AUTO_TEST_SUITE( maxElevation_N0703481)

const bool isFileName = true;

/*
A test where the route starts at a positive postion and ends up at a negative position.
The test was designed to ensure that the maxElevation function can deal with routes which have positive and negative elevations and
still return the correct value.
The function should return the maxElevation of 70.
*/
BOOST_AUTO_TEST_CASE( PositiveToNegativeElevation )
{
   Route route = Route(LogFiles::GPXRoutesDir + "n0703481_pos_to_neg_ele.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.maxElevation(), 70 );
}

/*
A test where the route starts at a negative postion and ends up at a positive position.
The test was designed to ensure that the maxElevation function can deal with routes which have negative and positive elevations and
still return the correct value.
The function should return the maxElevation of 200.
*/
BOOST_AUTO_TEST_CASE( NegativeToPositiveElevation )
{
   Route route = Route(LogFiles::GPXRoutesDir + "n0703481_neg_to_pos_ele.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.maxElevation(), 200 );
}

/*
A test where the route starts at a negative postion then goes to a positive position and then ends up back at a negative position.
The test was designed to ensure that the maxElevation function can deal with routes which have negative and positive elevations and
still return the correct value.
The function should return the maxElevation of 30.
*/
BOOST_AUTO_TEST_CASE( NegativeToPositiveToNegativeElevation )
{
   Route route = Route(LogFiles::GPXRoutesDir + "n0703481_neg_to_pos_to_neg_ele.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.maxElevation(), 30 );
}

/*
A test where the route starts at a positive postion then goes to a negative position and then ends up back at a positive position.
The test was designed to ensure that the maxElevation function can deal with routes which have positive and negative elevations and
still return the correct value.
The function should return the maxElevation of 50.
*/
BOOST_AUTO_TEST_CASE( PositiveToNegativeToPositiveElevation )
{
   Route route = Route(LogFiles::GPXRoutesDir + "n0703481_pos_to_neg_to_pos_ele.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.maxElevation(), 50 );
}

/*
A test where the route only contains one position.
The test was designed to ensure that the maxElevation function can deal with routes where there is only one position and still return the correct value.
The function should return the maxElevation of -120.
*/
BOOST_AUTO_TEST_CASE( OnePosition )
{
   Route route = Route(LogFiles::GPXRoutesDir + "n0703481_one_pos.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.maxElevation(), -120 );
}

/*
A test where the route where all positions have the same elevation.
The test was designed to ensure that the maxElevation function can deal with routes where there are multiple versions of the same value and
still return the correct value.
The function should return the maxElevation of 80.
*/
BOOST_AUTO_TEST_CASE( SameElevation )
{
   Route route = Route(LogFiles::GPXRoutesDir + "n0703481_same_ele.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.maxElevation(), 80 );
}

/*
A test where the route starts at a negative postion and then declines to an even smaller negative position.
The test was designed to ensure that the maxElevation function can deal with routes which have only negative elevations and still return the correct value.
The function should return the maxElevation of -10.
*/
BOOST_AUTO_TEST_CASE( DecreasingNegativeElevation )
{
   Route route = Route(LogFiles::GPXRoutesDir + "n0703481_descreasing_neg_ele.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.maxElevation(), -10 );
}

/*
A test where the route contains a lot of positions.
The test was designed to ensure that the maxElevation function can deal with routes where there are many position and still return the correct value.
The function should return the maxElevation of 5.
*/ 
BOOST_AUTO_TEST_CASE( LargeRouteFile )
{
   Route route = Route(LogFiles::GPXRoutesDir + "n0703481_large_route.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.maxElevation(), 5 );
}

/*
A test where the route position's elevations increment in very small amounts each time.
The test was designed to ensure that the maxElevation function can deal with routes which have positions containing very similar elevations and still return the correct value.
The function should return a maxElevation that is very close to 5.
*/
BOOST_AUTO_TEST_CASE( SmallIncrementationFile )
{
   Route route = Route(LogFiles::GPXRoutesDir + "n0703481_small_incrementation.gpx", isFileName);
   BOOST_CHECK_CLOSE( route.maxElevation(), 5 , 0.02);
}

/*
A test where the route position's elevations increment in very large amounts each time.
The test was designed to ensure that the maxElevation function can deal with routes which have positions containing very different elevations and still return the correct value.
The function should return the maxElevation of 1900.
*/
BOOST_AUTO_TEST_CASE( LargeIncrementationFile )
{
   Route route = Route(LogFiles::GPXRoutesDir + "n0703481_large_incrementation.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.maxElevation(), 1900 );
}

BOOST_AUTO_TEST_SUITE_END()

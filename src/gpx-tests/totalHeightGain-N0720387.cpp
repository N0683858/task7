#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "route.h"

using namespace GPS;

/*
Test suite to check function route::totalHeightGain function correctly,
documentation can be found in the form of comments above each test case.
*/
BOOST_AUTO_TEST_SUITE( Route_totalHeightGain_N0720387 )

const bool isFileName = true;

/*
Test case checks that an incline with all negative values is calculated correctly,
testing that subtraction is done properly with all negative values.
*/
BOOST_AUTO_TEST_CASE( inclineBelowSea )
{
   Route route = Route(LogFiles::GPXRoutesDir + "N0720387-inclineBelowSeaLevel.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.totalHeightGain(), 100 );
}

/*
Test case checks that an incline across the sea level boundary (negative
elevation to positive) is calculated correctly testing that subtraction
is done properly with changing signs.
*/
BOOST_AUTO_TEST_CASE( inclineAcrossSea )
{
   Route route = Route(LogFiles::GPXRoutesDir + "N0720387-inclineAcrossSeaLevel.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.totalHeightGain(), 100 );
}

/*
Test case checks that a decline across the sea level boundary (positive
elevation to negative) is calculated correctly testing that subtraction
is done properly with changing signs and that declining height differences
do not register as height increases.
*/
BOOST_AUTO_TEST_CASE( declineAcrossSea )
{
   Route route = Route(LogFiles::GPXRoutesDir + "N0720387-declineAcrossSeaLevel.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.totalHeightGain(), 0 );
}

/*
Test case checks that a decline followed by an incline only counts the
positive elevation increases and though net elevation is 0, total increase
is above 0.
*/
BOOST_AUTO_TEST_CASE( declineIncline )
{
   Route route = Route(LogFiles::GPXRoutesDir + "N0720387-declineIncline.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.totalHeightGain(), 100 );
}

/*
Test case checks that an incline followed by a decline counts the positive
elevation changes and the negatives that follow are ignored and do not effect
the total height gain.
*/
BOOST_AUTO_TEST_CASE( inclineDecline )
{
   Route route = Route(LogFiles::GPXRoutesDir + "N0720387-inclineDecline.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.totalHeightGain(), 100 );
}

/*
Test case checks that lots of big inclines and declines following eachother, going over
and under the sea level is correctly calculated.
*/
BOOST_AUTO_TEST_CASE( changesLotsAcrossSea )
{
   Route route = Route(LogFiles::GPXRoutesDir + "N0720387-changesAcrossSeaLevel.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.totalHeightGain(), 60000 );
}

/*
Test case checks that a log file with one position functions correctly and does not attempt
to access a second element of the vector, causing memory access violation. The route with
one point does not gain height and thus total height gained should be 0.
*/
BOOST_AUTO_TEST_CASE( onePosition )
{
   Route route = Route(LogFiles::GPXRoutesDir + "N0720387-onePosition.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.totalHeightGain(), 0 );
}

/*
Test case checks that a log file with huge increases in elevation are stored correctly,
although this may be an unrealistic log file, it assures that long routes can store
their total effectively.
*/
BOOST_AUTO_TEST_CASE( largeIncrease )
{
   Route route = Route(LogFiles::GPXRoutesDir + "N0720387-largeIncrease.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.totalHeightGain(), 26000000000 );
}

/*
Test case checks that a log file with tiny increases in elevation are correctly picked up
and tracked, although this may be too precise of a precision compared to a real life
instrument that creates GPX log files, this test proves that the function can handle tiny
increases and is not limited by data types.
*/
BOOST_AUTO_TEST_CASE( smallIncrease )
{
   Route route = Route(LogFiles::GPXRoutesDir + "N0720387-smallIncrease.gpx", isFileName);
   BOOST_CHECK_CLOSE( route.totalHeightGain(), 0.00026, 0.0000000001 );
}

BOOST_AUTO_TEST_SUITE_END()


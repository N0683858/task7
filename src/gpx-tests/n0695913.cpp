#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "route.h"
#include "track.h"

using namespace GPS;

BOOST_AUTO_TEST_SUITE( n0695913_num_positions )

const bool numCorrect = true;

/*
 * Check that the number of positions is correct for a route
 * where the granularity has not been specified
 */
BOOST_AUTO_TEST_CASE( correct_num_positions_route )
{
   Route route = Route(LogFiles::GPXRoutesDir + "ABCD.gpx", numCorrect);
   BOOST_CHECK_EQUAL( route.numPositions(), 4 );
}

/*
 * Check that the number of positions is correct for a track
 * where the granularity has not been specified
 */
BOOST_AUTO_TEST_CASE( correct_num_positions_track )
{
   Track track = Track(LogFiles::GPXTracksDir + "A1B.gpx", numCorrect);
   BOOST_CHECK_EQUAL( track.numPositions(), 11 );
}

/*
 * Check that the number of positions is correct for a route
 * with only one position, and no granularity specified
 */
BOOST_AUTO_TEST_CASE( correct_num_positions_route_oneposition )
{
   Route route = Route(LogFiles::GPXRoutesDir + "n0695913_oneposition.gpx", numCorrect);
   BOOST_CHECK_EQUAL( route.numPositions(), 1 );
}

/*
 * Check that the number of positions is correct for a route
 * with a granularity of 10 metres
 */
BOOST_AUTO_TEST_CASE( correct_num_positions_route_granularity10m )
{
   Route route = Route(LogFiles::GPXRoutesDir + "n0695913_granularityall.gpx", numCorrect, 10);
   BOOST_CHECK_EQUAL( route.numPositions(), 9 );
}

/*
 * Check that the number of positions is correct for a route
 * with a granularity of 20 metres
 */
BOOST_AUTO_TEST_CASE( correct_num_positions_route_granularity20m )
{
   Route route = Route(LogFiles::GPXRoutesDir + "n0695913_granularityall.gpx", numCorrect, 20);
   BOOST_CHECK_EQUAL( route.numPositions(), 9 );
}

/*
 * Check that the number of positions is correct for a route
 * with a granularity of 50 metres
 */
BOOST_AUTO_TEST_CASE( correct_num_positions_route_granularity50m )
{
   Route route = Route(LogFiles::GPXRoutesDir + "n0695913_granularityall.gpx", numCorrect, 50);
   BOOST_CHECK_EQUAL( route.numPositions(), 7 );
}

/*
 * Check that the number of positions is correct for a route
 * with a granularity of 100 metres
 */
BOOST_AUTO_TEST_CASE( correct_num_positions_route_granularity100m )
{
   Route route = Route(LogFiles::GPXRoutesDir + "n0695913_granularityall.gpx", numCorrect, 100);
   BOOST_CHECK_EQUAL( route.numPositions(), 6 );
}

/*
 * Check that the number of positions is correct for a route
 * with a granularity of 200 metres
 */
BOOST_AUTO_TEST_CASE( correct_num_positions_route_granularity200m )
{
   Route route = Route(LogFiles::GPXRoutesDir + "n0695913_granularityall.gpx", numCorrect, 200);
   BOOST_CHECK_EQUAL( route.numPositions(), 4 );
}

BOOST_AUTO_TEST_SUITE_END()

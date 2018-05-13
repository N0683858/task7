#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "route.h"
#include "track.h"

using namespace GPS;

/**
 * The GPX log files have been generated in a way that the maximum elevation in
 * all of them is 58.000000 meters.
 *
 * GPX log files of the following routes have been created:
 * - Constant elevation (does not change).
 * - Decreasing elevation (elevation decreases linearly).
 * - Increasing elevation (elevation increases linearly).
 * - Valley (elevation decreases then increases).
 * - Hill (elevation increases then decreases).
 * - Decreasing elevation through zero (elevation decreases linearly and crosses zero).
 */

BOOST_AUTO_TEST_SUITE( Route_maxElevation )

// Check that the correct maximum elevation is calculated when using the "constant" log file.
BOOST_AUTO_TEST_CASE( constant_log )
{
   Route route = Route(LogFiles::GPXRoutesDir + "maxElevation_constant_n0686300.gpx", true);
   BOOST_CHECK_EQUAL( route.maxElevation(), 58.000000 );
}

// Check that the correct maximum elevation is calculated when using the "decreasing" log file.
BOOST_AUTO_TEST_CASE( decreasing_log )
{
   Route route = Route(LogFiles::GPXRoutesDir + "maxElevation_decreasing_n0686300.gpx", true);
   BOOST_CHECK_EQUAL( route.maxElevation(), 58.000000 );
}

// Check that the correct maximum elevation is calculated when using the "increasing" log file.
BOOST_AUTO_TEST_CASE( increasing_log )
{
   Route route = Route(LogFiles::GPXRoutesDir + "maxElevation_increasing_n0686300.gpx", true);
   BOOST_CHECK_EQUAL( route.maxElevation(), 58.000000 );
}

// Check that the correct maximum elevation is calculated when using the "vshape" log file.
BOOST_AUTO_TEST_CASE( vshape_log )
{
   Route route = Route(LogFiles::GPXRoutesDir + "maxElevation_vshape_n0686300.gpx", true);
   BOOST_CHECK_EQUAL( route.maxElevation(), 58.000000 );
}

// Check that the correct maximum elevation is calculated when using the "nshape" log file.
BOOST_AUTO_TEST_CASE( nshape_log )
{
   Route route = Route(LogFiles::GPXRoutesDir + "maxElevation_nshape_n0686300.gpx", true);
   BOOST_CHECK_EQUAL( route.maxElevation(), 58.000000 );
}

// Check that the correct maximum elevation is calculated when using the "decreasingnegative" log file.
BOOST_AUTO_TEST_CASE( decreasingnegative_log )
{
   Route route = Route(LogFiles::GPXRoutesDir + "maxElevation_decreasingnegative_n0686300.gpx", true);
   BOOST_CHECK_EQUAL( route.maxElevation(), 58.000000 );
}

BOOST_AUTO_TEST_SUITE_END()

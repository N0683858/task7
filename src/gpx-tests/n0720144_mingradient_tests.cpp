/* Name: Minimum Gradient Tests
 * Number: N0720144 (James Doyle)
 */

// Includes:
#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "route.h"
#include "track.h"

// Using:
using namespace GPS;

BOOST_AUTO_TEST_SUITE( Route_minGradient_N0720144 )

const bool isFileName = true;

/* Test 1: Tests if function outputs the largest negative gradient in a set of points
 * that gives multiple negative gradient differences
 */

BOOST_AUTO_TEST_CASE( LargestNegativeGradient )
{
    Route route = Route(LogFiles::GPXRoutesDir + "LargestNegativeGradient.gpx",isFileName);
    BOOST_CHECK_CLOSE(route.minGradient(),-220513.18751,1);
}

/* Test 2: Tests if it throws the exception std::invalid_argument when there is a single point
 * in the track
 */

BOOST_AUTO_TEST_CASE( Invalid_Amount_of_Points )
{
    BOOST_CHECK_THROW(Route route = Route(LogFiles::GPXRoutesDir + "Invalid_Amount_of_Points.gpx",isFileName),std::invalid_argument);
}

/* Test 3: Tests if the elevations are zero it outputs a minimum gradient of 0
 */

BOOST_AUTO_TEST_CASE( Elevations_Eqaul_to_Zero )
{
    Route route = Route(LogFiles::GPXRoutesDir + "Elevations_Equal_to_Zero.gpx", isFileName);
    BOOST_CHECK_EQUAL(route.minGradient(),0);
}

/* Test 4: Tests if the gradient is outputted if all the latitudes of the points within the track
 * the same
 */

BOOST_AUTO_TEST_CASE( No_Change_Latitude )
{
    Route route = Route(LogFiles::GPXRoutesDir + "No_Change_Latitude.gpx",isFileName);
    BOOST_CHECK_CLOSE(route.minGradient(),235274.33443,1);
}

/* Test 4: Tests if the gradient is outputted if all the longitudes of the points within the track
 * the same
 */

BOOST_AUTO_TEST_CASE( No_Change_Longitude )
{
    Route route = Route(LogFiles::GPXRoutesDir + "No_Change_Longitude.gpx",isFileName);
    BOOST_CHECK_CLOSE(route.minGradient(),235274.33443,1);
}

BOOST_AUTO_TEST_SUITE_END()

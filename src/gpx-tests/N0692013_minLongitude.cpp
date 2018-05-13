#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "route.h"
#include "track.h"

//see Test Suite Designs for information on the functions

using namespace GPS;

BOOST_AUTO_TEST_SUITE( N0692013_routeMinLongitude )

const bool isFileName = true;

BOOST_AUTO_TEST_CASE( checkCorrectHorizontal )
{
   Route route = Route(LogFiles::GPXRoutesDir + "N0692013_correctHorizontalRoute.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.minLongitude(), 49.7205);
}

BOOST_AUTO_TEST_CASE( checkCorrectVertical )
{
   Route route = Route(LogFiles::GPXRoutesDir + "N0692013_correctVertical.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.minLongitude(), 25);
}

BOOST_AUTO_TEST_CASE( checkCorrectUnordered )
{
   Route route = Route(LogFiles::GPXRoutesDir + "N0692013_correctUnorderedRoute.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.minLongitude(), 49.8602);
}

BOOST_AUTO_TEST_CASE( checkCorrectNegatives )
{
   Route route = Route(LogFiles::GPXRoutesDir + "N0692013_correctNegatives.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.minLongitude(), -10.0091);
}

BOOST_AUTO_TEST_CASE( checkCorrectBoundary )
{
   Route route = Route(LogFiles::GPXRoutesDir + "N0692013_correctBoundary.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.minLongitude(), 179.102);
}

BOOST_AUTO_TEST_CASE( checkCorrectDiffAs0 )
{
   Route route = Route(LogFiles::GPXRoutesDir + "N0692013_correctDiffAs0.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.minLongitude(), 0);
}

BOOST_AUTO_TEST_SUITE_END()
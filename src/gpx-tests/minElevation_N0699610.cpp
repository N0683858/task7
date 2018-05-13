#include <boost/test/unit_test.hpp>
#include <stdexcept>
#include "logs.h"
#include "route.h"

using namespace GPS;

BOOST_AUTO_TEST_SUITE( minElevation_N0699610 )
/*Tests:
-Correct: tests that the correct value is returned
-Edge: tests that the correct value is returned on edge cases
-Incorrect: tests that the function acts as expected given unusual data
*/
const bool isFileName = true;
//------------------------------------------------------------------------------------------------------------------------------------------------------//
//CORRECT
//Positive values tests - tests for when the minimum elevation or the difference in elevation is positive:
//1.
//Test that the correct minimum elevation is returned
BOOST_AUTO_TEST_CASE( correctMinElevation )
{
   Route route = Route(LogFiles::GPXRoutesDir + "NorthYorkMoors.gpx",isFileName);//get log file as route
   BOOST_CHECK_EQUAL( route.minElevation(), 135);
}
//2.
//check for correct value when elevation intervals are set to 10
BOOST_AUTO_TEST_CASE( correctMinElevation10Interval )
{
   Route route = Route(LogFiles::GPXRoutesDir + "vertical10.gpx",isFileName);//get log file as route
   BOOST_CHECK_EQUAL( route.minElevation(), 33);
}
//3.
//Test that the correct minimum elevation is returned when first and last elevations are lowest
BOOST_AUTO_TEST_CASE( correctMinElevationFirstAndLast )
{
   Route route = Route(LogFiles::GPXRoutesDir + "increasingThenDecreasingElevation.gpx",isFileName);//get log file as route
   BOOST_CHECK_EQUAL( route.minElevation(), 42);

}
//4.
//Test that the correct minimum elevation is returned when no value for change in elevation is set, should default to zero change.
BOOST_AUTO_TEST_CASE( correctMinElevationNoChange )
{
   Route route = Route(LogFiles::GPXRoutesDir + "noChangeInElevation.gpx",isFileName);//get log file as route
   BOOST_CHECK_EQUAL( route.minElevation(), 58);

}
//5.
//Test that the correct minimum elevation is returned when the minimum elevation is the first value
BOOST_AUTO_TEST_CASE( correctMinimumFirstValue )
{
   Route route = Route(LogFiles::GPXRoutesDir + "minElevationFirstValue.gpx",isFileName);//get log file as route
   BOOST_CHECK_EQUAL( route.minElevation(), 52);

}
//6.
//Test that the correct minimum elevation is returned when the minimum elevation is the final value
BOOST_AUTO_TEST_CASE( correctMinimumFinalValue )
{
   Route route = Route(LogFiles::GPXRoutesDir + "minElevationFinalValue.gpx",isFileName);//get log file as route
   BOOST_CHECK_EQUAL( route.minElevation(), 48);

}
//7.
//Floating point test - tests for when the minimum elevation and the difference in elevation is a floating point:
//Test that the correct minimum elevation is returned when vertical difference is a real number (decimal)
BOOST_AUTO_TEST_CASE( correctDecimal )
{
   Route route = Route(LogFiles::GPXRoutesDir + "floatingPoint.gpx",isFileName);//get log file as route
   BOOST_CHECK_CLOSE( route.minElevation(), 39.5,1);

}
//8.
//Negative values tests - tests for when the minimum elevation or the difference in elevation is negative:
//Check for correct value when elevation difference (interval) is negative
BOOST_AUTO_TEST_CASE( correctNegativeInterval )
{
   Route route = Route(LogFiles::GPXRoutesDir + "negativeInterval5Metres.gpx",isFileName);//get log file as route
   BOOST_CHECK_EQUAL( route.minElevation(), 53);
}
//9.
//Elevation may be below sea level so this tests that the function can handle negative elevations
BOOST_AUTO_TEST_CASE( correctNegativeMinElevation )
{
   Route route = Route(LogFiles::GPXRoutesDir + "negativeElevation.gpx",isFileName);
   BOOST_CHECK_EQUAL( route.minElevation(), -6 );
}
//Large values test - tests for when the minimum elevation and the difference in elevation is large:
//10.
//Test that the correct minimum elevation is returned for large elevations (ie mountains)
BOOST_AUTO_TEST_CASE( correctLargeElevations )
{
   Route route = Route(LogFiles::GPXRoutesDir + "Rockies.gpx",isFileName);//get log file as route
   BOOST_CHECK_EQUAL( route.minElevation(), 4201);
}
//------------------------------------------------------------------------------------------------------------------------------------------------------//
//EDGE
//Very large values test - tests that when the minimum elevation and the difference in elevation are very large:
//11.
//Test that the correct minimum elevation is returned for very large elevations - starting position is the summit of Mount Everest, so there is no larger elevation on Earth
BOOST_AUTO_TEST_CASE( veryLargeElevations )
{
   Route route = Route(LogFiles::GPXRoutesDir + "Everest.gpx",isFileName);//get log file as route
   BOOST_CHECK_EQUAL( route.minElevation(), 6848);
}
//Zero tests - tests that when the minimum elevation is zero, or very close to zero:
//12.
//Ensure minElevation takes very low values
//minimum elevation may be zero, ensure this is found
BOOST_AUTO_TEST_CASE( edgeElevationZero )
{
   Route route = Route(LogFiles::GPXRoutesDir + "AHM.gpx",isFileName);
   BOOST_CHECK_EQUAL( route.minElevation(), 0);
}
//13.
//Test that correct min elevation is found when min elevation is very small
BOOST_AUTO_TEST_CASE( edgeSmallElevation )
{
   Route route = Route(LogFiles::GPXRoutesDir + "verySmallElevation.gpx",isFileName);
   BOOST_CHECK_CLOSE( route.minElevation(), 0.000001, 0.001 );

}
//13.
//Test that correct min elevation is found when min elevation is a very small negative number
BOOST_AUTO_TEST_CASE( edgeSmallNegativeElevation )
{
   Route route = Route(LogFiles::GPXRoutesDir + "verySmalNegativelElevation.gpx",isFileName);
   BOOST_CHECK_CLOSE( route.minElevation(), -0.000001,0.001 );

}
//------------------------------------------------------------------------------------------------------------------------------------------------------//
//INCORRECT
//Missing elevations test - tests that when some, or all, elevations are missing:
//14.
//Tests that when some elevation values are missing an invalid_argument exception is thrown
BOOST_AUTO_TEST_CASE( missingSomeElevations )
{
   Route route = Route(LogFiles::GPXRoutesDir + "missingElevations.gpx", isFileName);
   BOOST_CHECK_THROW( route.minGradient(), std::invalid_argument );
}

//15.
//Tests that when no elevation values are present then an invalid_argument exception is thrown
BOOST_AUTO_TEST_CASE( noElevation )
{
   Route route = Route(LogFiles::GPXRoutesDir + "noElevation.gpx", isFileName);
   BOOST_CHECK_THROW( route.minGradient(), std::invalid_argument );
}
//16.
//Tests that when the elevation values are invalid (ie letters rather than numbers) an invalid_argument exception is thrown
BOOST_AUTO_TEST_CASE( invalidElevation )
{
   Route route = Route(LogFiles::GPXRoutesDir + "invalidElevation.gpx", isFileName);
   BOOST_CHECK_THROW( route.minElevation(), std::invalid_argument );
}

BOOST_AUTO_TEST_SUITE_END()

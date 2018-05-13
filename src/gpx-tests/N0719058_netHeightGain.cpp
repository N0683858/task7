//Joseph Lavagna - NO719058
#include <boost/test/unit_test.hpp>
#include "logs.h"
#include "route.h"
#include "track.h"
#include "position.h"

using namespace GPS;


/*
Documentation

In the following file is a test suite containing numerous tests to check the implementation of the netHeightGain function to make sure all values returned are correct.

*/

BOOST_AUTO_TEST_SUITE (N0719058_netHeightGain)

const bool isFileName = true;

//Test: Zero Net Elevation
//Description: The route that I have specified QLHNR are all on the same plane and so the net elevation should equal 0. All positions on the route have an elevation of 38.
BOOST_AUTO_TEST_CASE( zeroNetElevation )
{
   Route route = Route(LogFiles::GPXRoutesDir + "N0719058_zeroNetElevation.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.totalHeightGain(), 0 );
}


//Test: Positive Net Elevation
//Description: The route that I have specified WRM have three different positions on different planes with elevation values of 8, 38, 68 and so a positive net elevation of 60. 
BOOST_AUTO_TEST_CASE( positiveNetElevation )
{
   Route route = Route(LogFiles::GPXRoutesDir + "N0719058_positiveNetElevation.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.totalHeightGain(), 60 );
}

//Test: Negative Net Elevation
//Description: The route that I have specified MRW have three different positions on different planes with elevations values of 68, 38, 8 and so a negative net elevation of -60. However the implemented function should return 0 if net elevation is negative. 
BOOST_AUTO_TEST_CASE( negativeNetElevation )
{
   Route route = Route(LogFiles::GPXRoutesDir + "N0719058_negativeNetElevation.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.totalHeightGain(), 0 );
}


//Test: Single Elevation
//Description: The route that I have specified for this test, B, is one single location and so has one single elevation value of 8. And so no net elevation value can be returned.  
BOOST_AUTO_TEST_CASE( singleElevation )
{
   Route route = Route(LogFiles::GPXRoutesDir + "N0719058_singleElevation.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.totalHeightGain(), 0 );
}


//Test: Increase Negative Elevation
//Description: The route all has negative values, but is incrementing in value. There fore a positive number should be returned since as the height is increasing.
BOOST_AUTO_TEST_CASE( increaseNegativeElevation )
{
   Route route = Route(LogFiles::GPXRoutesDir + "N0719058_increaseNegativeElevation.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.totalHeightGain(), 60 );
}


//Test: No Elevation
//Description: For this test while generating the GPX log file I set the elevation difference between planes to 0. And so the elevation value for each position shouldn't change regardless of planes. The route that I have specified UQMIE all have elevation values of 68 and so a 0 net elevation. 
BOOST_AUTO_TEST_CASE( noElevation )
{
   Route route = Route(LogFiles::GPXRoutesDir + "N0719058_noElevation.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.totalHeightGain(), 0 );
}


//Test: Increase Decrease Elevation
//Description: The route that I have specified alternates in elevation and reaches the max position. 
BOOST_AUTO_TEST_CASE( increaseDecreaseElevation )
{
   Route route = Route(LogFiles::GPXRoutesDir + "N0719058_increaseDecreaseElevation.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.totalHeightGain(), 60 );
}


BOOST_AUTO_TEST_SUITE_END()

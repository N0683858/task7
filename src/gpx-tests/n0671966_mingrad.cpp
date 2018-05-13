#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "route.h"
#include "track.h"

using namespace GPS;

/* 
Documentation:
For my test file I have chosen to do the Minimum Gradient function.
This function determines which gradient between each position is the lowest, to check that this function works I have created 10 different tests below checking the functions against certain routes I have created. To work out the gradient between two positions you first need to work out the distance between these two points this can be done using Pythagoras. After the angle is worked out using Trigonometry, the chosen angle will depends on if the route is downhill or uphill. My test will check that the function answers are correct and will try and catch out errors. Throughout the tests majority of them are check_close this is because there could be a rounding difference, I have each case to be 1 +/- of the answer I think this is an appropriate amount.

*/

BOOST_AUTO_TEST_SUITE( Route_minGradient )

const bool isFileName = true;

//TEST 1: No Elevation change
// This test checks that the minGradient is correct for ABCD GPX route where there is no change in elevtion therefore no gradient. 
BOOST_AUTO_TEST_CASE( routeABCD )
{
   Route route = Route(LogFiles::GPXRoutesDir + "ABCD.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.minGradient(), 0 );
}

//TEST 2: Constant Downwards Gradient
//This route goes downhill at a constant decrease rate
BOOST_AUTO_TEST_CASE( ConstDownGrad )
{
   Route route = Route(LogFiles::GPXRoutesDir + "ConstDownGrad.gpx", isFileName);
   BOOST_CHECK_CLOSE( route.minGradient(), -84.87, 1 );

}

//TEST 3: Const Upwards Gradient
//The route will go upwards by the same elevation each time
BOOST_AUTO_TEST_CASE( ConstUpGrad )
{
   Route route = Route(LogFiles::GPXRoutesDir + "ConstUpGrad.gpx", isFileName);
   BOOST_CHECK_CLOSE( route.minGradient(), 84.87, 1 );

}

//TEST 4: DiagalnalIncline
//This test will go dialgonlly on the grid testing that the function includes the Pythagorus part of the equation
BOOST_AUTO_TEST_CASE( DiagonalIncline )
{
   Route route = Route(LogFiles::GPXRoutesDir + "DiagonalIncline.gpx", isFileName);
   BOOST_CHECK_CLOSE( route.minGradient(), 82.75, 1 );

}

//TEST 5: DiagalnalDecline
//This test is the same as above however it decreases in elevation at each position
BOOST_AUTO_TEST_CASE( DiagonalDecline )
{
   Route route = Route(LogFiles::GPXRoutesDir + "DiagonalDecline.gpx", isFileName);
   BOOST_CHECK_CLOSE( route.minGradient(), -82.75, 1 );

}


//TEST 6: Only Elevation change = 90/-90
//This test is where the different positions will stay exactly where they are but go higher/lower in altitude ensuring that the function checks if the distance interms of latitude and longatude is equal to 0 beforehand
BOOST_AUTO_TEST_CASE( ElevationChangeOnly )
{
   Route route = Route(LogFiles::GPXRoutesDir + "ElevationChangeOnly.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.minGradient(), 90 );
}


//TEST 7: Unconstant Downward Gradient
//This GPX file has been edited so that the elevation isn't constant. The whole route will be going downwards but at a different rate
BOOST_AUTO_TEST_CASE( UnconstDownGrad )
{
   Route route = Route(LogFiles::GPXRoutesDir + "UnconstantDownGrad.gpx", isFileName);
   BOOST_CHECK_CLOSE( route.minGradient(), -77.34, 1 );

}


//TEST 8: Unconstant Upward Gradient
//This route will go upwards but not at a consistant rate, this elevation will differ
BOOST_AUTO_TEST_CASE( UnconstUpGrad )
{
   Route route = Route(LogFiles::GPXRoutesDir + "UnconstantUpGrad.gpx", isFileName);
   BOOST_CHECK_CLOSE( route.minGradient(), 79.82, 1 );

}

//The following tests checks that invalid arguments have been put inplace
//TEST 9: Invalid Input i.e letter
//This GPX file includes letters instead of numbers, the function should first check the inputted data is the right format
BOOST_AUTO_TEST_CASE( InvalidInput )
{
   Route route = Route(LogFiles::GPXRoutesDir + "InvalidInput.gpx", isFileName);
   BOOST_CHECK_THROW( route.minGradient(), std::invalid_argument );
}


//TEST 10: Nothing In Vector
//For this test I have left some places blank this should throw an exception
BOOST_AUTO_TEST_CASE( NoInput )
{
   Route route = Route(LogFiles::GPXRoutesDir + "NoInput.gpx", isFileName);
   BOOST_CHECK_THROW( route.minGradient(), std::invalid_argument );
}


BOOST_AUTO_TEST_SUITE_END()







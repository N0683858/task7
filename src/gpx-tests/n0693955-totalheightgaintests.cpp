#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "route.h"
#include "track.h"

using namespace GPS;

// Documentation has been done suitably in the form of comments in this file.



/********************************************
* Test Suite for TotalHeightGain - N0693955 *
* *******************************************/

/*
 * The function of this test suite is to test the correctness
 * of the totalHeightGain function which I implemented. It aims to
 * check for typical, atypical, and edge case scenarios for the
 * totalHeightGain function.
*/


/*
 *   STRUCTURE OF THE TEST SUITE
 *
 * Test Case 1 is a general purpose test case that tests the basic functionality.
 *
 * Test Cases 2-3 handle testing for inclination and declination above sea level.
 *
 * Test Cases 4-5 handle testing for inclination and declination below sea level
 *
 * Test Case 6 handles testing for inclination from below sea level to above sea level.
 *
 * Test Case 7 handles testing for declination from above sea level to below sea level.
 *
 * Test Case 8 handles testing for points below sea level that don't follow a continuous inclination.
 *
 * Test Case 9 handles testing for points above sea level that don't follow a continuous declination.
 *
 * Test Case 10 handles a singular point.
 *
*/

BOOST_AUTO_TEST_SUITE( TotalHeightGain_n0693955 )

const bool isFileName = true;



                                    /*************
                                    * TEST CASES *
                                    **************/

/***********************************************************************************/

//TEST CASE 1
/*
 * This test case checks the usual functionality of the function,
 * wherein the function ignores negative height differences and
 * adds the positive height differences
*/

BOOST_AUTO_TEST_CASE( ABBM )
{
    Route route = Route(LogFiles::GPXRoutesDir + "ABBM-n0693955.gpx", isFileName);
    BOOST_CHECK_EQUAL(route.totalHeightGain(), 50);
}

/***********************************************************************************/

//TEST CASE 2
/*
 * This test case checks if the function evaluates the height values
 * correctly when the heights are inclining in succession. Since all the
 * differences in heights will give a positive non-zero value, these
 * differences should be added to the total height gain.
 *
 * Possible Scenario: Going on an inclination from sea level to above sea level.
*/

BOOST_AUTO_TEST_CASE( IncliningHeights1 )
{
    Route route = Route(LogFiles::GPXRoutesDir + "IncliningHeights1-n0693955.gpx", isFileName);
    BOOST_CHECK_EQUAL(route.totalHeightGain(), 200);
}

/***********************************************************************************/

//TEST CASE 3
/*
 * This test case checks if the function evaluates the height values
 * correctly when the heights are declining in succession. Since all the
 * differences in height values would be negative in this scenario,
 * these differences should not be added to the total height gain.
 *
 * Possible Scenario: Going on a declination from above sea level to sea level.
*/

BOOST_AUTO_TEST_CASE( DecliningHeights1 )
{
    Route route = Route(LogFiles::GPXRoutesDir + "DecliningHeights1-n0693955.gpx", isFileName);
    BOOST_CHECK_EQUAL(route.totalHeightGain(), 0);
}

/***********************************************************************************/

//TEST CASE 4
/*
 * This test case checks if the function evaluates the height values
 * correctly when the heights are inclining in succession. Since all the
 * height values here are negative, this test case checks if it evaluates the
 * difference in each case correctly.
 *
 * Possible Scenario: Going on an inclination from below sea level to sea level.
*/

BOOST_AUTO_TEST_CASE( IncliningHeights2 )
{
    Route route = Route(LogFiles::GPXRoutesDir + "IncliningHeights2-n0693955.gpx", isFileName);
    BOOST_CHECK_EQUAL(route.totalHeightGain(), 200);
}

/***********************************************************************************/

//TEST CASE 5
/*
 * This test case checks if the function evaluate the height values
 * correctly when the heights are declining in succession. Since all the values
 * here are negative, this test case checks if it evaluates the difference
 * in each case correctly.
 *
 * Possible Scenario: Going on a declination from sea level to below sea level.
*/

BOOST_AUTO_TEST_CASE( DecliningHeights2 )
{
    Route route = Route(LogFiles::GPXRoutesDir + "DecliningHeights2-n0693955.gpx", isFileName);
    BOOST_CHECK_EQUAL(route.totalHeightGain(), 0);
}

/***********************************************************************************/

//TEST CASE 6
/*
 * This test case checks if the function evaluates the difference in
 * elevations correctly when the height being subtracted is a
 * negative value.
 *
 * Possible Scenario: Going on an inclination from below sea level to above sea level.
*/

BOOST_AUTO_TEST_CASE( STG )
{
    Route route = Route(LogFiles::GPXRoutesDir + "STG-n0693955.gpx", isFileName);
    BOOST_CHECK_EQUAL(route.totalHeightGain(), 200);
}

/***********************************************************************************/

//TEST CASE 7
/*
 * This purpose of this test case is similar to the previous one, however in this case
 * the height being subtracted initially is not a negative elevation value.
 *
 * Possible Scenario: Going on a declination from above sea level to below sea level.
*/

BOOST_AUTO_TEST_CASE( GTS )
{
    Route route = Route(LogFiles::GPXRoutesDir + "GTS-n0693955.gpx", isFileName);
    BOOST_CHECK_EQUAL(route.totalHeightGain(), 0);
}

/***********************************************************************************/

//TEST CASE 8
/*
 * This test case checks if the function evaluates correctly when all the
 * height values present are negative.
 *
 * Possibile Scenario: All points below sea level.
*/

BOOST_AUTO_TEST_CASE( AllNegatives )
{
    Route route = Route(LogFiles::GPXRoutesDir + "AllNegatives-n0693955.gpx", isFileName);
    BOOST_CHECK_EQUAL(route.totalHeightGain(), 50);
}

/***********************************************************************************/

//TEST CASE 9
/*
 * This test case checks if the function evaluates correctly when all the
 * height values present are positive.
 *
 * Possibile Scenario: All points above sea level.
*/

BOOST_AUTO_TEST_CASE( AllPositives )
{
    Route route = Route(LogFiles::GPXRoutesDir + "AllPositives-n0693955.gpx", isFileName);
    BOOST_CHECK_EQUAL(route.totalHeightGain(), 100);
}

/***********************************************************************************/

//TEST CASE 10
/*
 * This test case disregards the data if there is only one point,
 * and therefore, only one height value. The total height gain
 * cannot be calculated if there is only one value available for
 * a subtraction where two values must be present.
 *
 * Possible Scenario: Singular point, regardless of whether it is above, beyond, or
 * at sea level.
 *
 * NOTE: This test case is set up to throw up an invalid argument exception as the gpx file
 * holds just one height value.
*/

BOOST_AUTO_TEST_CASE ( SingleHeight )
{
    Route route = Route(LogFiles::GPXRoutesDir + "SingleHeight-n0693955.gpx", isFileName);
    BOOST_CHECK_THROW(route.totalHeightGain(), std::invalid_argument);
}

/***********************************************************************************/

BOOST_AUTO_TEST_SUITE_END()

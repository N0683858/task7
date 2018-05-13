#include <boost/test/unit_test.hpp>
#include <iostream>
#include "logs.h"
#include "track.h"
#include "types.h"

using namespace GPS;
const bool isFileName = true;

BOOST_AUTO_TEST_SUITE( MaxRateOfDescentTests )

//Correctness logic tests
/* The first set of test cases that should be tested for are the correctness tests. These tests are for making sure that the logic is correct within the function. For example if the function was made up of:

        a + b = c
        return c

 * then with an input of a = 2 and b = 3 there should be an output of 5.
 * In this particular function the point of it is to return the greatest change between two different points in a track, but only for descent.
*/
BOOST_AUTO_TEST_CASE( correctnesstest_zero_elevation )
{
   BOOST_CHECK_EQUAL( Track(LogFiles::GPXTracksDir + "A1B3C.gpx", isFileName).maxRateOfDescent(), 0.0 );
}
/* In these test cases the tracks will only have parts where the elevation changes to be lower at points.
 * The output will be different based on the track and will have to be calculated before testing.
 */
BOOST_AUTO_TEST_CASE( correctnesstests_elevation_down )
{
    BOOST_CHECK_EQUAL( Track(LogFiles::GPXTracksDir + "changingelevationnegative.gpx", isFileName).maxRateOfDescent(), -4.0 );
}
/* In these test cases the tracks will only have parts where the elevation changes to be higher at points.
 * The expected output should be zero.
 */
BOOST_AUTO_TEST_CASE( correctnesstests_elevation_up )
{
    BOOST_CHECK_EQUAL( Track(LogFiles::GPXTracksDir + "changingelevationpositive.gpx", isFileName).maxRateOfDescent(), 0);

}

//Underflow and overflow tests
/* In this test case the track will have an initial value of the largest value double.
 */
BOOST_AUTO_TEST_CASE( largest_value_initial )
{
    BOOST_CHECK_EQUAL( Track(LogFiles::GPXTracksDir + "changingelevationmaxvalueinit.gpx", isFileName).maxRateOfDescent(), -21942);
}
/* In this test case the track will have an initial value of the lowest value double
 */
BOOST_AUTO_TEST_CASE( largest_value_subtract )
{
  BOOST_CHECK_EQUAL(Track(LogFiles::GPXTracksDir + "changingelevationtakeawaymaxvalue.gpx", isFileName).maxRateOfDescent(), -1388);
}

BOOST_AUTO_TEST_CASE( lowest_value_initial )
{
  BOOST_CHECK_EQUAL( Track(LogFiles::GPXTracksDir + "changingelevationlowestvalinit.gpx", isFileName).maxRateOfDescent(), 0);
}
//In this test case the next value will be a very low value double
BOOST_AUTO_TEST_CASE( lowest_value_next )
{
  BOOST_CHECK_EQUAL(Track(LogFiles::GPXTracksDir + "changingelevationlowestvaluenext.gpx", isFileName).maxRateOfDescent(), -23330);
}
//In this test case the first value will be a high value double and the next value will be a low value double
BOOST_AUTO_TEST_CASE( highest_init_value_lowest_next_value )
{
  BOOST_CHECK_EQUAL(Track(LogFiles::GPXTracksDir + "changingelevationhighestvaluetolowest.gpx", isFileName).maxRateOfDescent(), -23330);
}

BOOST_AUTO_TEST_CASE( lowest_value_subtract )
{
  //returns zero
  BOOST_CHECK_EQUAL(Track(LogFiles::GPXTracksDir + "changingelevationlowestvaluetohighest.gpx", isFileName).maxRateOfDescent(), 0);
}

BOOST_AUTO_TEST_SUITE_END()

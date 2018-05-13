/*
 * Created by: Joshua Latham. All of this work is my own.

        ######## N0641701's Route::netLength() Test File ########

netLength calculates the distance between the first and last points on the Route.

All log files used will be generated with the program that I built to generate log files unless stated otherwise.



All tests catagorised, and they are as follows:



### These are normal tests to check that the function is giving the correct output.

Test: CorrectOutput
Decscription:
This test will test the function for the correct
output given a number of points which have a known
distance between the first and last point.

Test: OnePoint
Description: This test will test the function on
how it handles a route with only one point. The expected
output should be 0, as there is no distance to measure.

Test: TwoPoints
Description: This test will test the function on
how it handles a route with just two points with
a distance. The expected output should be the distance
between the two points.

Test: BackToStart
Description: This test will test the function against
a route that loops back to its starting point. Therefore
the 0 is the expected output.

Test: TwoIdenticalPoints
Description: Two points with the same location. This test
should give a distance of 0.

Test: UpAndDown
Description: This test will present points that do not move
latitudinally or longitudinally but in elevation. The
distance expected is 0. I have manually created the log file for this.



### These tests are designed to catch any errors when it comes to handling positive and negative numbers.

Test: PosLatLong
Description: Testing the function against positive
latitudinal and positive longitudinal points which
shouldn't affect the output.

Test: PosLatNegLong
Description: Testing the function against positive
latitudinal data and negative longitudinal data.

Test: NegLatNegLong
Decscription: Testing the function against negative
longitudinal data and negative longitudinal data.

Test: NegLatPosLong
Description: Testing the function against negative
longitudinal data and positive longitudinal data.



### Edge cases

Test: BigNumbers
Description: Testing the function on how well it can handle large numbers.
I've manually created these log files with very large numbers to see how well
they'll be handled.

Test: SmallNumbers
Description Testing against very small numbers to see if the function
can handle them.

Test: BigData
Description: Testing the function against a large number of points to see if it will handle it.

*/

#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "route.h"
#include "track.h"

using namespace GPS;

BOOST_AUTO_TEST_SUITE( NetLength )

const bool isFileName = true;

//Correct output test. The usual data to expect.
BOOST_AUTO_TEST_CASE(CorrectOutput)
{
    Route route = Route(LogFiles::GPXRoutesDir + "CorrectOutput_N0641701_MHCBA.gpx", isFileName);
    BOOST_CHECK_CLOSE(route.netLength(), 2827.47, 0.01);
}
//One point. Testing just one point on its own.
BOOST_AUTO_TEST_CASE(OnePoint)
{
    Route route = Route(LogFiles::GPXRoutesDir + "OnePoint_N0641701_M.gpx", isFileName);
    BOOST_CHECK_EQUAL(route.netLength(), 0);
}
//Two Points. Testing two points with different locations.
BOOST_AUTO_TEST_CASE(TwoPoints)
{
    Route route = Route(LogFiles::GPXRoutesDir + "TwoPoints_N0641701_MN.gpx", isFileName);
    BOOST_CHECK_CLOSE(route.netLength(), 999.111, 0.01);
}
//A route that circles back to the beginning resulting in a net length of 0.
BOOST_AUTO_TEST_CASE(BackToStart)
{
    Route route = Route(LogFiles::GPXRoutesDir + "BackToStart_N0641701_MHINSRM.gpx", isFileName);
    BOOST_CHECK_EQUAL(route.netLength(), 0);
}
//Testing two identical points which should give the expected result of 0.
BOOST_AUTO_TEST_CASE(TwoIdenticalPoints)
{
    Route route = Route(LogFiles::GPXRoutesDir + "TwoIdenticalPoints_N0641701_MM.gpx", isFileName);
    BOOST_CHECK_EQUAL(route.netLength(), 0);
}
//Testing a route that doesn't move anywhere but by elevation.
BOOST_AUTO_TEST_CASE(UpAndDown)
{
    Route route = Route(LogFiles::GPXRoutesDir + "UpAndDown_N0641701_MMMMM.gpx", isFileName);
    BOOST_CHECK_EQUAL(route.netLength(), 0);
}

//Positive and Negative test to make sure the function can handle them correctly.

//Testing a positive latitude and longitude.

BOOST_AUTO_TEST_CASE(PosLatLong)
{
    Route route = Route(LogFiles::GPXRoutesDir + "PosLatLong_N0641701_MIE.gpx", isFileName);
    BOOST_CHECK_CLOSE(route.netLength(), 28276.2, 0.01);
}

//Testing Positive latitude but negative longitude
BOOST_AUTO_TEST_CASE(PosLatNegLong)
{
    Route route = Route(LogFiles::GPXRoutesDir + "PosLatNegLong_N0641701_MGA.gpx", isFileName);
    BOOST_CHECK_CLOSE(route.netLength(), 28276.2, 0.01);
}

//Testing netagive latitude and negative longitude.
BOOST_AUTO_TEST_CASE(NegLatNegLong)
{
    Route route = Route(LogFiles::GPXRoutesDir + "NegLatNegLong_N0641701_MQU.gpx", isFileName);
    BOOST_CHECK_CLOSE(route.netLength(), 28276.2, 0.01);
}

//Testing negative latitude and positive longitude
BOOST_AUTO_TEST_CASE(NegLatPosLong)
{
    Route route = Route(LogFiles::GPXRoutesDir + "NegLatPosLong_N0641701_MSY.gpx", isFileName);
    BOOST_CHECK_CLOSE(route.netLength(), 28276.2, 0.01);
}

//Testing whether or not the function can handle large numbers.
BOOST_AUTO_TEST_CASE(BigNumbers)
{
    Route route = Route(LogFiles::GPXRoutesDir + "BigNumbers_N0641701_MHCDE.gpx", isFileName);
    BOOST_CHECK_CLOSE(route.netLength(), 18398222.331737, 0.01);
}

//Testing whether or not the function can handle very small numbers.
BOOST_AUTO_TEST_CASE(SmallNumbers)
{
    Route route = Route(LogFiles::GPXRoutesDir + "SmallNumbers_N0641701_MHCDE.gpx", isFileName);
    BOOST_CHECK_CLOSE(route.netLength(), 222390.160475, 0.01);
}

//Testing whether or not the function can handle extremely large data sets.
BOOST_AUTO_TEST_CASE(BigData)
{
    Route route = Route(LogFiles::GPXRoutesDir + "BigData_N0641701_MHCBA.gpx", isFileName);
    BOOST_CHECK_CLOSE(route.netLength(), 2827.47, 0.01);
}
BOOST_AUTO_TEST_SUITE_END()

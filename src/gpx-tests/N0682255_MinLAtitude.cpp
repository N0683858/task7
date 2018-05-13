
#include <boost/test/unit_test.hpp>

#include <stdexcept>

#include "xmlparser.h"
#include "logs.h"
#include "route.h"

using namespace GPS;

/*////////////////////////////////////////Design//////////////////////////////////////////////////////////////

It's important to know that this test suit assumes correct implimentation of the route class.
As such it dose not attempt to check for null vectors and invalid arguments.


1: Testing one value

2: Test suit for data patterns
    1:Ascending
    2:Descending
    3:Staggered

3: Test suit for different values
    1:Positive
    2:Negative
    3:Positive and Negative

4: Large data set

5: Test suit for Ivalid input
    1: >=90
    2: <=-90

Test 1 is needed as the start as a failure would produce a failure for tests 2,3 and 4.

Test 2 comes before 3 but only uses positive values. I origionally had Test 3 before 2,
however they would need a pattern or to be staggered which gives the data patterns test no purpose.
As a result test 2 now only uses positive values - positive values test in different values is
still needed as tests can be run in any order.

Test 3 now uses only staggered values.

Test 5 is placed at the end to encourage correct code before handling exceptions.
*/

/*
    using tolerance as 0.1 as test data is widely spead +- ~10 however if there is manipulation of data
    maybe in a for loop that uses ++ then using 0.1 will distinguish between the values.
*/
BOOST_AUTO_TEST_SUITE(n0682255)


/*
 The check single value test case holds the smallest route possible of one position.
 If this test is failed it means the implimentation of the function is severly wrong.
 This is to catch functions that either manipulate the data, or return the wrong value.
 For the test data: the longditude is 1 and elevation 2 to distinguish between them if they are returned.
*/
BOOST_AUTO_TEST_CASE(checkSingleValue)
{
    const bool isFileName = true;
    const std::string filePath = LogFiles::GPXRoutesDir + "singleValueN0682255.gpx";

    Route route = Route(filePath, isFileName);

    BOOST_CHECK_CLOSE(route.minLatitude() , 0 , 1);

}

/*
    This test suit checks for hard coded return values e.g returning Position[0],
    these would pass tests where the smallest latitudes were at the begining.
    By testing descending, ascending and staggered values we can eliminate hard coded return values.
 */
BOOST_AUTO_TEST_SUITE(DataSetPatterns)

BOOST_AUTO_TEST_CASE(checkAscending)
{
    const bool isFileName = true;
    const std::string filePath = LogFiles::GPXRoutesDir + "posAscendN0682255.gpx";

    Route route = Route(filePath, isFileName);

    BOOST_CHECK_CLOSE(route.minLatitude() , 1 , 1);

}

BOOST_AUTO_TEST_CASE(checkDescending)
{
    const bool isFileName = true;
    const std::string filePath = LogFiles::GPXRoutesDir + "posDescendN0682255.gpx";

    Route route = Route(filePath, isFileName);

    BOOST_CHECK_CLOSE(route.minLatitude() , 60 , 1);

}

BOOST_AUTO_TEST_CASE(checkPosativeStaggered)
{
    const bool isFileName = true;
    const std::string filePath = LogFiles::GPXRoutesDir + "posStaggeredN0682255.gpx";

    Route route = Route(filePath, isFileName);

    BOOST_CHECK_CLOSE(route.minLatitude() , 20 , 1);

}
BOOST_AUTO_TEST_SUITE_END()


/*
    This test suit tests if the function can handle positive , negative and a mixture of the both.
 */
BOOST_AUTO_TEST_SUITE(ValueHandling)
BOOST_AUTO_TEST_CASE(checkPositive)
{
    const bool isFileName = true;
    const std::string filePath = LogFiles::GPXRoutesDir + "posStaggeredN0682255.gpx";

    Route route = Route(filePath, isFileName);

    BOOST_CHECK_CLOSE(route.minLatitude() , 20 , 1);

}

BOOST_AUTO_TEST_CASE(checkNegative)
{
    const bool isFileName = true;
    const std::string filePath = LogFiles::GPXRoutesDir + "negStaggeredN0682255.gpx";

    Route route = Route(filePath, isFileName);

    BOOST_CHECK_CLOSE(route.minLatitude() , -40 , 1);

}

BOOST_AUTO_TEST_CASE(checkPosativeandNegative)
{
    const bool isFileName = true;
    const std::string filePath = LogFiles::GPXRoutesDir + "posNegStaggeredN0682255.gpx";

    Route route = Route(filePath, isFileName);

    BOOST_CHECK_CLOSE(route.minLatitude() , -19.9869 , 1);

}
BOOST_AUTO_TEST_SUITE_END()


/*
    This test case uses large data sets. It also uses values with very similar numbers
so the tolerance has to be of greater precision. Otherwise the test may be passed.
 */
BOOST_AUTO_TEST_CASE(checkLargeData)
{
    const bool isFileName = true;
    const std::string filePath = LogFiles::GPXRoutesDir + "NorthYorkMoors.gpx";

    Route route = Route(filePath, isFileName);

    BOOST_CHECK_CLOSE(route.minLatitude() , 54.40526783466339  , 0.001);

}
BOOST_AUTO_TEST_SUITE(InvalidData)


/*
    These test cases check if there are any invalid values as latitude cannot be greater than 90 deg or less than -90 deg
*/
BOOST_AUTO_TEST_CASE(checkGreaterThan90)
{
    const bool isFileName = true;
    const std::string filePath = LogFiles::GPXRoutesDir + "posOutOfBoundsN0682255.gpx";

    Route route = Route(filePath, isFileName);

    BOOST_CHECK_THROW(route.minLatitude() , std::invalid_argument);

}

BOOST_AUTO_TEST_CASE(checkLessThanMinus90)
{
    const bool isFileName = true;
    const std::string filePath = LogFiles::GPXRoutesDir + "negOutOfBoundsN0682255.gpx";

    Route route = Route(filePath, isFileName);

    BOOST_CHECK_THROW(route.minLatitude() , std::invalid_argument);

}
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()




#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "route.h"
#include "track.h"

using namespace GPS;

BOOST_AUTO_TEST_SUITE(MaxLongitudeN0494166)

const bool isFileName = true;

    BOOST_AUTO_TEST_CASE(HorizontalEastWestLine)
    {
        Route route = Route(LogFiles::GPXRoutesDir + "N0494166HorizontalEastWestLine.gpx", isFileName);
        BOOST_CHECK_EQUAL(route.maxLongitude(), 0.0898312);
    }
    //This is to test the basic functionality of the function, ensuring that a normal horizontal line results in a correct answer. If it doesn't, that's probably a bit of a red flag.
    
    BOOST_AUTO_TEST_CASE(VerticalNorthSouthLine)
    {
        Route route = Route(LogFiles::GPXRoutesDir + "N0494166VerticalNorthSouthLine.gpx", isFileName);
        BOOST_CHECK_EQUAL(route.maxLongitude(), 0.0898312);
    }
    //This is to ensuree the functionality of the function with several equal values being the highest.

    BOOST_AUTO_TEST_CASE(SinglePoint)
    {
        Route route = Route(LogFiles::GPXRoutesDir + "N0494166SinglePoint.gpx", isFileName);
        BOOST_CHECK_EQUAL(route.maxLongitude(), 0.0898312);
    }
    //This is to ensure the functionality of the function when working with a single point.

    BOOST_AUTO_TEST_CASE(HighestZero)
    {
        Route route = Route(LogFiles::GPXRoutesDir + "N0494166HighestZero.gpx", isFileName);
        BOOST_CHECK_EQUAL(route.maxLongitude(), 0);
    }
    //This is to ensure the functionality of the function when the highest longitude is 0.

    BOOST_AUTO_TEST_CASE(HighestNegative)
    {
        Route route = Route(LogFiles::GPXRoutesDir + "N0494166HighestNegative.gpx", isFileName);
        BOOST_CHECK_EQUAL(route.maxLongitude(), -0.0898312);
    }
    //This is to ensure the functionality of the function when the highest longitude is a negative number.

    BOOST_AUTO_TEST_CASE(TooLarge)
    {
        Route route = Route(LogFiles::GPXRoutesDir + "N0494166TooLarge.gpx", isFileName);
        BOOST_CHECK_THROW(route.maxLongitude(), std::out_of_range);
    }
    //This is to ensure that the function recognises when it is using a value outide of the correct range.

    BOOST_AUTO_TEST_CASE(SlightDifference)
    {
        Route route = Route(LogFiles::GPXRoutesDir + "N0494166SlightDifference.gpx", isFileName);
        BOOST_CHECK_EQUAL(route.maxLongitude(), 0.0898313);
    }
    //This is to ensure that the function maintains functionality when the largest value is only slightly higher (0.0000001) than the next highest.
BOOST_AUTO_TEST_SUITE_END()

//Type:     Source file (Testing)
//User:     n0688119 (Elliot Harding)
//Purpose:  Testing the function route::maxGradient()

/*
                **Documentation**

This test file contains 14 tests for the function route::maxGradient(). The tests were chosen
in order to test the full functionality of maxGradient, ensuring that it is implimented correctly.
A range of data is used within the tests, this includes typical data, atypical data as well as
incorrect data. This way the expected results from all types of data input can be tested.

In terms of atypical data, the extremes of input data can be tested. Once the edges of correct
data is tested, it is safe to assume that input data inbetween the edge cases will also work
correctly.
 */

//Includes:
#include <boost/test/unit_test.hpp>
#include "logs.h"
#include "route.h"
#include "track.h"

//namespaces:
using namespace GPS;

//Public variables:
const bool isFileName = true;

//Test cases:
BOOST_AUTO_TEST_SUITE(Route_maxGradient)

/*
Test 1:
created using :     gpx log made manually
Description   :     This test case tests normal data, with variing elevation changes, the function should return
                    the largest gradient between two points.
GPX contains   :    Typical data, with varing elevation changes
*/
BOOST_AUTO_TEST_CASE(n0688119_Route_maxGradient_ChangesInElevation){
    Route route = Route(LogFiles::GPXRoutesDir + "n0688119_differentChangesInElevation.gpx",isFileName);
    BOOST_CHECK_CLOSE(route.maxGradient(),89.7426543,1);
}

/*
Test 2:
created using :     gpx log made manually
Description   :     Testing if the function finds the smallest negative gradient, given that all the gradients between
                    points are negative.
GPX contains   :    Positions all lower in elevation than the previous point, some to a greater extent
*/
BOOST_AUTO_TEST_CASE(n0688119_Route_maxGradient_SmallestNegativeGradient){
    Route route = Route(LogFiles::GPXRoutesDir + "n0688119_smallestNegativeGradient.gpx",isFileName);
    BOOST_CHECK_CLOSE(route.maxGradient(),-65.93637193,1);
}

/*
Test 3:
created using  :    generated via source function
Description    :    Testing if the function handles no change in latitude or longitude,
                    as this would result in a division by zero as there is not change in
                    distance(from a birds eye view)
GPX contains   :    Assortment of positions, all with the same latitude and longitude
Expected result:    function returns 90 degrees (-90 degrees in the case of a lower elevation)


    !!!!TO NOTE!!!!
    First I was going to do a boost check throw, but the teacher pointed out to me that
    if the latitude and logitude are the same it is not an error but a feature, so instead I
    compare with 90 degrees

*/
BOOST_AUTO_TEST_CASE(n0688119_Route_maxGradient_noLatOrLongChange){
    Route route = Route(LogFiles::GPXRoutesDir + "n0688119_noLatOrLongChange.gpx",isFileName);
    BOOST_CHECK_EQUAL(route.maxGradient(),90);
}

/*
Test 4:
created using :     generated via source function
Description   :     Testing the function returns 0 (meaning the greatest gradient change is 0), if there are no changes
                    in elevation of the route
GPX contains   :    Positions all the same elevation
*/
BOOST_AUTO_TEST_CASE(n0688119_Route_maxGradient_NoElevationChange){
    Route route = Route(LogFiles::GPXRoutesDir + "n0688119_noElevationChange.gpx",isFileName);
    BOOST_CHECK_EQUAL(route.maxGradient(),0);
}

/*
Test 5:
created using  :    generated via source function
Description    :    Testing the function handles a route if successive points have a positive gradient
Expected result:    The largest positive gradient
GPX contains   :    Positions all higher in elevation than the previous point with same increase between each
*/
BOOST_AUTO_TEST_CASE(n0688119_Route_maxGradient_constantUpwards){
    Route route = Route(LogFiles::GPXRoutesDir + "n0688119_constantUpwards.gpx",isFileName);
    BOOST_CHECK_CLOSE(route.maxGradient(),6.39971588,1);
}

/*
Test 6:
created using  :    generated via source function
Description    :    Testing the function handles a route if successive points have a negative gradient
Expected result:    The largest negative gradient
GPX contains   :    Positions all lower in elevation than the previous point with same decrease between each
*/
BOOST_AUTO_TEST_CASE(n0688119_Route_maxGradient_constantDownwards){
    Route route = Route(LogFiles::GPXRoutesDir + "n0688119_constantDownwards.gpx",isFileName);
    BOOST_CHECK_CLOSE(route.maxGradient(),-6.39971588,1);
}

/*
Test 7:
created using  :    generated via source function
Description    :    Testing the function handles a route gradient which goes up then down
Expected result:    The largest positive gradient
*/
BOOST_AUTO_TEST_CASE(n0688119_Route_maxGradient_UpThenDown){
    Route route = Route(LogFiles::GPXRoutesDir + "n0688119_UpThenDown.gpx",isFileName);
    BOOST_CHECK_CLOSE(route.maxGradient(),6.39971588,1);
}

/*
Test 8:
created using  :    generated via source function
Description    :    Testing the function handles a route gradient which goes down then up
Expected result:    The largest positive gradient
*/
BOOST_AUTO_TEST_CASE(n0688119_Route_maxGradient_DownThenUp){
    Route route = Route(LogFiles::GPXRoutesDir + "n0688119_DownThenUp.gpx",isFileName);
    BOOST_CHECK_CLOSE(route.maxGradient(),6.39971588,1);
}

/*
Test 9:
created using  :    generated via source function
Description    :    Testing the function can handle large elevation values
Expected result:    The largest positive gradient
*/
BOOST_AUTO_TEST_CASE(n0688119_Route_maxGradient_largeValues){
    Route route = Route(LogFiles::GPXRoutesDir + "n0688119_largeValues.gpx",isFileName);
    BOOST_CHECK_CLOSE(route.maxGradient(),-6.39971588,0.1);
}

/*
Test 10:
created using  :    generated via source function
Description    :    Testing the function can handle precise decimal elevation values
Expected result:    The largest positive gradient
*/
BOOST_AUTO_TEST_CASE(n0688119_Route_maxGradient_smallValues){
    Route route = Route(LogFiles::GPXRoutesDir + "n0688119_smallValues.gpx",isFileName);
    BOOST_CHECK_CLOSE(route.maxGradient(),-6.39971588,0.1);
}

/*
Test 11:
created using  :    generated via source function
Description    :    Testing the function can handle small decimal elevation values
Expected result:    The largest positive gradient
*/
BOOST_AUTO_TEST_CASE(n0688119_Route_maxGradient_smallElevationChanges){
    Route route = Route(LogFiles::GPXRoutesDir + "n0688119_smallElevationChange.gpx",isFileName);
    BOOST_CHECK_CLOSE(route.maxGradient(),6.39971588,0.1);
}

/*
Test 12:
created using  :    generated via source function
Description    :    Testing if the function handles only one point, as two are needed to find a gradient
GPX contains   :    Only one position
Expected result:    std::invalid_argument thrown
*/
BOOST_AUTO_TEST_CASE(n0688119_Route_maxGradient_onePoint){
    Route route = Route(LogFiles::GPXRoutesDir + "n0688119_onePoint.gpx",isFileName);
    BOOST_CHECK_THROW(route.maxGradient(),std::invalid_argument);
}

/*
Test 13:
created using  :    gpx log made manually
Description    :    Testing if input that is not numbers is dealt with correctly
GPX contains   :    Letters are input instead of numbers for the elevation
Expected result:    std::invalid_argument thrown
*/
BOOST_AUTO_TEST_CASE(n0688119_Route_maxGradient_incorrectInput){
    BOOST_CHECK_THROW(Route route = Route(LogFiles::GPXRoutesDir + "n0688119_incorrectInput.gpx",isFileName),std::invalid_argument);
}

/*
Test 14:
created using  :    generated via source function
Description    :    Testing if the function handles empty input correctly
GPX contains   :    No data
Expected result:    std::domain_error thrown
*/
BOOST_AUTO_TEST_CASE(n0688119_Route_maxGradient_noInput){
    BOOST_CHECK_THROW(Route route = Route(LogFiles::GPXRoutesDir + "n0688119_noInput.gpx",isFileName),std::domain_error);
}

BOOST_AUTO_TEST_SUITE_END()

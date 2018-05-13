#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "route.h"

//Include using namespace libraries
using namespace GPS;


//////////////////////////////////////////////////////////
BOOST_AUTO_TEST_SUITE(minLatitude)
// The first part of the test is to verify of the implementation of the function
// works for negative Latitudes. The boundaries for latitude is that it  can be as high as 90
// and as low as -90. The edge cases where errors are more prone to be is when the latitude
// is in the area of 90, 0, or -90. The test below uses a variety of different route sizes and latitudes
// to ensure there are no bugs in the min latitude function.
BOOST_AUTO_TEST_CASE(NegativeLatitude){
  // The two files below produce negative latitude values for a gpx file. This gpx file
  // was created with customize parameters. the result return should be -90 or close to it by .1
  // The second test should be -89.11.

  //The latitude values start high then go low.
    Route route = Route(LogFiles::GPXRoutesDir + "ShortRouteNegativeNumb.gpx", fileExist);
    BOOST_CHECK_CLOSE(route.minLatitude(), -90 ,0.1);

    //In this file the latitude values fluctuate with its lowest value located in the middle.
    Route route = Route(LogFiles::GPXRoutesDir + "LatDecline.gpx", fileExist);
    BOOST_CHECK_CLOSE(route.minLatitude(), -89.11 , 0.1);

}
// This test case handles numbers that are not a whole decimal.
BOOST_AUTO_TEST_CASE(ZeroLatitudes){
  Route route = Route(LogFiles::GPXRoutesDir + "MinLatEquatMeridaian.gpx", fileExist);
  BOOST_CHECK_CLOSE(route.minLatitude(), -0.179964 , 0.1);
}

//
//
//
//This test case checks to see how well the sorting algorithm is within the function
//By having the lowest value continuously swapped until the lowest value has been found.
BOOST_AUTO_TEST_CASE(FluctuatingLat){
  Route route = Route(LogFiles::GPXRoutesDir + "SpikeLat.gpx", fileExist);
  BOOST_CHECK_CLOSE(route.minLatitude(), 52.7325, 0.1);
}


// This test case just checks to see if it handles positive latitude values.
BOOST_AUTO_TEST_CASE(PositiveLatitudes){
  Route route = Route(LogFiles::GPXRoutesDir + "MinLatNorthPole.gpx", fileExist);
  BOOST_CHECK_CLOSE(route.minLatitude(),89.82, 0.1)
}

//The lowest value will be located at the first point, but this test is just checking how
//well the function handles the different types of routes.
BOOST_AUTO_TEST_CASE(risingLatitudes){
  Route route = Route(LogFiles::GPXRoutesDir + "LatRising.gpx", fileExist);
  BOOST_CHECK_CLOSE(route.minLatitude(),52.8225, 0.1)
}

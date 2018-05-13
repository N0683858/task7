//Created by N0689061
#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "route.h"
#include "track.h"

using namespace GPS;


/*
                                   Documentation

The following test cases are to test the validity of the netHeightGain function in order to make sure that
the values being returned are both valid and accurate. There are 9 test cases below, each providing a description
of the test case.

The test cases are as follows:

Single_Elevation_Value
No_Elevation
Negative_Net_Elevation
Positive_Net_Elevation
Negative_Elevation_Values
Positive_Elevation_Values
Positive_Negative_Values
Large_Dataset
Alternating_Elevations

*/

BOOST_AUTO_TEST_SUITE( Net_Height_Gain_Z )

const bool isFileName = true;

/*
Test: Single_Elevation_Value
Desc: This test checks if the the correct net elevation value is returned when there is only a single point in the
      GPX file. The net elevation returned should be 0 (as there are no other points).
*/
BOOST_AUTO_TEST_CASE(Single_Elevation_Value){
    Route route = Route(LogFiles::GPXRoutesDir + "Edge.gpx", isFileName);
    BOOST_CHECK_CLOSE(route.netHeightGain(), 0, 0.01);
}

/*
Test: No_Elevation
Desc: This test checks whether the correct net elevation value returned when there is no elevation (flat plane).
      The net elevation returned should be 0.
*/
BOOST_AUTO_TEST_CASE(No_Elevation){
    Route route = Route(LogFiles::GPXRoutesDir + "ABCD.gpx", isFileName);
    BOOST_CHECK_CLOSE(route.minElevation(), 0, 0.01);
}

/*
Test: Negative_Net_Elevation
Desc: This test checks whether the net elevation returned is 0 when the net elevation result is negative. i.e if the
      net elevation is -20 the value returned from the function should be 0.
*/
BOOST_AUTO_TEST_CASE(Negative_Net_Elevation){
    Route route = Route(LogFiles::GPXRoutesDir + "NorthYorkMoors.gpx", isFileName);
    BOOST_CHECK_CLOSE(route.netHeightGain(), 0, 0.01);
}

/*
Test: Positive_Net_Elevation
Desc: This test checks whether the the function returns the correct net elevation value when working with positive elevation values.
*/
BOOST_AUTO_TEST_CASE(Positive_Net_Elevation){
    Track track = Track(LogFiles::GPXTracksDir + "positiveNetElevation.gpx", isFileName);
    BOOST_CHECK_CLOSE(track.netHeightGain(), 60, 0.01);
}

/*
Test: Negative_Elevation_Values
Desc: This test checks whether the the function returns the correct net elevation value when working with negative elevation values.
*/
BOOST_AUTO_TEST_CASE(Negative_Elevation_Values){
    Track track = Track(LogFiles::GPXTracksDir + "negativeElevation.gpx", isFileName);
    BOOST_CHECK_CLOSE(track.netHeightGain(), 5, 0.01);
}

/*
Test: Positive_Elevation_Values
Desc: This test checks whether the the function returns the correct net elevation value when working with positive elevation values.
*/
BOOST_AUTO_TEST_CASE(Positive_Elevation_Values){
    Track track = Track(LogFiles::GPXTracksDir + "positiveElevation.gpx", isFileName);
    BOOST_CHECK_CLOSE(track.netHeightGain(), 202, 0.01);
}

/*
Test: Positive_Negative_Values
Desc: This test checks whether the the function returns the correct net elevation value when working with both positive and negative
      elevation values.
*/
BOOST_AUTO_TEST_CASE(Positive_Negative_Values){
    Track track = Track(LogFiles::GPXTracksDir + "negativePositiveElevation.gpx", isFileName);
    BOOST_CHECK_CLOSE(track.netHeightGain(), 25, 0.01);
}

/*
Test: Large_Dataset
Desc: This test checks whether the the function returns the correct net elevation value when working with a large dataset.
*/
BOOST_AUTO_TEST_CASE(Large_Dataset){
    Route route = Route(LogFiles::GPXRoutesDir + "NorthYorkMoors.gpx", isFileName);
    BOOST_CHECK_CLOSE(route.netHeightGain(), 0, 0.01);
}


/*
Test: Alternating_Elevations
Desc: This test checks whether the the function returns the correct net elevation value when with alternating positive and negative
      elevations are being read in
*/
BOOST_AUTO_TEST_CASE(Alternating_Elevations){
    Route route = Route(LogFiles::GPXRoutesDir + "ZigZag.gpx", isFileName);
    BOOST_CHECK_CLOSE(route.netHeightGain(), 50, 0.01);
}


BOOST_AUTO_TEST_SUITE_END()

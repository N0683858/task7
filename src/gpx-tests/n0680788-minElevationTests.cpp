
#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "route.h"
#include "track.h"

using namespace GPS;

/*
Test Suite for method Route::minElevation() - N0680788
--------------------------------------------------------
The original set position that I have used for all the tests is Earth::CityCampus, which has a set elevation of 53 metres.

The test cases that I have designed are:

 - null_elevation: 
This will test a route that has been set with null elevation (constant) when using the GridWorld constructor, the value returned should be equal to the set position (53).
 - constant_elevation: 
This will test a route that has a constant elevation i.e. GHI.
 - elevation_above_sealevel: 
This will test a route that starts below sea level i.e. negative elevation, then proceeds to increase in elevation above sea level to the original position (53).
 - elevation_below_sealevel: 
This will test a route that starts above sea level i.e. original position, then proceeds to decrease in elevation below sea level to a negative value.
 - increasing_elevation: 
This will test a route that starts at a position on the outer level of gridworld, and is positive, i.e. ABCDE. The route will increase in elevation to the original set position (53).
 - decreasing_elevation: 
This will test a route that starts at the original set position (53), and decreases to a position on the outer level of gridworld, and is positive.
 - pyramid_elevation: 
This will test a route starting from a elevation on the outer level of gridworld, increasing to the original set elevation (53), and then back to the start elevation.
 - valley_elevation:
This will test a route starting from the original set elevation (53), then decreases to a elevation on the outer level of gridworld, then back to the original set elevation.
*/

BOOST_AUTO_TEST_SUITE( n0680788_Route_minElevation )

const bool correctFile = true;

//The route has been set is 'MHC'
//The GridWorld produced has been set so that the difference in elevation is 0.
//This means that for any route given, the elevation is not going to change (constant)
//Meaning that the minimum elevation is going to be the original set position, which should return 53 metres. 
BOOST_AUTO_TEST_CASE( null_elevation )
{
   Route route = Route(LogFiles::GPXRoutesDir + "minElevation_n0680788_nullElevationDifference.gpx", correctFile);
   BOOST_CHECK_EQUAL( route.minElevation(), 53.000000 );
}

//The route that has been set is 'GHI'
//The GridWorld produced has been set so that the difference in elevation is 20.
//This means that because GHI all have the same elevation, there would be no change, but because they are on a lower level than the original set elevation, the value would different to 53.
//Therefore the minimum value returned should have a difference of 20 from the original set elevation. In this case 33.
BOOST_AUTO_TEST_CASE( constant_elevation )
{
   Route route = Route(LogFiles::GPXRoutesDir + "minElevation_n0680788_constantElevation.gpx", correctFile);
   BOOST_CHECK_EQUAL( route.minElevation(), 33.000000 );
}

//The route that has been set is 'CHM'
//The GridWorld produced has been set so that the difference in elevation is 30.
//The reason for this is so that a position on the lowest level of GridWorld, has a negative elevation which would be below sea level.
//A position 'C' on the lowest level would be the start position, and the end of the route would be the original set position i.e. CityCampus.
//Since as 'C' is 2 levels away from 'M' (CityCampus), the minimum elevation value should be -7 (53-2(30))
BOOST_AUTO_TEST_CASE( elevation_above_sealevel )
{
   Route route = Route(LogFiles::GPXRoutesDir + "minElevation_n0680788_riseAboveSeaLevel.gpx", correctFile);
   BOOST_CHECK_EQUAL( route.minElevation(), -7.000000 );
}

//The route that has been set is 'MHC'
//The GridWorld produced has been set so that the difference in elevation is 30.
//Similar to 'elevation_above_sealevel', a position on the outer level of GridWorld would have a negative elevation. 
//So the start position 'M' (CityCampus)  would be the highest elevation, and the last position C would have the lowest position elevation.
//Since as 'C' is 2 levels away from 'M' (CityCampus), the minimum elevation value should be -7 (53-2(30))
BOOST_AUTO_TEST_CASE( elevation_below_sealevel )
{
   Route route = Route(LogFiles::GPXRoutesDir + "minElevation_n0680788_fallBelowSeaLevel.gpx", correctFile);
   BOOST_CHECK_EQUAL( route.minElevation(), -7.000000 );
}

//The route that has been set is 'CHM'
//The GridWorld produced has been set so that the difference in elevation is 20.
//This route will start on the lowest elevation based on elevation difference, and increase in elevation to the elevation of CityCampus.
//Since as the difference in elevation is 20, the minimum elevation value returned should be 13 (53-2(20))
BOOST_AUTO_TEST_CASE( increasing_elevation )
{
   Route route = Route(LogFiles::GPXRoutesDir + "minElevation_n0680788_increasingElevation.gpx", correctFile);
   BOOST_CHECK_EQUAL( route.minElevation(), 13.000000 );
}

//The route that has been set is 'MHC'
//The GridWorld produced has been set so that the difference in elevation is 20.
//The start position would be CityCampus, and the elevation should decrease to the lowest elevation based on the elevation difference.
//Since as the difference in elevation is 20, the minimum elevation value returned should be 13 (53-2(20))
BOOST_AUTO_TEST_CASE( decreasing_elevation )
{
   Route route = Route(LogFiles::GPXRoutesDir + "minElevation_n0680788_decreasingElevation.gpx", correctFile);
   BOOST_CHECK_EQUAL( route.minElevation(), 13.000000 );
}

//The route that has been set is 'CHMHC'
//The GridWorld produced has been set so that the difference in elevation is 20.
//The reason for the elevation being given in a pyramid shape, is due to the start postion being set to 'C' which is the lowest possible elevation value based on elevation difference, and then increasing to 'M' which is the CityCampus position (highest elevation), then going back down to 'C'
//Since as the difference in elevation is 20, the minimum elevation value returned should be 13 (53-2(20))
BOOST_AUTO_TEST_CASE( pyramid_elevation )
{
   Route route = Route(LogFiles::GPXRoutesDir + "minElevation_n0680788_pyramid.gpx", correctFile);
   BOOST_CHECK_EQUAL( route.minElevation(), 13.000000 );
}

//The route that has been set is 'MHCHC'
//The GridWorld produced has been set so that the difference in elevation is 20.
//The reason for the elevation being given in a valley shape, is due to the start position being set to 'M' CityCampus and then decreasing to the lowest possible elevation 'C' and then increasing back to 'M'.
//Since as the difference in elevation is 20, the minimum elevation value returned should be 13 (53-2(20))
BOOST_AUTO_TEST_CASE( valley_elevation )
{
   Route route = Route(LogFiles::GPXRoutesDir + "minElevation_n0680788_valley.gpx", correctFile);
   BOOST_CHECK_EQUAL( route.minElevation(), 13.000000 );
}

BOOST_AUTO_TEST_SUITE_END()



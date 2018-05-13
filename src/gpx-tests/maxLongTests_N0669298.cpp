#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "route.h"
#include "track.h"

using namespace GPS;

BOOST_AUTO_TEST_SUITE( Route_MaxLongitude_N0669298 )

const bool isFileName = true;

// A test case to test that the right Longitude is being returned from a GPX file where the gridworld represents a straight line
// The returned Longitude should be the greatest value (including a negative range)
// In this case the gpx is named: CliftonStraightLineIncreasingLong.gpx

BOOST_AUTO_TEST_CASE( CheckLongFlatHorizLine )
{
   Route route = Route(LogFiles::GPXRoutesDir + "CliftonStraightLineIncreasingLong.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.maxLongitude(), -1.16021);
}

// A test case to test that the right Longitude is being returned from a GPX file where the gridworld represents a straight vertical line
// The returned Longitude should be the greatest value (including a negative range)
// multiple points along the route will have this same Longitude
// In this case the gpx is named: CliftonStraightLineIncreasingLong.gpx

BOOST_AUTO_TEST_CASE( CheckLongFlatVertLine )
{
   Route route = Route(LogFiles::GPXRoutesDir + "CliftonStraightVerticalLine.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.maxLongitude(), -1.19);
}

// A test case to test that the right Longitude is being returned from a GPX file where the gridworld represents a straight horizontal line
// In this case the line is crossing the primeMeridian in Greenwich (which is the  point at which Longitude is 0)
// The longitude will pass from being a negative value to a positive one
// In this case the gpx is named: AcrossGreenwichPrimeMeridian.gpx

BOOST_AUTO_TEST_CASE( CheckAcrossPrimeMeridian )
{
   Route route = Route(LogFiles::GPXRoutesDir + "AcrossGreenwichPrimeMeridian.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.maxLongitude(), 0.0144234);
}

// A test case to test that the right Longitude is being returned from a GPX file where the gridworld represents a straight vertical line
// In this case the line is running along the primeMeridian in line with Greenwich (which is the  point at which Longitude is 0)
// The longitude will remain as being 0 through all of the points
// In this case the gpx is named: AlongGreenwichPrimeMeridian.gpx

BOOST_AUTO_TEST_CASE( CheckAlongPrimeMeridian )
{
   Route route = Route(LogFiles::GPXRoutesDir + "AlongGreenwichPrimeMeridian.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.maxLongitude(), 0);
}

// A test case to test that the right Longitude is being returned from a GPX file where the gridworld represents a straight horizontal line
// In this case the line is running across the antimeridian in line with Russia and Fiji (which is the  point at which Longitude is 180)
// The longitude will change from the maximum positive value possible for Longitude to the maximum negative value
// This test assumes that the gpx file was generated using an application that takes the limits of Longitude into consideration
// In this case the gpx is named: ExceedMaxLongitudeNearUelkal.gpx

BOOST_AUTO_TEST_CASE( ExceedMaxLongitudeWithloop  )
{
   Route route = Route(LogFiles::GPXRoutesDir + "ExceedMaxLongitudeNearUelkal.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.maxLongitude(), 179.999);
}

// A test case to test that the right Longitude is being returned from a GPX file where the gridworld represents a straight vertical line
// In this case the line is running along the antimeridian in line with Russia and Fiji (which is the  point at which Longitude is 180)
// The longitude will remain at the maximum positve value ( 180 )
// In this case the gpx is named: AlongMaxLongitudeNearUelkal.gpx

BOOST_AUTO_TEST_CASE( AlongMaxLongitude )
{
   Route route = Route(LogFiles::GPXRoutesDir + "AlongMaxLongitudeNearUelkal.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.maxLongitude(), 180);
}

// A test case to test that the an exception is being thrown from the implementation of MaxLongitude
// In this case the line is running across the antimeridian in line with Russia and Fiji (which is the  point at which Longitude is 180)
// The longitude will change from the maximum positive and continue past its bounds
// This test assumes that the gpx file was generated using an application that does not take the limits of Longitude into consideration
// In this case the gpx is named: ExceedMaxLongitudeNearUelkalNoLoop.gpx

BOOST_AUTO_TEST_CASE( AcrossMaxLongitudeWithNoLoop )
{
   Route route = Route(LogFiles::GPXRoutesDir + "ExceedMaxLongitudeNearUelkalNoLoop.gpx", isFileName);
   BOOST_CHECK_THROW( route.maxLongitude(), std::out_of_range);
}

// A test case to test that the an exception is being thrown from the implementation of MaxLongitude
// In this case the line is running across the antimeridian in line with Russia and Fiji (which is the  point at which Longitude is 180)
// The longitude will change from the maximum negative value and continue past its bounds
// This test assumes that the gpx file was generated using an application that does not take the limits of Longitude into consideration
// In this case the gpx is named: ExceedMaxLongitudeNearUelkalNoLoopBackwards.gpx

BOOST_AUTO_TEST_CASE( AcrossMaxLongitudeWithNoLoopBackwards )
{
   Route route = Route(LogFiles::GPXRoutesDir + "ExceedMaxLongitudeNearUelkalNoLoopBackwards.gpx", isFileName);
   BOOST_CHECK_THROW( route.maxLongitude(), std::out_of_range);
}

// A test case to test that the right Longitude is being returned from a GPX file where the gridworld represents a straight vertical line
// In this case the line is running horizontally with only a change of .0000001 Longitude between each point
// In this case the gpx is named: LongitudeChangeOf0000001.gpx

BOOST_AUTO_TEST_CASE( SmallLongChanges )
{
   Route route = Route(LogFiles::GPXRoutesDir + "LongitudeChangeOf0000001.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.maxLongitude(), -1.0000000);
}

// A test case to test that the right Longitude is being returned from a GPX file where the gridworld represents a straight vertical line
// In this case the line is running horizontally with a change of 50 Longitude between each point
// In this case the gpx is named: LongitudeChangeOf50.gpx

BOOST_AUTO_TEST_CASE( LargeLongChanges )
{
   Route route = Route(LogFiles::GPXRoutesDir + "LongitudeChangeOf50.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.maxLongitude(), 151);
}

BOOST_AUTO_TEST_SUITE_END()


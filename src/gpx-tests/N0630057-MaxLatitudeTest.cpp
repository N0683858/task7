#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "route.h"
#include "track.h"


//My test suite has been designed to allow for changes to the maximum latitude using the MaxLatitude() function.
//First, I have used the log files provided to us to check that the function is working correctly. It checks to
//that the function is picking up the correct maximum latitude from a simple log file.
//My second test checks to see if the function is able to deal with a negative latitude being the maximum latitude.
//This is important as a low maximum latitude is possible.
//My third test checks to see whether MaxLatitude() is able to deal with a route or track with different latitude array sizes.
//I have used a few different sizes to ensure it doesn't have a problem.
//My final test checks to see whether it can deal with a whole number and convert it to a float. This is more to check whether
//the function is able to pick the maximum latitude as whole number will not be an input often.




using namespace GPS;

BOOST_AUTO_TEST_SUITE( Max_Latitude )

const bool isFileName = true;


BOOST_AUTO_TEST_CASE( Correct_Max_Latitude ) //Check MaxLatitude() produces the correct latitude
{
   Route route = Route(LogFiles::GPXRoutesDir + "ABCD.gpx", isFileName); // Initializes a Route or Track file to a variable for checking
   Track track = Track(LogFiles::GPXTracksDir + "A1B3C.gpx", isFileName);

   BOOST_CHECK_EQUAL( route.MaxLatitude(), 0.179964 );//checks being run
   BOOST_CHECK_EQUAL( track.MaxLatitude(), 0.179964 );//should both pass

   BOOST_CHECK_EQUAL( route.MaxLatitude(), 0.183648 );//should fail
   BOOST_CHECK_EQUAL( track.MaxLatitude(), 0.183648 );
}


BOOST_AUTO_TEST_CASE( Check_Negatives )//Check MaxLatitudes() can deal with negatives
{
    Route route = Route(LogFiles::GPXRoutesDir + "MinusRouteOne.gpx", isFileName);
    Route route2 = Route(LogFiles::GPXRoutesDir + "MinusRouteTwo.gpx", isFileName);

    Track track = Track(LogFiles::GPXTracksDir + "MinusTrackOne.gpx", isFileName);
    Track track2 = Track(LogFiles::GPXTracksDir + "MinusTrackTwo.gpx", isFileName);

    BOOST_CHECK_EQUAL( route.MaxLatitude(), -0.179964 );
    BOOST_CHECK_EQUAL( route2.MaxLatitude(), -0.179964 );

    BOOST_CHECK_EQUAL( track.MaxLatitude(), -0.179964 );
    BOOST_CHECK_EQUAL( track2.MaxLatitude(), -0.179964 );
}


BOOST_AUTO_TEST_CASE( Deal_with_All_Route_sizes )//Check MaxLatitude() can deal with all route sizes
{
    Route route = Route(LogFiles::GPXRoutesDir + "OnePoint.gpx", isFileName);
    Route route2 = Route(LogFiles::GPXRoutesDir + "TwoPoint.gpx", isFileName);
    Route route3 = Route(LogFiles::GPXRoutesDir + "ThreePoint.gpx", isFileName);

    Track track = Track(LogFiles::GPXTracksDir + "GPXOnePoint.gpx", isFileName);
    Track track2 = Track(LogFiles::GPXTracksDir + "GPXTwoPoint.gpx", isFileName);
    Track track3 = Track(LogFiles::GPXTracksDir + "GPXThreePoint.gpx", isFileName);

   BOOST_CHECK_EQUAL( route.MaxLatitude(), 0.179964 );
   BOOST_CHECK_EQUAL( route2.MaxLatitude(), 0.179964 );
   BOOST_CHECK_EQUAL( route3.MaxLatitude(), 0.179964 );

   BOOST_CHECK_EQUAL( track.MaxLatitude(), 50 );
   BOOST_CHECK_EQUAL( track2.MaxLatitude(), 50 );
   BOOST_CHECK_EQUAL( track3.MaxLatitude(), 50 );
}

BOOST_AUTO_TEST_CASE( Test_Whole_Numbers )//Check MaxLatitude() can deal with whole numbers
{
    Track track = Track(LogFiles::GPXTracksDir + "WholeNumber50.gpx", isFileName);
    Track track2 = Track(LogFiles::GPXTracksDir + "WholeNumber160.gpx", isFileName);
    Route route = Route(LogFiles::GPXRoutesDir + "WholeNumber20.gpx", isFileName);
    Route route2 = Route(LogFiles::GPXRoutesDir + "WholeNumber5.gpx", isFileName);

   BOOST_CHECK_EQUAL( track.MaxLatitude(), 50 );
   BOOST_CHECK_EQUAL( track2.MaxLatitude(), 160 );

   BOOST_CHECK_EQUAL( route.MaxLatitude(), 20 );
   BOOST_CHECK_EQUAL( route2.MaxLatitude(), 5 );
}




BOOST_AUTO_TEST_SUITE_END()

#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "route.h"
#include "track.h"
#include "types.h"

using namespace GPS;

BOOST_AUTO_TEST_SUITE( Total_Time )
	
const bool isFileName = true;

//----testing files with extreme values - high/low----

//test with an empty files to ensure that the function can handle this type of input
BOOST_AUTO_TEST_CASE( Test_Zero_Timings ){
   Track track = Track(LogFiles::GPXTracksDir + "TrackHas0.gpx", isFileName);
   BOOST_CHECK_EQUAL(track.totalTime(), 0);
}

//test a file with a very large totalTime to ensure that the function can handle larger numbers
BOOST_AUTO_TEST_CASE( Test_Large_Timings ){
   Track track = Track(LogFiles::GPXTracksDir + "TrackMultiplePoints.gpx", isFileName);
   BOOST_CHECK_EQUAL(track.totalTime(), 21000);
}



//----Tests on other specific files which have more regular values----

//test file A1B.gpx for the correct result
BOOST_AUTO_TEST_CASE( Test_A1B_Result ){
   Track track = Track(LogFiles::GPXTracksDir + "A1B.gpx", isFileName);
   BOOST_CHECK_EQUAL( track.totalTime(), 10);
}
//test file TrackAbsoluteTimeNegative.gpx for the correct result
BOOST_AUTO_TEST_CASE( Test_TrackAbsoluteTimeNegative_Result ){
   Track track = Track(LogFiles::GPXTracksDir + "TrackAbsoluteTimeNegative.gpx", isFileName);
   BOOST_CHECK_EQUAL( track.totalTime(), 10);
}



//----Tests using other functions----

//BOOST message to tell the user the next tests rely on differnet functions
//warning them that if the other functions are not working then these tests should be ignored
BOOST_AUTO_TEST_CASE( Different_Functions_Message ){
   BOOST_TEST_MESSAGE( "Next tests make use of restingTime() & travellingTime()." );
   BOOST_TEST_MESSAGE( "If these functions are not working correctly, ignore following test results." );
}

//test that restingTime() + travellingTime() == totalTime()
//use the A1B3C.gpx file for the test
BOOST_AUTO_TEST_CASE( Test_Resting_Travelling_Add ){
   Track track = Track(LogFiles::GPXTracksDir + "A1B3C.gpx", isFileName);

   seconds travelling = track.travellingTime();
   seconds resting = track.restingTime();
   seconds total = travelling + resting;

   BOOST_CHECK_EQUAL( track.totalTime(), total);
}

//test that totalTime() - restingTime() == travellingTime()
//use the A1B3C.gpx file for the test
BOOST_AUTO_TEST_CASE( Test_Total_Resting_Sub ){
   Track track = Track(LogFiles::GPXTracksDir + "A1B3C.gpx", isFileName);

   seconds totalTime = track.totalTime();
   seconds resting = track.restingTime();
   seconds total = totalTime - resting;//totalTime should be the larger value everytime

   BOOST_CHECK_EQUAL( track.travellingTime(), total);
}

//test that totalTime() - travellingTime() == restingTime()
//use the A1B3C.gpx file for the test
BOOST_AUTO_TEST_CASE( Test_Total_Travelling_Sub ){
   Track track = Track(LogFiles::GPXTracksDir + "A1B3C.gpx", isFileName);

   seconds totalTime = track.totalTime();
   seconds travelling = track.travellingTime();
   seconds total = totalTime - travelling;//totalTime should be the larger value everytime

   BOOST_CHECK_EQUAL( track.restingTime(), total);
}

BOOST_AUTO_TEST_SUITE_END()



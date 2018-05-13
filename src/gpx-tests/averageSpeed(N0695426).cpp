
#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "route.h"
#include "track.h"

/*Test that can't be done
because of how the averageSpeed function gets it's data there
are a dealing with negative distance and negative time test (as you can't have 
two positions with a negative distance or negative time between them)
 




*/

using namespace GPS;

BOOST_AUTO_TEST_SUITE( average_speed )

bool correctFileName = true;

BOOST_AUTO_TEST_CASE(divide_with_zero_test)
{
	/*
	Speed = distance divide by time and if distance or time are zero
	then that could cause a problem for the averageSpeed function
	*/
	

        Track track = Track(LogFiles::GPXTracksDir + "TestNT.gpx", correctFileName);//NT means no time
	
	//no time test
	BOOST_CHECK_THROW(Track.averageSpeed(true), std::logic_error);
	
	
        Track track = Track(LogFiles::GPXTracksDir + "TestND.gpx", correctFileName);//ND means no distance
	
	//no distance test
	BOOST_CHECK_EQUALS(Track.averageSpeed(true), 0);
	
}

BOOST_AUTO_TEST_CASE(normal_operation)
{
	/*
		This test is design to see of the function 
		can work with the kind of data that it would get 
		normally.
		
		TestNU.gpx has a 
		total distance 10
		total rests 2
		total time 10
	*/
	

        Track track = Track(LogFiles::GPXTracksDir + "TestNU.gpx", correctFileName);//NU means Normal use
	
	
	
	//distance is 10 and time is 10
	
	//with rests 
	/*calculation is 10 / 10 = 1 */
	BOOST_CHECK_EQUALS(Track.averageSpeed(true), 1);
	
	//without rests
	/*
	calculation is 10 / 8 = 1.25*/
	BOOST_CHECK_EQUALS(Track.averageSpeed(false), 1.25);
	
}

BOOST_AUTO_TEST_CASE(small_speed_test)
{
	/*
	This test ensures that the result of average speed remains
	accurate to the greatest possible decimal place
	*/
	

        Track track = Track(LogFiles::GPXTracksDir + "TestSS.gpx", correctFileName);//SS means small speed
	
	/*
	The reason that it is a greater than test is to check that the 
	function is getting a result that is greater than 0. Why
	because the most likely problem that could occur with this function
	is that the result will be rounded to zero.
	
	
	*/
	BOOST_CHECK_GT(Track.averageSpeed(true), 0);
	
	BOOST_CHECK_EQUALS(Track.averageSpeed(true), 0.0000000000001);
}

/*
BOOST_AUTO_TEST_CASE(no_movement_Test)
{
	this test is the same as the no distance test
        Track track = Track(LogFiles::GPXTracksDir + "TestNM.gpx", correctFileName);
	
	BOOST_CHECK_EQUALS(Track.averageSpeed(true), 0);
	
	
}*/

BOOST_AUTO_TEST_CASE(is_route_test)
{

        Track track = Track(LogFiles::GPXRoutesDir + "ABCD.gpx", correctFileName);
	
	/*
	It is highly possible that a correctly formatted route could be used 
	instead of a track because gps program is designed to use both.
	*/
	
	BOOST_CHECK_THROW(Track.averageSpeed(true), std::invalide_argument);
	
}

BOOST_AUTO_TEST_CASE(max_distance_test)
{
	bool isFileName = true;
        Track track = Track(LogFiles::GPXTracksDir + "TestVD.gpx", correctFileName);//VD means vast distance
	
	/*
	This test if the function can calculate large speeds however
	due to the size of the earth it is impossible to get to 
	generate a speed that would meet the max value of a double
	why because any two points on earth can't be more than about 20000
	miles away and the smallest period of time is 1 because seconds is an unsigned integer
	which can't be negative
	*/
	
	BOOST_CHECK_EQUALS(Track.averageSpeed(true), 12430);
	
}

BOOST_AUTO_TEST_SUITE_END()


#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "route.h"
#include "track.h"

using namespace GPS;


/*
Design:
Speed will always be positive, 
and also less than an maximum,
theoretically the maximum speed is that of light at 300,000m/s however most gps systems are made to shut off at 1200mph or 536.5m/s
test 1: typcial speed for persone walking
test 2: typical speed for car

test 3: edge case before shut off
test 5: impossible data



Structure:
Tests are seperated into two groupes
The first for correct data - consisting of regular and edge cases
The second for incorrect data - consisting of inacceptable or no data

*/



BOOST_AUTO_TEST_SUITE( trackMaxSpeed )

const bool isFileName = true;


//tests for correct data
BOOST_AUTO_TEST_CASE (walkingMaxSpeed)
{
	Track track = Track(LogFiles::GPXTracksDir + "maxSpeedWalking.gpx", isFileName);
	BOOST_CHECK_EQUAL(track.maxSpeed(), 1.46);
}

BOOST_AUTO_TEST_CASE (carMaxSpeed)
{
	Track track = Track(LogFiles::GPXTracksDir + "maxSpeedCar.gpx", isFileName);
	BOOST_CHECK_EQUAL(track.maxSpeed(), 7.32);
}

//test for missing or incorrect or out of bounds data
//less than shut off point
BOOST_AUTO_TEST_CASE (edgeMaxSpeed)
{
	Track track = Track(LogFiles::GPXTracksDir + "maxSpeedEdge.gpx", isFileName);
	BOOST_CHECK_LT(track.maxSpeed(), 536.5);
}
//less than LIGHTSPEED
BOOST_AUTO_TEST_CASE (LightSpeed)
{
	Track track = Track(LogFiles::GPXTracksDir + "maxSpeedLightSpeed.gpx", isFileName);
	BOOST_CHECK_LT(track.maxSpeed(), 300000);
}


BOOST_AUTO_TEST_SUITE_END()
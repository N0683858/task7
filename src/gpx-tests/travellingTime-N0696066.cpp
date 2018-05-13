#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "route.h"
#include "track.h"

using namespace GPS;

BOOST_AUTO_TEST_SUITE( Track_TravellingTime )

const bool isFileName = true;

//This checks the travel time is correct when the time duration is set to 1 seconds
//with route A1B2C
BOOST_AUTO_TEST_CASE ( duration_1_sec )
{
    Track track = Track(LogFiles::GPXTracksDir + "TrackDuration1.gpx", isFileName);
    BOOST_CHECK_EQUAL(track.travellingTime(), 3);
}

//This checks the travel time is correct when the time duration is set to 10 seconds
//with route A3B1C
BOOST_AUTO_TEST_CASE ( duration_10_sec )
{
    Track track = Track(LogFiles::GPXTracksDir + "TrackDuration10.gpx", isFileName);
    BOOST_CHECK_EQUAL(track.travellingTime(), 40);
}

//this checks the travel time is correct when the time duration is set to an even number, 2 in this case
//with route A4B2C
BOOST_AUTO_TEST_CASE( duration_2_sec)
{
    Track track = Track(LogFiles::GPXTracksDir + "TrackDurationEven.gpx", isFileName);
    BOOST_CHECK_EQUAL(track.travellingTime(), 12);
}

//this checks the travel time is correct when the time duration is set to an odd number, 7 in this case
//with route M3A2G
BOOST_AUTO_TEST_CASE ( duration_7_sec)
{
    Track track = Track(LogFiles::GPXTracksDir + "TrackDurationOdd.gpx", isFileName);
    BOOST_CHECK_EQUAL(track.travellingTime(), 35);
}

//This test checks the travel time when the time unit duration and interval is 1
BOOST_AUTO_TEST_CASE ( duration_interval_1 )
{
    Track track = Track(LogFiles::GPXTracksDir + "TrackI&D1.gpx", isFileName);
    BOOST_CHECK_EQUAL(track.travellingTime(), 6);
}

//This test checks the travel time when the Log interval is set to 10
BOOST_AUTO_TEST_CASE ( interval_10 )
{
    Track track = Track(LogFiles::GPXTracksDir + "TrackInterval10.gpx", isFileName);
    BOOST_CHECK_EQUAL(track.travellingTime(), 60);
}

/*This test checks that an error is thrown when the log interval is a negative number
because if the log interval is set a negative number then the GPX log becomes corrupted
and doesn't show the correct track*/
BOOST_AUTO_TEST_CASE ( interval_negative )
{
    Track track = Track(LogFiles::GPXTracksDir + "TrackIntervalNegative.gpx", isFileName);
    BOOST_CHECK_THROW(track.travellingTime(), std::invalid_argument);
}

/*This test checks that the correct travel time is produced when log interval is a multiple
 *of the duration and they're both odd numbers*/
BOOST_AUTO_TEST_CASE ( interval_multiple_of_duration )
{
    Track track = Track(LogFiles::GPXTracksDir + "TrackI&DMultiples.gpx", isFileName);
    BOOST_CHECK_EQUAL(track.travellingTime(), 45);
}

/*This test checks if an error is thrown when
 *the log interval and the duration are odd numbers and if they're not multiples.
  The logs produced don't produce the correct number of logs to calculate the travelling time*/
BOOST_AUTO_TEST_CASE( interval_not_multiple_of_duration_odd )
{
    Track track = Track(LogFiles::GPXTracksDir + "TrackI&DNotMultiples.gpx", isFileName);
    BOOST_CHECK_THROW(track.travellingTime(), std::invalid_argument);
}

/*the purpose of this test is to check that the duration is an even number and that
 * the log interval is a factor of the duration while remaining to be equal to
 * or less than half of the duration. This is because if the log interval is more than half
 * of the duration it'll produce incorrect logs and if it is not a factor it also produces incorrect
 * logs
 */
BOOST_AUTO_TEST_CASE( interval_factor_of_duration_and_less_than_half_of_duration )
{
    Track track = Track(LogFiles::GPXTracksDir + "TrackIntervalEvenlessthanhalf.gpx", isFileName);
    BOOST_CHECK_EQUAL(track.travellingTime(), 100);
}

/*This test checks the travel time when the absolute start time is a number beyond 1
as the absolute start time can be a positive value*/
BOOST_AUTO_TEST_CASE ( absolute_1 )
{
    Track track = Track(LogFiles::GPXTracksDir + "TrackAbsoluteTime1.gpx", isFileName);
    BOOST_CHECK_EQUAL(track.travellingTime(), 40);
}

/*This test checks the travel time when the absolute start time is a negative number
because if the absolute start time is set to a negative number then the GPX log becomes corrupted
and doesn't show the correct path*/
BOOST_AUTO_TEST_CASE ( absolute_negative )
{
    Track track = Track(LogFiles::GPXTracksDir + "TrackAbsoluteTimeNegative.gpx", isFileName);
    BOOST_CHECK_THROW(track.travellingTime(), std::invalid_argument);
}

//This tests checks that is can produce the correct results when handling a large track
BOOST_AUTO_TEST_CASE ( multiple_tracks )
{
    Track track = Track(LogFiles::GPXTracksDir + "TrackMultiplePoints.gpx", isFileName);
    BOOST_CHECK_EQUAL(track.travellingTime(), 21000);
}

//This test checks if the correct travel time is returned while the track includes points of no movement
BOOST_AUTO_TEST_CASE ( track_has_rests )
{
    Track track = Track(LogFiles::GPXTracksDir + "TrackHasRests.gpx", isFileName);
    BOOST_CHECK_EQUAL(track.travellingTime(), 30);
}

/*This test checks if the correct travel time appears when one of the point
 * sequence is equal to 0. Eg. A0A2B
*/
BOOST_AUTO_TEST_CASE ( Track_zero_sequence )
{
    Track track = Track(LogFiles::GPXTracksDir + "TrackHas0andRests.gpx", isFileName);
    BOOST_CHECK_EQUAL(track.travellingTime(), 20);
}

BOOST_AUTO_TEST_SUITE_END()

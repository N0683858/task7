/**
 **** Unit tests for the method Route::operator[]()
 *
 * Route::operator[]() returns the Position at the specified index which
 * represents a certain point on the route.
 *
 * First, we should test if Route::operator[]() behaves correctly when the
 * given index refers to a Position within the Route.
 * To do this, we use a GPX file of a route generated using the GridWorld class
 * and we check that the [] operator returns the correct Position at each
 * index.
 *
 * Route::operator[]() should throw an std::out_of_range exception if the index
 * is out of bounds. We should test that the function throws that exception
 * when given an index which is outside the expected interval (from 0 to the
 * size of the route - 1).
 * We expect an std::out_of_range exception in two cases:
 *   - When the index is greater than or equal to the positions vector size.
 *   - When the index is negative.
 *
 * We also test the function for edge cases, for example the first and the last
 * Position of the route which should not throw an exception. In addition, we
 * also test the outer bounds of the array (-1 and the route size).
 *
 * Finally, We use the same tests against a Track object which inherits
 * operator[]() from the Route class.
 **/

#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "route.h"
#include "track.h"
#include "position.h"

using namespace GPS;

BOOST_AUTO_TEST_SUITE( Route_array_operator )

/**
 * Check that Route::operator[] returns all positions of a Route correctly
 * The test Route is extracted from a GPX file generated using the GridWorld
 * class. Thus all the Position values are known.
 * Since Position does not include the == operator, its attributes are checked
 * individually.
 **/
BOOST_AUTO_TEST_CASE( correct_index_route ) {
    Route route = Route(LogFiles::GPXRoutesDir + "MIOT.gpx", true);

    Position pos0 = Position(0, 109.322, 0);
    BOOST_CHECK_EQUAL(route[0].latitude(), pos0.latitude());
    BOOST_CHECK_EQUAL(route[0].longitude(), pos0.longitude());
    BOOST_CHECK_EQUAL(route[0].elevation(), pos0.elevation());

    Position pos1 = Position(0.089982, 109.412, 0);
    BOOST_CHECK_EQUAL(route[1].latitude(), pos1.latitude());
    BOOST_CHECK_EQUAL(route[1].longitude(), pos1.longitude());
    BOOST_CHECK_EQUAL(route[1].elevation(), pos1.elevation());

    Position pos2 = Position(0, 109.502, 0);
    BOOST_CHECK_EQUAL(route[2].latitude(), pos2.latitude());
    BOOST_CHECK_EQUAL(route[2].longitude(), pos2.longitude());
    BOOST_CHECK_EQUAL(route[2].elevation(), pos2.elevation());

    Position pos3 = Position(-0.089982, 109.502, 0);
    BOOST_CHECK_EQUAL(route[3].latitude(), pos3.latitude());
    BOOST_CHECK_EQUAL(route[3].longitude(), pos3.longitude());
    BOOST_CHECK_EQUAL(route[3].elevation(), pos3.elevation());
}

/**
 * Check that operator[] returns all positions of a Track correctly
 * The test Track is extracted from a GPX file generated using the GridWorld
 * class. Thus all the Position values are known.
 * Since Position does not include the == operator, its attributes are checked
 * individually.
 **/
BOOST_AUTO_TEST_CASE( correct_index_track ) {
    Track track = Track(LogFiles::GPXTracksDir + "M3I6O.gpx", true);

    Position pos0 = Position(0, 109.322, 0);
    BOOST_CHECK_EQUAL(track[0].latitude(), pos0.latitude());
    BOOST_CHECK_EQUAL(track[0].longitude(), pos0.longitude());
    BOOST_CHECK_EQUAL(track[0].elevation(), pos0.elevation());

    Position pos1 = Position(0.089982, 109.412, 0);
    BOOST_CHECK_EQUAL(track[1].latitude(), pos1.latitude());
    BOOST_CHECK_EQUAL(track[1].longitude(), pos1.longitude());
    BOOST_CHECK_EQUAL(track[1].elevation(), pos1.elevation());

    Position pos2 = Position(0, 109.502, 0);
    BOOST_CHECK_EQUAL(track[2].latitude(), pos2.latitude());
    BOOST_CHECK_EQUAL(track[2].longitude(), pos2.longitude());
    BOOST_CHECK_EQUAL(track[2].elevation(), pos2.elevation());
}


/**
  * Check that an std::out_of_range exception is thrown when the given index is
  * greater or equal to the size of the positions vector.
  * Test using a Route.
  **/
BOOST_AUTO_TEST_CASE( out_of_range_upper_route ) {
    Route route = Route(LogFiles::GPXRoutesDir + "MIOT.gpx", true);

    BOOST_CHECK_THROW( route[5], std::out_of_range );
    BOOST_CHECK_THROW( route[10], std::out_of_range );
    BOOST_CHECK_THROW( route[15], std::out_of_range );
}

/**
  * Check that an std::out_of_range exception is thrown when the given index is
  * greater or equal to the size of the positions vector.
  * Test using a Track.
  **/
BOOST_AUTO_TEST_CASE( out_of_range_upper_track ) {
    Track track = Track(LogFiles::GPXTracksDir + "M3I6O.gpx", true);

    BOOST_CHECK_THROW( track[5], std::out_of_range );
    BOOST_CHECK_THROW( track[10], std::out_of_range );
    BOOST_CHECK_THROW( track[15], std::out_of_range );
}

/**
  * Check that an std::out_of_range exception is thrown when the given index is
  * negative.
  * Test using a Route.
  **/
BOOST_AUTO_TEST_CASE( out_of_range_negative_route ) {
    Route route = Route(LogFiles::GPXRoutesDir + "MIOT.gpx", true);

    BOOST_CHECK_THROW( route[-5], std::out_of_range );
    BOOST_CHECK_THROW( route[-10], std::out_of_range );
    BOOST_CHECK_THROW( route[-15], std::out_of_range );
}

/**
  * Check that an std::out_of_range exception is thrown when the given index is
  * negative.
  * Test using a Track.
  **/
BOOST_AUTO_TEST_CASE( out_of_range_negative_track ) {
    Track track = Track(LogFiles::GPXTracksDir + "M3I6O.gpx", true);

    BOOST_CHECK_THROW( track[-5], std::out_of_range );
    BOOST_CHECK_THROW( track[-10], std::out_of_range );
    BOOST_CHECK_THROW( track[-15], std::out_of_range );
}

/**
  * Check that std::out_of_range is NOT thrown when the index is equal to
  * one of the endpoints of accepted range. (i.e. 0 and vector size - 1).
  * Test using a Route.
  **/
BOOST_AUTO_TEST_CASE( out_of_range_endpoints_route ) {
    Route route = Route(LogFiles::GPXRoutesDir + "MIOT.gpx", true);

    BOOST_CHECK_NO_THROW( route[0] );
    BOOST_CHECK_NO_THROW( route[3] );
}

/**
  * Check that std::out_of_range is NOT thrown when the index is equal to
  * one of the endpoints of accepted range. (i.e. 0 and vector size - 1).
  * Test using a Track.
  **/
BOOST_AUTO_TEST_CASE( out_of_range_endpoints_track ) {
    Track track = Track(LogFiles::GPXTracksDir + "M3I6O.gpx", true);

    BOOST_CHECK_NO_THROW( track[0] );
    BOOST_CHECK_NO_THROW( track[2] );
}

/**
  * Check that std::out_of_range is thrown when the index is equal to one of
  * the outer bounds of the correct range (-1 and vector size).
  * Test using a Route.
  **/
BOOST_AUTO_TEST_CASE( out_of_range_outer_bounds_route )
{
    Route route = Route(LogFiles::GPXRoutesDir + "MIOT.gpx", true);

    BOOST_CHECK_THROW( route[-1], std::out_of_range );
    BOOST_CHECK_THROW( route[4], std::out_of_range );
}

/**
  * Check that std::out_of_range is thrown when the index is equal to one of
  * the outer bounds of the correct range (-1 and vector size).
  * Test using a Track.
  **/
BOOST_AUTO_TEST_CASE( out_of_range_outer_bounds_track )
{
    Track track = Track(LogFiles::GPXTracksDir + "M3I6O.gpx", true);

    BOOST_CHECK_THROW( track[-1], std::out_of_range );
    BOOST_CHECK_THROW( track[3], std::out_of_range );
}

BOOST_AUTO_TEST_SUITE_END()

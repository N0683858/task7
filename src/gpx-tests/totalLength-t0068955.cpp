#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "route.h"
#include "track.h"
#include <math.h>

using namespace GPS;

/*

  A B C D E
  F G H I J
  K L M N O
  P Q R S T
  U V W X Y

*/


/*
 * Check if the total length calculated from the GPX files
 * is close to the length calculated in the function.
 */
BOOST_AUTO_TEST_SUITE( route_correct_distance_from_files )

const bool isFileName = true;

// check if the length calculated from the file ABCD.gpx
// is close to the length calculated in the function
BOOST_AUTO_TEST_CASE( ABCD_length )
{
   Route route = Route(LogFiles::GPXRoutesDir + "ABCD.gpx", isFileName);
   BOOST_CHECK_EQUAL(30022.523566455005, route.totalLength());
}

// check if the length calculated from the file NorthYorkMoors.gpx
// is close to the length calculated in the function
BOOST_AUTO_TEST_CASE( NYM_length )
{
   Route route = Route(LogFiles::GPXRoutesDir + "NorthYorkMoors.gpx", isFileName);
   BOOST_CHECK_EQUAL(25204.617211916873, route.totalLength());
}

// check if function can calculate length between 2 consecutive points
// Ex: Distance between A and B
// using the log file AB.gpx
BOOST_AUTO_TEST_CASE( AB_length) {
    Route route = Route(LogFiles::GPXRoutesDir + "AB.gpx", isFileName);
    BOOST_CHECK_CLOSE(10010, route.totalLength(), 2);
}

// check if function can calculate an overlapping route
// Ex: ABA => AB & BA
// This test can also be used to check if length calculated
// by moving right 1 point is equal to the length calculated by moving left 1 point
// Ex: AB (moving right 1 point) =? BA(moving left 1 point)
BOOST_AUTO_TEST_CASE( ABA_length) {
    Route route = Route(LogFiles::GPXRoutesDir + "ABA.gpx", isFileName);
    BOOST_CHECK_CLOSE(20020, route.totalLength(), 2);
}

// checks if length calculated by moving downwards 2 points is equal to
// the length calculated by moving upwards 2 points
// Ex: length of CHM (move downwards 2 points) =? length of MHC (move upwards 2 points)
BOOST_AUTO_TEST_CASE( CHM_MHC_length) {
    Route route1 = Route(LogFiles::GPXRoutesDir + "CHM.gpx", isFileName);
    Route route2 = Route(LogFiles::GPXRoutesDir + "MHC.gpx", isFileName);
    BOOST_CHECK_CLOSE(route1.totalLength(), route2.totalLength(), 2);
}

// checks if length calculated by moving right one point is equal to
// the length calculated my moving downwards one point
// Ex: length of AB (move right 1 ponit) =? length of BG (move downwards 1 point)
// Note: AB.gpx is already tested above so if BG.gpx is equal to AB.gpx then BG.gpx is correct
BOOST_AUTO_TEST_CASE( BG_AB_length) {
    Route route1 = Route(LogFiles::GPXRoutesDir + "AB.gpx", isFileName);
    Route route2 = Route(LogFiles::GPXRoutesDir + "BG.gpx", isFileName);
    BOOST_CHECK_CLOSE(route1.totalLength(), route2.totalLength(), 2);
}

// checks if length calculated by moving upwards 2 points is equal to
// the length calculated by moving right 2 points
// Ex: length of ABC (move right 2 points) =? length of CHM (move downwards 2 points)
BOOST_AUTO_TEST_CASE( ABC_CHM_length) {
    Route route1 = Route(LogFiles::GPXRoutesDir + "ABC.gpx", isFileName);
    Route route2 = Route(LogFiles::GPXRoutesDir + "CHM.gpx", isFileName);
    BOOST_CHECK_CLOSE(route1.totalLength(), route2.totalLength(), 2);
}

// check if function can calculate diagonal lengths
// Ex: length of AGMSY => length of EIMQU
BOOST_AUTO_TEST_CASE( AGMSY_EIMQU_length) {
    Route route1 = Route(LogFiles::GPXRoutesDir + "AGMSY.gpx", isFileName);
    Route route2 = Route(LogFiles::GPXRoutesDir + "EIMQU.gpx", isFileName);
    BOOST_CHECK_CLOSE(route1.totalLength(), route2.totalLength(), 2);
}

// check if pythagoras' theorem works
// using the triangle AFG
// AG(2) =? AF(2) + FG(2)
BOOST_AUTO_TEST_CASE( pythagorean ) {
    Route ag_route = Route(LogFiles::GPXRoutesDir + "AG.gpx", isFileName);
    Route af_route = Route(LogFiles::GPXRoutesDir + "AF.gpx", isFileName);
    Route fg_route = Route(LogFiles::GPXRoutesDir + "FG.gpx", isFileName);
    BOOST_CHECK_CLOSE(pow(ag_route.totalLength(), 2),
                      pow(af_route.totalLength(), 2) + pow(fg_route.totalLength(), 2),
                      2);
}

// check if length calculated by adding by adding 2 routes is equal to the
// length calculated by adding 2 different routes
// where all routes have equal length
// Ex: length of AB + length of RS ?= length of XY + length of OJ
BOOST_AUTO_TEST_CASE( routes_addition) {
    Route ab_route = Route(LogFiles::GPXRoutesDir + "AB.gpx", isFileName);
    Route rs_route = Route(LogFiles::GPXRoutesDir + "RS.gpx", isFileName);
    Route xy_route = Route(LogFiles::GPXRoutesDir + "XY.gpx", isFileName);
    Route oj_route = Route(LogFiles::GPXRoutesDir + "OJ.gpx", isFileName);
    BOOST_CHECK_CLOSE(ab_route.totalLength() + rs_route.totalLength(),
                      xy_route.totalLength() + oj_route.totalLength(),
                      2);
}


// check if length calculated by 2 unsuccessive points is equal to the
// length calculated by another 2 unsuccessive points
// Ex: length of AJ =? length of PY
// where AJ & PY are unsuccessive points
BOOST_AUTO_TEST_CASE( AJ_PY_length) {
    Route route1 = Route(LogFiles::GPXRoutesDir + "AJ.gpx", isFileName);
    Route route2 = Route(LogFiles::GPXRoutesDir + "PY.gpx", isFileName);
    BOOST_CHECK_CLOSE(route1.totalLength(), route2.totalLength(), 2);
}

// check if FG 1/4 FJ
// check if length calculated from the route FG is 1/4 the length of route FJ
BOOST_AUTO_TEST_CASE( FG_FJ_length) {
    Route fg_route = Route(LogFiles::GPXRoutesDir + "FG.gpx", isFileName);
    Route fj_route = Route(LogFiles::GPXRoutesDir + "FJ.gpx", isFileName);
    BOOST_CHECK_CLOSE(0.25 * fj_route.totalLength(),
                      fg_route.totalLength(),
                      2);
}

BOOST_AUTO_TEST_SUITE_END()
/////////////////////////////////////////////////////////////////////////////////////////////

/*
 * checks if function throws exceptions when given incorrect files
 * Such files could be empty strings or non existing files
 */
BOOST_AUTO_TEST_SUITE( incorrect_files)

const bool isFileName = true;

// checks if function throws an invalid argument exception when opening
// NNorthYorkMoors.gpx file (which does not exist)
BOOST_AUTO_TEST_CASE( wrong_file_name )
{
   BOOST_CHECK_THROW(Route route = Route(LogFiles::GPXRoutesDir + "NNorthYorkMoors.gpx", isFileName),
                     std::invalid_argument);
}

// checks if function throws a domain error exception when
// an empty string is given instead of a file name
BOOST_AUTO_TEST_CASE( empty_file_name_param )
{
   BOOST_CHECK_THROW(Route route = Route(LogFiles::GPXRoutesDir + "", isFileName),
                     std::domain_error);
}

BOOST_AUTO_TEST_SUITE_END()
/////////////////////////////////////////////////////////////////////////////////////////////


// checks if function throws exception if the xml contents of the file are incorrect
// such contents could be 'rtept' 'lat' 'lon' 'rte' 'gpx'
BOOST_AUTO_TEST_SUITE( wrong_file_contents )

const bool isFileName = true;

// check if function throws exception if 'rte' is missing from the log file 'ABCD_rte.gpx'
BOOST_AUTO_TEST_CASE( rte_not_found ) {
    BOOST_CHECK_THROW(Route route = Route(LogFiles::GPXRoutesDir + "ABCD_rte.gpx", isFileName),
                      std::domain_error);
}

// check if function throws exception when 'rtept' is missing from the log file 'ABCD_rtept.gpx'
BOOST_AUTO_TEST_CASE( rtept_not_found ) {
    BOOST_CHECK_THROW(Route route = Route(LogFiles::GPXRoutesDir + "ABCD_rtept.gpx", isFileName),
                      std::domain_error);
}

// check if function throws exception when 'lat' is missing from the log file 'ABCD_lat.gpx'
BOOST_AUTO_TEST_CASE( lat_not_found ) {
    BOOST_CHECK_THROW(Route route = Route(LogFiles::GPXRoutesDir + "ABCD_lat.gpx", isFileName),
                      std::domain_error);
}

// check if function throws exception when 'lon' is missing from the log file 'ABCD_lon.gpx'
BOOST_AUTO_TEST_CASE( lon_not_found) {
    BOOST_CHECK_THROW(Route route = Route(LogFiles::GPXRoutesDir + "ABCD_lon.gpx", isFileName),
                      std::domain_error);
}

// check if program throws exception when 'gpx' is missing from the log file 'ABCD_lon.gpx'
BOOST_AUTO_TEST_CASE( gpx_not_found ) {
    BOOST_CHECK_THROW(Route route = Route(LogFiles::GPXRoutesDir + "ABCD_lon.gpx", isFileName),
                      std::domain_error);
}

BOOST_AUTO_TEST_SUITE_END()
/////////////////////////////////////////////////////////////////////////////////////////////

// checks if function can catch incorrect_positions
// Ex: repeated positions or positions that have over range latitude and longitude
BOOST_AUTO_TEST_SUITE( incorrect_positions )

const bool isFileName = true;

// checks if program ignores repeated position (positions that are repeated consecutively).
BOOST_AUTO_TEST_CASE( duplicate_positions ) {
    Route route = Route(LogFiles::GPXRoutesDir + "ABCD_duplicate_positions.gpx", isFileName);
    BOOST_CHECK_EQUAL(30022.523566455005, route.totalLength());
}

BOOST_AUTO_TEST_SUITE_END()


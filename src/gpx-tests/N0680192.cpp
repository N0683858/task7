#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "route.h"
#include "track.h"
#include "position.h"

using namespace GPS;

BOOST_AUTO_TEST_SUITE( findPosistion )

const bool isFileName = true;

/* Check that the correct error is thrown when a point that is not in the list is passed
 * This to check that standard function behaviour
 */
BOOST_AUTO_TEST_CASE( search_for_missing_entry )
{
   Route route = Route(LogFiles::GPXRoutesDir + "N0680192_MissingEntry.gpx", isFileName);
   BOOST_CHECK_THROW( route.findPosition("C"), std::out_of_range );
}

/* Check that the correct error is thrown when a unnamed point is passed in
 * This stops undefinded data errors arising
*/
BOOST_AUTO_TEST_CASE( unnamed_posistion )
{
   Route route = Route(LogFiles::GPXRoutesDir + "N0680192_MissingName.gpx", isFileName);
   BOOST_CHECK_THROW( route.findPosition("H"), std::out_of_range );
}

// Check that the correct error is thrown when passing a lowercase value in when all values are Capitalised
// Ensures complete strings are checked
BOOST_AUTO_TEST_CASE( lowercase_match_error )
{
   Route route = Route(LogFiles::GPXRoutesDir + "N0680192_StringHandling_LowerCase.gpx", isFileName);
   BOOST_CHECK_THROW( route.findPosition("h"), std::out_of_range );
}

// Check that the correct error is thrown when passing a uppercase value in when all values are lowercase
// Same reasoning as previous case
BOOST_AUTO_TEST_CASE( uppercase_match_error )
{
   Route route = Route(LogFiles::GPXRoutesDir + "N0680192_StringHandling_UpperCase.gpx", isFileName);
   BOOST_CHECK_THROW( route.findPosition("H"), std::out_of_range );
}

// Check that a partial match will not make a full match
// Checks for whole string matching and strings are not partially matched
BOOST_AUTO_TEST_CASE( partial_match_error )
{
   Route route = Route(LogFiles::GPXRoutesDir + "N0680192_PartialMatch.gpx", isFileName);
   BOOST_CHECK_THROW( route.findPosition("Capital"), std::out_of_range );
}

//Multiple BOOST_CHECK_EQUAL statements due to Position not supporting == operator
/*Check to see that repeated data is found properly, should find the first instance of a posistion as
 * it should search from the begining of the list and stop after a match is found to stop pointless
 * searching of a list
 */
BOOST_AUTO_TEST_CASE( repeated_data_check )
{
   Route route = Route(LogFiles::GPXRoutesDir + "N0680192_RepeatedData.gpx", isFileName);
   Position repeatedPosition = route[1];
   BOOST_CHECK_EQUAL( route.findPosition("B").latitude(), repeatedPosition.latitude());
   BOOST_CHECK_EQUAL( route.findPosition("B").longitude(), repeatedPosition.longitude());
   BOOST_CHECK_EQUAL( route.findPosition("B").elevation(), repeatedPosition.elevation());
}
//Multiple BOOST_CHECK_EQUAL statements due to Position not supporting == operator
//Check to see if it can handle large data sets and looping works for the last object
BOOST_AUTO_TEST_CASE( large_data_check )
{
   Route route = Route(LogFiles::GPXRoutesDir + "N0680192_LargeDataSet.gpx", isFileName);
   Position repeatedPosition = route[24];
   BOOST_CHECK_EQUAL( route.findPosition("Y").latitude(), repeatedPosition.latitude());
   BOOST_CHECK_EQUAL( route.findPosition("Y").longitude(), repeatedPosition.longitude());
   BOOST_CHECK_EQUAL( route.findPosition("Y").elevation(), repeatedPosition.elevation());
}

//Multiple BOOST_CHECK_EQUAL statements due to Position not supporting == operator
//Check to see if it can handle single data sets and looping works for the first object
BOOST_AUTO_TEST_CASE( single_data_check )
{
   Route route = Route(LogFiles::GPXRoutesDir + "N0680192_SingleDataSet.gpx", isFileName);
   Position repeatedPosition = route[0];
   BOOST_CHECK_EQUAL( route.findPosition("A").latitude(), repeatedPosition.latitude());
   BOOST_CHECK_EQUAL( route.findPosition("A").longitude(), repeatedPosition.longitude());
   BOOST_CHECK_EQUAL( route.findPosition("A").elevation(), repeatedPosition.elevation());
}

//Multiple BOOST_CHECK_EQUAL statements due to Position not supporting == operator
//Check to see if it can handle single data sets and looping works for the first object
BOOST_AUTO_TEST_CASE( small_data_check )
{
   Route route = Route(LogFiles::GPXRoutesDir + "N0680192_SmallDataSet.gpx", isFileName);
   Position repeatedPosition = route[1];
   BOOST_CHECK_EQUAL( route.findPosition("B").latitude(), repeatedPosition.latitude());
   BOOST_CHECK_EQUAL( route.findPosition("B").longitude(), repeatedPosition.longitude());
   BOOST_CHECK_EQUAL( route.findPosition("B").elevation(), repeatedPosition.elevation());
}

BOOST_AUTO_TEST_SUITE_END()


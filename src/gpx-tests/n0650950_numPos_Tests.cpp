#include <boost/test/unit_test.hpp>
#include "logs.h"
#include "route.h"
#include "track.h"
using namespace GPS;

BOOST_AUTO_TEST_SUITE( Route_numPositions )

const bool isFileName = true;
const bool notFileName = false;

//TESTING THAT THE NUMBER OF POSITIONS IS AT LEAST 1 THE MINIMUM
BOOST_AUTO_TEST_CASE(numPositions_atLeastOne_route) {
  Route route = Route(LogFiles::GPXRoutesDir + "N0650950_Routes.gpx", isFileName, 1);
  unsigned int noofpos = route.numPositions();
  BOOST_CHECK( noofpos >= 1 );
}

//TESTING THAT THE NUMBER OF POSITIONS FUNCTION OUTPUTS THE CORRECT TOTAL VALUE
BOOST_AUTO_TEST_CASE(numPositions_correct_route) {
  Route route = Route(LogFiles::GPXRoutesDir + "N0650950_Routes.gpx", isFileName, 5);
  unsigned int noofpos = route.numPositions();
  unsigned int numberWeKnowItShouldBe = 12; 
  BOOST_CHECK_EQUAL(noofpos, numberWeKnowItShouldBe);
}

//TESTING GRANULARITY @ 50 METERS
BOOST_AUTO_TEST_CASE(numPositions_GranCheck50_route) {
  //All the positions are more than 50 metres apart so no positions should be thrown away
  Route route = Route(LogFiles::GPXRoutesDir + "N0650950_Routes.gpx", isFileName, 50);
  unsigned int noofpos = route.numPositions();
  BOOST_CHECK_EQUAL(noofpos, 12);
}

//TESTING GRANULARITY @ 100 METERS
BOOST_AUTO_TEST_CASE(numPositions_GranCheck100_route) {
  //Only 11 of the positions are more than 100 metres apart so 1 position should be thrown away
  Route route = Route(LogFiles::GPXRoutesDir + "N0650950_Routes.gpx", isFileName, 100);
  unsigned int noofpos = route.numPositions();
  BOOST_CHECK_EQUAL(noofpos, 11);
}

//TESTING GRANULARITY @ 150 METERS
BOOST_AUTO_TEST_CASE(numPositions_GranCheck150_route) {
  //Only 10 of the positions are more than 150 metres apart so 2 positions should be thrown away
  Route route = Route(LogFiles::GPXRoutesDir + "N0650950_Routes.gpx", isFileName, 150);
  unsigned int noofpos = route.numPositions();
  BOOST_CHECK_EQUAL(noofpos, 10);
}

//TESTING GRANULARITY @ 200 METERS
BOOST_AUTO_TEST_CASE(numPositions_GranCheck200_route) {
  //Only 8 of the positions are more than 200 metres apart so 4 positions should be thrown away
  Route route = Route(LogFiles::GPXRoutesDir + "N0650950_Routes.gpx", isFileName, 200);
  unsigned int noofpos = route.numPositions();
  BOOST_CHECK_EQUAL(noofpos, 8);
}

//TESTING GRANULARITY @ 250 METERS
BOOST_AUTO_TEST_CASE(numPositions_GranCheck250_route) {
  //Only 7 of the positions are more than 200 metres apart so 5 positions should be thrown away
  Route route = Route(LogFiles::GPXRoutesDir + "N0650950_Routes.gpx", isFileName, 250);
  unsigned int noofpos = route.numPositions();
  BOOST_CHECK_EQUAL(noofpos, 7);
}

//TESTING GRANULARITY @ 1000 METERS
BOOST_AUTO_TEST_CASE(numPositions_GranCheck1000_route) {
  //Only 4 of the positions are more than 200 metres apart so 8 positions should be thrown away
  Route route = Route(LogFiles::GPXRoutesDir + "N0650950_Routes.gpx", isFileName, 1000);
  unsigned int noofpos = route.numPositions();
  BOOST_CHECK_EQUAL(noofpos, 4);
}

//TESTING LOWER EDGE CASE GRANULARITY
BOOST_AUTO_TEST_CASE(numPositions_lowerEdgeCaseGran_route) {
  //The distance between the two points in "route2" is 4.92 metres. The granularity is
  // 4.88 metres so the route class should throw 0 of the positions away
  Route route2 = Route(LogFiles::GPXRoutesDir + "N0650950_Routes2.gpx", isFileName, 4.88);
  unsigned int noofpos = route2.numPositions();
  BOOST_CHECK_EQUAL(noofpos, 2);
}

//TESTING UPPER EDGE CASE GRANULARITY
BOOST_AUTO_TEST_CASE(numPositions_upperEdgeCaseGran_route) {
  //The distance between the two points in "route2" is 4.92 metres. The granularity is
  // 4.96 metres so the route class should throw 1 of the positions away
  Route route2 = Route(LogFiles::GPXRoutesDir + "N0650950_Routes2.gpx", isFileName, 4.96);
  unsigned int noofpos = route2.numPositions();
  BOOST_CHECK_EQUAL(noofpos, 1);
}
BOOST_AUTO_TEST_SUITE_END()

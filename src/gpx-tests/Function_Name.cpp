#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "route.h"
#include "track.h"

using namespace GPS;

BOOST_AUTO_TEST_SUITE(<FileName>_<FunctionName>)

const bool isFileName = true;

// Check that the name is correct for a GPX route containing a <name> element within <rte>.
BOOST_AUTO_TEST_CASE(name_present_route)
{
	Route route = Route(LogFiles::GPXRoutesDir + "ABCD.gpx", isFileName);
	BOOST_CHECK_EQUAL(route.name(), "ABCD");
}

// Check that the name is correct for a GPX track containing a <name> element within <trk>.
BOOST_AUTO_TEST_CASE(name_present_track)
{
	Track track = Track(LogFiles::GPXTracksDir + "A1B3C.gpx", isFileName);
	BOOST_CHECK_EQUAL(track.name(), "A1B3C");
}

// Check that the name is correct for a GPX route without a <name> element within <rte>.
BOOST_AUTO_TEST_CASE(name_absent)
{
	Route route = Route(LogFiles::GPXRoutesDir + "NorthYorkMoors.gpx", isFileName);
	BOOST_CHECK_EQUAL(route.name(), "Unnamed Route");
}

BOOST_AUTO_TEST_SUITE_END()

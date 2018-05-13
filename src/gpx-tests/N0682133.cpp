#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "route.h"
#include "track.h"
#include "position.h"

using namespace GPS;

BOOST_AUTO_TEST_SUITE( findPos)

const bool isFileName = true;


BOOST_AUTO_TEST_CASE( LongRouteTest )
{
   Route route = Route(LogFiles::GPXRoutesDir + "LongRoute.gpx", isFileName);
   BOOST_CHECK_THROW( route.findPosition("Y"), std::out_of_range );
}

BOOST_AUTO_TEST_CASE( SingleValueCheck )
{
   Route route = Route(LogFiles::GPXRoutesDir + "SingleValueCheck.gpx", isFileName);
   BOOST_CHECK_THROW( route.findPosition("A"), std::out_of_range );
}

BOOST_AUTO_TEST_CASE( NotOnRoute )
{
   Route route = Route(LogFiles::GPXRoutesDir + "NotOnRoute.gpx", isFileName);
   BOOST_CHECK_THROW( route.findPosition("M"), std::out_of_range );
}

BOOST_AUTO_TEST_SUITE_END()




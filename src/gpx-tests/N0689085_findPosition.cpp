#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "route.h"
#include "track.h"
#include "position.h"

using namespace GPS;

BOOST_AUTO_TEST_SUITE (Route_FindPosition)

const bool isFileName = true;

//-----------------------------------------------

//Test1, CheckForPosition,
//"N" is not within this gpx file, meaning it must throw to be correct.
BOOST_AUTO_TEST_CASE( WrongPosition )
{
   Route route = Route(LogFiles::GPXRoutesDir + "N0689085Position.gpx", isFileName);
   BOOST_CHECK_THROW( route.findPosition("N"), std::out_of_range );
}

//-----------------------------------------------

//Test2, CheckForUppercase,
//All the positions are lowercase meaning "L" should not pass.
BOOST_AUTO_TEST_CASE( UppercaseMatch )
{
   Route route = Route(LogFiles::GPXRoutesDir + "N0689085Uppercase.gpx", isFileName);
   BOOST_CHECK_THROW( route.findPosition("L"), std::out_of_range );
}

//-----------------------------------------------

//Test3, CheckForLowercase,
//All the positions are Uppercase meaning "l" should not pass.
BOOST_AUTO_TEST_CASE( LowercaseMatch )
{
   Route route = Route(LogFiles::GPXRoutesDir + "N0689085Lowercase.gpx", isFileName);
   BOOST_CHECK_THROW( route.findPosition("l"), std::out_of_range );
}

BOOST_AUTO_TEST_SUITE_END()

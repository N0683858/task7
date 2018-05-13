#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "route.h"
#include "track.h"

// The design structure of my test suite is to test every possible option for the direction of routes, for example:
// - a route where the elevation increases
// - a route where the elevation decreases
// - a route where the elevation is stationary
// - a route where the elevation increases and then decreases
// - a route where the elevation decreases and then increases
// - a route where there is only one point meaning an invalid argument should be thrown
// - a route where the elevation does not change through oyt the route which lead to a flat surface route

//how the check value hasve been worked out:
// in a three dimension where the longitude and latitude are the vertical axies and the elevation is the horizontal axie
// by using pythagoras rule a^2 = b^2 + c^2
// where ( a ) is the gradient
//       ( b ) is the difference between the elevation of two point
//       ( c ) is the  distent between two point using the Law of haversines using the horizantal axies
// the gardient will be zero if the (b) is equal to zero



using namespace GPS;

BOOST_AUTO_TEST_SUITE( Route_MinGradient_n0719479 )

const bool isFileName = true;

// uphill route AGM:
// M is Pontianak with Position(0,109.322134,0) the vertical, horizontal units for this grid is 10 and 120000
// as the route increases, the smallest gradient should be the smallest positive value between them
BOOST_AUTO_TEST_CASE( uphill_route )
{
   Route route = Route(LogFiles::GPXRoutesDir + "going_up_a_hill_route_n0719479"+".gpx", isFileName);
   BOOST_CHECK_CLOSE( route.minGradient(), 169625, 0.1);
}

// downhill route MSY:
// M is citycampus with Position(52.9581383,-1.1542364,53) the vertical, horizontal units for this grid is 10 and 120000
// as the route decreases, the smallest gradient should be the biggest negative value between them
BOOST_AUTO_TEST_CASE( downhill_route )
{
   Route route = Route(LogFiles::GPXRoutesDir + "going_down_a_hill_route_n0719479"+".gpx", isFileName);
   BOOST_CHECK_CLOSE( route.minGradient(), -172816, 0.1 );
}

// uphill then downhill route AGMX:
// M is citycampus with Position(52.9581383,-1.1542364,53) the vertical, horizontal units for this grid is 10 and 120000
// as the route increases then decreases, the smallest gradient should be the biggest negative value between them
BOOST_AUTO_TEST_CASE( up_down_hill_route )
{
   Route route = Route(LogFiles::GPXRoutesDir + "going_up_down_hill_route_n0719479"+".gpx", isFileName);
   BOOST_CHECK_CLOSE( route.minGradient(), -269700, 0.1);
}

// downhill then uphill route MDI:
// M is Pontianak with Position(0,109.322134,0) the vertical, horizontal units for this grid is 10 and 120000
// as the route decreases then increases, the smallest gradient should be the biggest negative value between them
BOOST_AUTO_TEST_CASE( down_up_hill_route )
{
   Route route = Route(LogFiles::GPXRoutesDir + "going_down_up_hill_route_n0719479"+".gpx", isFileName);
   BOOST_CHECK_CLOSE( route.minGradient(), -268,376, 0.1 );
}

// route containing only 1 point:
// as there is only one point and the gradient cannot be calculated, an invalid arugment should be thrown
BOOST_AUTO_TEST_CASE( one_point_location )
{
   Route route = Route(LogFiles::GPXRoutesDir + "one_point_location_n0719479"+".gpx", isFileName);
   BOOST_CHECK_THROW( route.minGradient() , std::invalid_argument );
}

//flat route LQRS:
// M is Pontianak with Position(0,109.322134,0) the vertical, horizontal units for this grid is 10 and 120000
// as the route is flat, the gradient should be zero
BOOST_AUTO_TEST_CASE( flat_surface_route )
{
   Route route = Route(LogFiles::GPXRoutesDir + "flat_route_n0719479"+".gpx", isFileName);
   BOOST_CHECK_EQUAL( route.minGradient(), 0 );
}
BOOST_AUTO_TEST_SUITE_END()

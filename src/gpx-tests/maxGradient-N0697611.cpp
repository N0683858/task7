#include <boost/test/unit_test.hpp>


#include "geometry.h"
#include "logs.h"
#include "route.h"

using namespace GPS;

BOOST_AUTO_TEST_SUITE( Route_maxGradient_N0697611 )

const bool isFileName = true;


BOOST_AUTO_TEST_CASE( elev_zero_throughout )//checks that the output is 0 if all elevations are 0
{
   Route route = Route(LogFiles::GPXRoutesDir + "ABCD.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.maxGradient(), 0 );
}

BOOST_AUTO_TEST_CASE( One_Point )//checks that the output is 0 when there is only 1 position
{
   Route route = Route(LogFiles::GPXRoutesDir + "N0697611_M_OnePoint.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.maxGradient(), 0 );
}


BOOST_AUTO_TEST_CASE(  typical_flat)//Checks that a flat route still returns 0 at an elevation other than 0
{
Route route = Route(LogFiles::GPXRoutesDir + "N0697611_ACE_CliftonCampus.gpx", isFileName);

BOOST_CHECK_CLOSE(route.maxGradient(), 0,0.15) ;

}


BOOST_AUTO_TEST_CASE( typical_uphill)//Checks that a correct uphill gradient is calculated
{
Route route = Route(LogFiles::GPXRoutesDir + "N0697611_CHM_CliftonCampus.gpx", isFileName);

BOOST_CHECK_CLOSE(route.maxGradient(), radToDeg(atan2(100,1000)),0.15) ;

}



BOOST_AUTO_TEST_CASE(  typical_downhill)//Checks that a correct downhill gradient is calculated
{
Route route = Route(LogFiles::GPXRoutesDir + "N0697611_MRW_CliftonCampus.gpx", isFileName);

BOOST_CHECK_CLOSE(route.maxGradient(), radToDeg(atan2(-100,1000)),0.15) ;

}

BOOST_AUTO_TEST_CASE( typical_uturn)//Checks that if two gradients of equal magnitude, but one positive and one negative, the positive one is the one returned
{
Route route = Route(LogFiles::GPXRoutesDir + "N0697611_JIGQST_CliftonCampus.gpx", isFileName);

BOOST_CHECK_CLOSE(route.maxGradient(), radToDeg(atan2(100,1000)),0.15) ;

}


//
BOOST_AUTO_TEST_CASE( Flat_near_equator)//Checks that 0 is returned for a flat route
{                                         //this test is repeated at the equator
Route route = Route(LogFiles::GPXRoutesDir + "N0697611_ACE_Pontianak.gpx", isFileName);

BOOST_CHECK_CLOSE(route.maxGradient(), 0,0.15) ;

}

BOOST_AUTO_TEST_CASE( Equatorial_uphill)//Checks that a correct uphill gradient is calculated
{                                         //this test is repeated at the equator
Route route = Route(LogFiles::GPXRoutesDir + "N0697611_CHM_Pontianak.gpx", isFileName);

BOOST_CHECK_CLOSE(route.maxGradient(), radToDeg(atan2(100,1000)),0.15) ;

}



BOOST_AUTO_TEST_CASE( Equatorial_downhill)//Checks that a correct downhill gradient is calculated
{                                         //this test is repeated at the equator
Route route = Route(LogFiles::GPXRoutesDir + "N0697611_MRW_Pontianak.gpx", isFileName);

BOOST_CHECK_CLOSE(route.maxGradient(), radToDeg(atan2(-100,1000)),0.15) ;

}

BOOST_AUTO_TEST_CASE( Equatorial_uturn)//Checks that if two gradients of equal magnitude, but one positive and one negative, the positive one is the one returned
{                                       //this test repeats this at the equator
Route route = Route(LogFiles::GPXRoutesDir + "N0697611_JIGQST_Pontianak.gpx", isFileName);

BOOST_CHECK_CLOSE(route.maxGradient(), radToDeg(atan2(100,1000)),0.15) ;

}



//


BOOST_AUTO_TEST_CASE( EquatorialMeridian_uturn)//Checks that if two gradients of equal magnitude, but one positive and one negative, the positive one is the one returned
{                                               //This test repeats this at the equatorial meridian
Route route = Route(LogFiles::GPXRoutesDir + "N0697611_JIGQST_EquatorialMeridian.gpx", isFileName);

BOOST_CHECK_CLOSE(route.maxGradient(), radToDeg(atan2(100,1000)),0.15) ;

}

//

BOOST_AUTO_TEST_CASE( EquatorialAntiMeridian_uturn)//Checks that if two gradients of equal magnitude, but one positive and one negative, the positive one is the one returned
{                                                   //this test repeats this at the equatorial anti meridian
Route route = Route(LogFiles::GPXRoutesDir + "N0697611_JIGQST_EquatorialAntiMeridian.gpx", isFileName);

BOOST_CHECK_CLOSE(route.maxGradient(), radToDeg(atan2(100,1000)),0.15) ;

}



//

BOOST_AUTO_TEST_CASE( Northpole_flat)//Tests a flat route near the north pole
{
Route route = Route(LogFiles::GPXRoutesDir + "N0697611_ACE_NorthPole.gpx", isFileName);

BOOST_CHECK_CLOSE(route.maxGradient(), 0,0.15) ;

}
BOOST_AUTO_TEST_CASE( NorthPole_uphill)//Checks the gradient is accurate when going uphill near the northpole
{
Route route = Route(LogFiles::GPXRoutesDir + "N0697611_CHM_NorthPole.gpx", isFileName);

BOOST_CHECK_CLOSE(route.maxGradient(), radToDeg(atan2(100,1000)),0.15) ;

}



BOOST_AUTO_TEST_CASE( NorthPole_downhill)//Checks the gradient is accurate when going downhill near the northpole
{
Route route = Route(LogFiles::GPXRoutesDir + "N0697611_MRW_NorthPole.gpx", isFileName);

BOOST_CHECK_CLOSE(route.maxGradient(), radToDeg(atan2(-100,1000)),0.15) ;

}


BOOST_AUTO_TEST_CASE( Flat_then_up) //checks that the correct gradient is returned when choosing between 0 and a positive gradient
{
Route route = Route(LogFiles::GPXRoutesDir + "N0697611_VWXS_FlatThenUp.gpx", isFileName);

BOOST_CHECK_CLOSE(route.maxGradient(), radToDeg(atan2(100,1000)),0.15) ;

}

BOOST_AUTO_TEST_CASE( Flat_then_down)//checks that the correct gradient is returned when choosing between 0 and a negative gradient
{
Route route = Route(LogFiles::GPXRoutesDir + "N0697611_GHID_FlatThenDown.gpx", isFileName);

BOOST_CHECK_CLOSE(route.maxGradient(), 0,0.15) ;

}

BOOST_AUTO_TEST_CASE( Steep_up) //checks that an extreme positive gradient is returned correctly
{
Route route = Route(LogFiles::GPXRoutesDir + "N0697611_LM_Steepup.gpx", isFileName);

BOOST_CHECK_CLOSE(route.maxGradient(), radToDeg(atan2(10000000,100)),0.15) ;

}


BOOST_AUTO_TEST_CASE( Steep_down)//checks that an extreme negative gradient is returned correctly
{
Route route = Route(LogFiles::GPXRoutesDir + "N0697611_MN_Steepdown.gpx", isFileName);

BOOST_CHECK_CLOSE(route.maxGradient(), radToDeg(atan2(-10000000,100)),0.15) ;

}



BOOST_AUTO_TEST_SUITE_END()

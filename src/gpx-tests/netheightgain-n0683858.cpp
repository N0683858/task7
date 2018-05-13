#include <boost/test/unit_test.hpp>
#include "logs.h"
#include "route.h"
#include "track.h"

using namespace GPS;


BOOST_AUTO_TEST_SUITE( Net_Height_Gain_N0683858 )

const bool isFileName = true;

/* Test case checks that the net height gain is calcualted correctly when all the vales are negative,
 * to see if the subtraction is done properly*/
BOOST_AUTO_TEST_CASE( AllNegKLM )
{
   Route route = Route(LogFiles::GPXRoutesDir + "All_Neg_KLM_N0683858.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.netHeightGain(), 100  );
}

/*Test case checks that the net height gain is caculated correctly when all the values are positive,
 * makes sure the subtraction is done correctly*/
BOOST_AUTO_TEST_CASE( AllPosMNO )
{
   Route route = Route(LogFiles::GPXRoutesDir + "All_Pos_MNO_N0683858.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.netHeightGain(), 0 );
}
/*Test case checks the subtraction is done properly when the elevation is negative to poisitive*/

BOOST_AUTO_TEST_CASE( NegToPosKLM )
{
   Route route = Route(LogFiles::GPXRoutesDir + "Neg_to_Pos_KLM_N0683858.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.netHeightGain(), 240 );
}
/*Test case checks if the net height gain is calculated correctly when the values are increasing (positive),
 * checks to see if the subtraction is done peroperly with the evlevation increasing*/
BOOST_AUTO_TEST_CASE( PosIncreasingWRM )
{
   Route route = Route(LogFiles::GPXRoutesDir + "Pos_Increasing_WRM_N0683858.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.netHeightGain(), 268 );
}

/*Test case checks the subtraction is done properly when the elevation is poisitive to negative*/
BOOST_AUTO_TEST_CASE( PosToNegMGA )
{
   Route route = Route(LogFiles::GPXRoutesDir + "Pos_to_Neg_N0683858.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.netHeightGain(), 0 );
}
/*Test case checks if the net height gain is calculated correctly when the elevation values are the same,
 * checks to see if the subtraction is done peroperly with the elevation same*/
BOOST_AUTO_TEST_CASE( SameElevationABC )
{
   Route route = Route(LogFiles::GPXRoutesDir + "Same_Elevation_ABC_N0683858.gpx", isFileName);
   BOOST_CHECK_EQUAL( route.netHeightGain(),  0);
}

BOOST_AUTO_TEST_SUITE_END();

#include <boost/test/unit_test.hpp>
#include "logs.h"
#include "route.h"
#include "track.h"

using namespace GPS;

BOOST_AUTO_TEST_SUITE( Track_RateOfAscent_N0687265 )
	
	/*
	 *  Required to create a track object.
	 */
	const bool FileName = true;

	/*  
	 *	Tests a gpx file with a standard elevation and timebetween.
	 *  Also uses negative elevation values to ensure that difference in elevation can handle 
	 *	a difference in both positive and negative values. Also ensures that the correct 
	 *  calculation is carried out (elevation difference / time)
	 */ 
	BOOST_AUTO_TEST_CASE( NormalValues ){
		Track track = Track(LogFiles::GPXTracksDir + "N0687265_NormalValues.gpx", FileName);
		BOOST_CHECK_EQUAL( track.maxRateOfAscent() , 20);
	}

	/*
	 *  Tests a gpx file with a large difference in elevation to ensure the calculated value
	 *  is still correct.
	 */
	BOOST_AUTO_TEST_CASE( LargeElevationValues ){
		Track track = Track(LogFiles::GPXTracksDir + "N0687265_LargeElevationValues.gpx", FileName);
		BOOST_CHECK_EQUAL( track.maxRateOfAscent() , 200);
	}

	/*
	 *  Tests a gpx file with a small difference in elevation to ensure the calculated value
	 *  is still correct. Also checks the precesion of the returned value and checks its within
	 *	1% of the correct value.
	 */
	BOOST_AUTO_TEST_CASE( SmallElevationValues ){
		Track track = Track(LogFiles::GPXTracksDir + "N0687265_SmallElevationValues.gpx", FileName);
		BOOST_CHECK_CLOSE( track.maxRateOfAscent() , 0.02, 1);
	}

	/*
	 *  Tests a gpx file with only descending elevation values and checks that the returned 
	 *  value is 0.
	 */
	BOOST_AUTO_TEST_CASE( DescendingElevationValues ){
		Track track = Track(LogFiles::GPXTracksDir + "N0687265_DescendingElevationValues.gpx", FileName);
		BOOST_CHECK_EQUAL( track.maxRateOfAscent() , 0);
	}

	/*
	 *  Tests a gpx file with no difference in elevation, and checks that the returned 
	 *  value is 0.
	 */
	BOOST_AUTO_TEST_CASE( NoElevationValues ){
		Track track = Track(LogFiles::GPXTracksDir + "N0687265_NoElevationValues.gpx", FileName);
		BOOST_CHECK_EQUAL( track.maxRateOfAscent() , 0);
	}

	/*
	 *  Tests a gpx file with a large time for travel between each point. Checks the precision of the 
	 *  returned value is within 1% of the correct value which is given to a standard 3 decimal places.
	 */
	BOOST_AUTO_TEST_CASE( LongTimeValues ){
		Track track = Track(LogFiles::GPXTracksDir + "N0687265_LongTimeValues.gpx", FileName);
		BOOST_CHECK_CLOSE( track.maxRateOfAscent() , 0.667, 1);
	}

	/*
	 *  Tests a gpx file with a short time for travel between each point, and ensures the calculated value
	 *  is still correct.
	 */
	BOOST_AUTO_TEST_CASE( ShortTimeValues ){
		Track track = Track(LogFiles::GPXTracksDir + "N0687265_ShortTimeValues.gpx", FileName);
		BOOST_CHECK_EQUAL( track.maxRateOfAscent() , 200);
	}

	/*
	 *  Tests a gpx file with a zero time value to ensure that the implementation throws
	 *  an overflow_error before the program tries to divide by 0 and breaks the program.
	 */
	BOOST_AUTO_TEST_CASE( ZeroTimeValues ){
		Track track = Track(LogFiles::GPXTracksDir + "N0687265_ZeroTimeValues.gpx", FileName);
		BOOST_CHECK_THROW( track.maxRateOfAscent() , std::overflow_error);
	}

BOOST_AUTO_TEST_SUITE_END()
#include <boost/test/unit_test.hpp>

#include "logs.h"
#include "route.h"
#include "track.h"	

const bool isFileName = true;
using namespace GPS;

BOOST_AUTO_TEST_SUITE( totalTime_N0702007 )

/*
	Function: Total Time
	
	Returns the difference in seconds between the earliest and latest points.
	gridworld_track uses a timeUnitDuration variable, but I don't think it applies to regular Track calculations, so we'll do these functions in terms of GPX time units.
	
	
	Tests/Considerations & Explanations:
	
        IMPLEMENTATION CONSIDERATIONS:
                Data out of order:
                When passed data is out of order, namely, when time isn't necessarily increasing with each point in a track, it would be reasonable to throw an error; but
                given that the implementation of totalTime could simply find the difference between the first and last points in time, it is simple to implement a function
                that would handle this data correctly.




	CORRECT: 
	
		Regular input:
		Testing correct input ensures the function works as expected.
		
		Regular input, non-zero starting value:
		Ensures the Total Time function isn't assuming the start time is zero
		
		
                Regular input, two points at the same start time:
                Ensures that the code can handle two identical start times

                Only two points at the same time
                Similarly ensures the code can handle the start times being the same as end times

		Correct input, data not ordered correctly by time:
		Though there are arguments for data that isn't ordered being invalid, providing functionality for time going back and forth will help in the case of 
		manually-typed data being slightly incorrect.
		
		The multiple cases for this test I'll cover are:
			Time going backwards
			Latest time out of place (Not first nor last)
			Smallest time out of place (Not first nor last)
			Smallest time immediately before largest time
			Smallest time immediately after largest time
                        Two start points at same time, not at beginning of code
                        Two end points at same time, not at end of code
                        Two start and end points, flipped


		
		Correct input, maximum values for time:
		Maximum time unit given that time is ULL = 18446744073709551615		
		This ensures that the function won't fail given large input values (which could cause errors if the function doesn't allocate a large enough variable)
		
		Correct input, minimum values for inputs (No time taken):
		This test can catch issues with handlng small numbers, such as DIV/0 exceptions
		
		Correct input, large quantity of points:
		Choosing a quantity of points to test is a little difficult, as file size and runtime length may become unacceptably large after a few thousand points. 
		Should this program frequently need to track hundreds of thousands of points, this test should be scaled accordingly.
		For the sake of the other students having to download any file, I'll keep this to using 'TrackMultiplePoints'.
		
		
		
	INCORRECT:
		
		After considering the many ways to incorrectly input time values into the GPX files, a lot of the errors will throw exceptions either at parsing time or 
		be completely undetectable for the function itself.
		
		
		
        OTHER UNIMPLEMENTED TESTS:
		

		Malformatted XML:
		This error would instead be handled by the parser.
		
                Empty track containing no points:
		If there are no points for the track, the parser will throw an error.
		
		
		Negative time values:
		This error is impossible to be detected by the function itself; negative values wouldn't be handled by the XML parser, which through using stull results in an
		integer value with the first bit flipped, exactly the same as a very large positive value.
			
		Wrong type for time:
		Incorrect types would throw an error at 'StringToTime' and would not reach this function.
		
		Incorrect & Correct input, multiple track segments
		The transformation from XML to Route or Track combines all track segments into a single set of data.
		
		Incorrect values for variables other than 'Time'
		Given the functions' purpose doesn't utilise any variables other than 'Time' in the given track, 
		
*/



// Tests for correct, ordered values
BOOST_AUTO_TEST_CASE( totaltime_correct_set1)
{
   Track track = Track(LogFiles::GPXTracksDir + "TrackDuration10.gpx", isFileName);
   BOOST_CHECK_EQUAL( track.totalTime(), 40 );	

}
BOOST_AUTO_TEST_CASE( totaltime_correct_set2)
{
   Track track = Track(LogFiles::GPXTracksDir + "TrackDuration1.gpx", isFileName);
   BOOST_CHECK_EQUAL( track.totalTime(), 3 );	

}

// This test also covers the 'large quantity of points' point to a reasonable standard
BOOST_AUTO_TEST_CASE( totaltime_large_quantity)
{
   Track track = Track(LogFiles::GPXTracksDir + "TrackMultiplePoints.gpx", isFileName);
   BOOST_CHECK_EQUAL( track.totalTime(), 21000 );

}


// Test for disordered first value
BOOST_AUTO_TEST_CASE( totaltime_earliest_disordered)
{
   Track track = Track(LogFiles::GPXTracksDir + "N0702007TrackTimeEarliestOffset.gpx", isFileName);
   BOOST_CHECK_EQUAL( track.totalTime(), 40 );	

}

// Test for disordered last value
BOOST_AUTO_TEST_CASE( totaltime_latest_disordered)
{
   Track track = Track(LogFiles::GPXTracksDir + "N0702007TrackTimeLatestOffset.gpx", isFileName);
   BOOST_CHECK_EQUAL( track.totalTime(), 40 );	
   
}




// Test for time going backwards
BOOST_AUTO_TEST_CASE( totaltime_backwards)
{
   Track track = Track(LogFiles::GPXTracksDir + "N0702007TrackTimeBackwards.gpx", isFileName);
   BOOST_CHECK_EQUAL( track.totalTime(), 60 );	
   
}



// Test for disordered first & last values, first before last
BOOST_AUTO_TEST_CASE( totaltime_disordered_fbl)
{
   Track track = Track(LogFiles::GPXTracksDir + "N0702007TrackTimeFirstBeforeLast.gpx", isFileName);
   BOOST_CHECK_EQUAL( track.totalTime(), 60 );	
   
}


// Test for disordered first & last values, last before first
BOOST_AUTO_TEST_CASE( totaltime_disordered_lbf)
{
   Track track = Track(LogFiles::GPXTracksDir + "N0702007TrackTimeLastBeforeFirst.gpx", isFileName);
   BOOST_CHECK_EQUAL( track.totalTime(), 60 );	
   
}


// Test for largest integer
BOOST_AUTO_TEST_CASE( totaltime_maxull)
{
   Track track = Track(LogFiles::GPXTracksDir + "N0702007TrackTimeLargestPossible.gpx", isFileName);
   BOOST_CHECK_EQUAL( track.totalTime(), 18446744073709551615ull );
   
}

// Tests for duplicate values
BOOST_AUTO_TEST_CASE( totaltime_start_duplicate)
{
   Track track = Track(LogFiles::GPXTracksDir + "N0702007TrackTimeSameValuesStart.gpx", isFileName);
   BOOST_CHECK_EQUAL( track.totalTime(), 40 );
   
}
BOOST_AUTO_TEST_CASE( totaltime_end_duplicate)
{
   Track track = Track(LogFiles::GPXTracksDir + "N0702007TrackTimeSameValuesEnd.gpx", isFileName);
   BOOST_CHECK_EQUAL( track.totalTime(), 40 );
   
}
BOOST_AUTO_TEST_CASE( totaltime_startend_duplicate)
{
   Track track = Track(LogFiles::GPXTracksDir + "N0702007TrackTimeSameValuesStartEnd.gpx", isFileName);
   BOOST_CHECK_EQUAL( track.totalTime(), 40 );
   
}
BOOST_AUTO_TEST_CASE( totaltime_startend_duplicate_disordered)
{
   Track track = Track(LogFiles::GPXTracksDir + "N0702007TrackTimeSameValuesStartEndDisordered.gpx", isFileName);
   BOOST_CHECK_EQUAL( track.totalTime(), 40 );
   
}
BOOST_AUTO_TEST_CASE( totaltime_startend_duplicate_disordered_lbf)
{
   Track track = Track(LogFiles::GPXTracksDir + "N0702007TrackTimeSameValuesStartEndDisorderedEndBeforeStart.gpx", isFileName);
   BOOST_CHECK_EQUAL( track.totalTime(), 40 );
   
}




// Tests for same start & end
BOOST_AUTO_TEST_CASE( totaltime_same_startend)
{
   Track track = Track(LogFiles::GPXTracksDir + "N0702007TrackTimeSameStartEnd.gpx", isFileName);
   BOOST_CHECK_EQUAL( track.totalTime(), 0 );
   
}
BOOST_AUTO_TEST_CASE( totaltime_same_startend_nonzero)
{
   Track track = Track(LogFiles::GPXTracksDir + "N0702007TrackTimeSameStartEndNonzero.gpx", isFileName);
   BOOST_CHECK_EQUAL( track.totalTime(), 0 );
   
}





BOOST_AUTO_TEST_SUITE_END()

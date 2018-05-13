#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE ParseNMEATests
#include <boost/test/unit_test.hpp>

#include <stdexcept>

#include "logs.h"
#include "parseNMEA.h"

using namespace GPS;

/////////////////////////////////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_SUITE( IsValidSentence )

BOOST_AUTO_TEST_CASE( WellFormedSentences )
{
    BOOST_CHECK( isValidSentence("$GPGLL,5425.31,N,107.03,W,82610*69") );
    BOOST_CHECK( isValidSentence("$GPGGA,113922.000,3722.5993,N,00559.2458,W,1,0,,4.0,M,,M,,*40") );
    BOOST_CHECK( isValidSentence("$GPRMC,113922.000,A,3722.5993,N,00559.2458,W,0.000,0.00,150914,,A*62") );
}

BOOST_AUTO_TEST_CASE( IllFormedSentences )
{
    BOOST_CHECK( ! isValidSentence("") );
    BOOST_CHECK( ! isValidSentence("Hello World") );
    BOOST_CHECK( ! isValidSentence("GPGLL,5425.31,N,107.03,W,82610*69") );
    BOOST_CHECK( ! isValidSentence("$GPGLL5425.31,N,107.03,W,82610*69") );
    BOOST_CHECK( ! isValidSentence("$GPGLL,5425.31,N,107.03,W,82610*6") );
    BOOST_CHECK( ! isValidSentence("$GPGLL,5425.31,N,107.03,W,82610*") );
    BOOST_CHECK( ! isValidSentence("$GPGLL,5425.31,N,107.03,W,82610") );
    BOOST_CHECK( ! isValidSentence("$GPGLL,5425.31,N,107.03,W,82610*693") );
    BOOST_CHECK( ! isValidSentence("$GPGLL,5425.31,N,107.03,W,82610*he") );
}

BOOST_AUTO_TEST_CASE( IncorrectChecksum )
{
    BOOST_CHECK( ! isValidSentence("$GPGLL,5425.31,N,107.03,W,82610*24") );
    BOOST_CHECK( ! isValidSentence("$GPGGA,113922.000,3722.5993,N,00559.2458,W,1,0,,4.0,M,,M,,*41") );
    BOOST_CHECK( ! isValidSentence("$GPRMC,113922.000,A,3722.5993,N,00559.2458,W,0.000,0.00,150914,,A*97") );
}

BOOST_AUTO_TEST_CASE( ValidChecksumsWithHexDigits )
{
    BOOST_CHECK( isValidSentence("$GPGLL,5430.49,N,106.74,W,163958*5E") );
    BOOST_CHECK( isValidSentence("$GPGLL,5430.49,N,106.74,W,163958*5e") );

    BOOST_CHECK( isValidSentence("$GPGGA,114530.000,3722.6279,N,00559.1566,W,1,0,,1.0,M,,M,,*4E") );
    BOOST_CHECK( isValidSentence("$GPGGA,114530.000,3722.6279,N,00559.1566,W,1,0,,1.0,M,,M,,*4e") );

    BOOST_CHECK( isValidSentence("$GPRMC,115856.000,A,3722.6710,N,00559.3014,W,0.000,0.00,150914,,A*6D") );
    BOOST_CHECK( isValidSentence("$GPRMC,115856.000,A,3722.6710,N,00559.3014,W,0.000,0.00,150914,,A*6d") );
}

BOOST_AUTO_TEST_CASE( InvalidChecksumsWithHexDigits )
{
    BOOST_CHECK( ! isValidSentence("$GPGLL,5430.46,N,106.94,W,164623*7b") );
    BOOST_CHECK( ! isValidSentence("$GPGLL,5430.46,N,106.94,W,164623*4B") );

    BOOST_CHECK( ! isValidSentence("$GPGGA,114530.000,3722.6279,N,00559.1566,W,1,0,,1.0,M,,M,,*8F") );
    BOOST_CHECK( ! isValidSentence("$GPGGA,114530.000,3722.6279,N,00559.1566,W,1,0,,1.0,M,,M,,*2a") );

    BOOST_CHECK( ! isValidSentence("$GPRMC,115856.000,A,3722.6710,N,00559.3014,W,0.000,0.00,150914,,A*6F") );
    BOOST_CHECK( ! isValidSentence("$GPRMC,115856.000,A,3722.6710,N,00559.3014,W,0.000,0.00,150914,,A*1d") );
}

BOOST_AUTO_TEST_SUITE_END()

/////////////////////////////////////////////////////////////////////////////////////////

/* It is bad practice to add things to the standard namespace,
 * but it is the only easy work-around here.
 * TODO: find a better solution.
 */
namespace std
{
    // Define stream insertion to allow use of BOOST_CHECK_EQUAL().
    std::ostream & operator<<(std::ostream & os, const std::vector<string> v)
    {
        os << '{';
        for (auto it = v.begin(); it != v.end(); ++it)
        {
            if (it != v.begin()) os << ',';
            os << *it;
        }
        os << '}';
        return os;
    }
}

BOOST_AUTO_TEST_SUITE( DecomposeSentence )

BOOST_AUTO_TEST_CASE( GLL )
{
    NMEAPair decomposedSentence = decomposeSentence("$GPGLL,5425.31,N,107.03,W,82610*69");

    BOOST_CHECK_EQUAL( decomposedSentence.first , std::string("GPGLL") );

    BOOST_CHECK_EQUAL( decomposedSentence.second , std::vector<std::string>({"5425.31","N","107.03","W","82610"}) );
}

BOOST_AUTO_TEST_CASE( GGA )
{
    NMEAPair decomposedSentence = decomposeSentence("$GPGGA,114530.000,3722.6279,N,00559.1566,W,1,0,,1.0,M,,M,,*4E");

    BOOST_CHECK_EQUAL( decomposedSentence.first , std::string("GPGGA") );

    BOOST_CHECK_EQUAL( decomposedSentence.second , std::vector<std::string>({"114530.000","3722.6279","N","00559.1566","W","1","0","","1.0","M","","M","",""}) );
}

BOOST_AUTO_TEST_CASE( RMC )
{
    NMEAPair decomposedSentence = decomposeSentence("$GPRMC,115856.000,A,3722.6710,N,00559.3014,W,0.000,0.00,150914,,A*6d");

    BOOST_CHECK_EQUAL( decomposedSentence.first , std::string("GPRMC") );

    BOOST_CHECK_EQUAL( decomposedSentence.second , std::vector<std::string>({"115856.000","A","3722.6710","N","00559.3014","W","0.000","0.00","150914","","A"}) );
}

// Unsupported formats should decompose okay, but they will be rejected by extractPosition().
BOOST_AUTO_TEST_CASE( UnsupportedFormat )
{
    NMEAPair decomposedSentence = decomposeSentence("$GPMSS,55,27,318.0,100,*66");

    BOOST_CHECK_EQUAL( decomposedSentence.first , std::string("GPMSS") );

    BOOST_CHECK_EQUAL( decomposedSentence.second , std::vector<std::string>({"55","27","318.0","100",""}) );
}

BOOST_AUTO_TEST_SUITE_END()

/////////////////////////////////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_SUITE( ExtractPosition )

BOOST_AUTO_TEST_CASE( GLL_North_West )
{
    NMEAPair decomposedSentence = { "GPGLL", {"5425.31","N","107.03","W","82610"} };
    Position pos = extractPosition(decomposedSentence);
    BOOST_CHECK_CLOSE( pos.latitude() , 54.4218 , 0.01 );
    BOOST_CHECK_CLOSE( pos.longitude() , -1.1172 , 0.01 );
    BOOST_CHECK_SMALL( pos.elevation() , 0.0001 );
}

BOOST_AUTO_TEST_CASE( GLL_NE )
{
    NMEAPair decomposedSentence = { "GPGLL", {"5425.31","N","107.03","E","82610"} };
    Position pos = extractPosition(decomposedSentence);
    BOOST_CHECK_CLOSE( pos.latitude() , 54.4218 , 0.01 );
    BOOST_CHECK_CLOSE( pos.longitude() , 1.1172 , 0.01 );
    BOOST_CHECK_SMALL( pos.elevation() , 0.0001 );
}

BOOST_AUTO_TEST_CASE( GLL_SE )
{
    NMEAPair decomposedSentence = { "GPGLL", {"5425.31","S","107.03","E","82610"} };
    Position pos = extractPosition(decomposedSentence);
    BOOST_CHECK_CLOSE( pos.latitude() , -54.4218 , 0.01 );
    BOOST_CHECK_CLOSE( pos.longitude() , 1.1172 , 0.01 );
    BOOST_CHECK_SMALL( pos.elevation() , 0.0001 );
}

BOOST_AUTO_TEST_CASE( GLL_SW )
{
    NMEAPair decomposedSentence = { "GPGLL", {"5425.31","S","107.03","W","82610"} };
    Position pos = extractPosition(decomposedSentence);
    BOOST_CHECK_CLOSE( pos.latitude() , -54.4218 , 0.01 );
    BOOST_CHECK_CLOSE( pos.longitude() , -1.1172 , 0.01 );
    BOOST_CHECK_SMALL( pos.elevation() , 0.0001 );
}

BOOST_AUTO_TEST_CASE( RMC_NW )
{
    NMEAPair decomposedSentence = { "GPRMC", {"115856.000","A","3722.6710","N","00559.3014","W","0.000","0.00","150914","","A"} };
    Position pos = extractPosition(decomposedSentence);
    BOOST_CHECK_CLOSE( pos.latitude() , 37.3778 , 0.01 );
    BOOST_CHECK_CLOSE( pos.longitude() , -5.9884 , 0.01 );
    BOOST_CHECK_SMALL( pos.elevation() , 0.0001 );
}

BOOST_AUTO_TEST_CASE( RMC_NE )
{
    NMEAPair decomposedSentence = { "GPRMC", {"115856.000","A","3722.6710","N","00559.3014","E","0.000","0.00","150914","","A"} };
    Position pos = extractPosition(decomposedSentence);
    BOOST_CHECK_CLOSE( pos.latitude() , 37.3778 , 0.01 );
    BOOST_CHECK_CLOSE( pos.longitude() , 5.9884 , 0.01 );
    BOOST_CHECK_SMALL( pos.elevation() , 0.0001 );
}

BOOST_AUTO_TEST_CASE( RMC_SE )
{
    NMEAPair decomposedSentence = { "GPRMC", {"115856.000","A","3722.6710","S","00559.3014","E","0.000","0.00","150914","","A"} };
    Position pos = extractPosition(decomposedSentence);
    BOOST_CHECK_CLOSE( pos.latitude() , -37.3778 , 0.01 );
    BOOST_CHECK_CLOSE( pos.longitude() , 5.9884 , 0.01 );
    BOOST_CHECK_SMALL( pos.elevation() , 0.0001 );
}

BOOST_AUTO_TEST_CASE( RMC_SW )
{
    NMEAPair decomposedSentence = { "GPRMC", {"115856.000","A","3722.6710","S","00559.3014","W","0.000","0.00","150914","","A"} };
    Position pos = extractPosition(decomposedSentence);
    BOOST_CHECK_CLOSE( pos.latitude() , -37.3778 , 0.01 );
    BOOST_CHECK_CLOSE( pos.longitude() , -5.9884 , 0.01 );
    BOOST_CHECK_SMALL( pos.elevation() , 0.0001 );
}

BOOST_AUTO_TEST_CASE( GGA_NW )
{
    NMEAPair decomposedSentence = { "GPGGA", {"170834","4124.8963","N","08151.6838","W","1","05","1.5","280.2","M","-34.0","M","","",""} };
    Position pos = extractPosition(decomposedSentence);
    BOOST_CHECK_CLOSE( pos.latitude() , 41.4149 , 0.01 );
    BOOST_CHECK_CLOSE( pos.longitude() , -81.8614 , 0.01 );
    BOOST_CHECK_CLOSE( pos.elevation() , 280.2 , 0.01 );
}

BOOST_AUTO_TEST_CASE( GGA_NE )
{
    NMEAPair decomposedSentence = { "GPGGA", {"170834","4124.8963","N","08151.6838","E","1","05","1.5","280.2","M","-34.0","M","","",""} };
    Position pos = extractPosition(decomposedSentence);
    BOOST_CHECK_CLOSE( pos.latitude() , 41.4149 , 0.01 );
    BOOST_CHECK_CLOSE( pos.longitude() , 81.8614 , 0.01 );
    BOOST_CHECK_CLOSE( pos.elevation() , 280.2 , 0.01 );
}

BOOST_AUTO_TEST_CASE( GGA_SE )
{
    NMEAPair decomposedSentence = { "GPGGA", {"170834","4124.8963","S","08151.6838","E","1","05","1.5","280.2","M","-34.0","M","","",""} };
    Position pos = extractPosition(decomposedSentence);
    BOOST_CHECK_CLOSE( pos.latitude() , -41.4149 , 0.01 );
    BOOST_CHECK_CLOSE( pos.longitude() , 81.8614 , 0.01 );
    BOOST_CHECK_CLOSE( pos.elevation() , 280.2 , 0.01 );
}

BOOST_AUTO_TEST_CASE( GGA_SW )
{
    NMEAPair decomposedSentence = { "GPGGA", {"170834","4124.8963","S","08151.6838","W","1","05","1.5","280.2","M","-34.0","M","","",""} };
    Position pos = extractPosition(decomposedSentence);
    BOOST_CHECK_CLOSE( pos.latitude() , -41.4149 , 0.01 );
    BOOST_CHECK_CLOSE( pos.longitude() , -81.8614 , 0.01 );
    BOOST_CHECK_CLOSE( pos.elevation() , 280.2 , 0.01 );
}

BOOST_AUTO_TEST_CASE( GGA_NegativeElevation )
{
    NMEAPair decomposedSentence = { "GPGGA", {"170834","4124.8963","S","08151.6838","W","1","05","1.5","-280.2","M","-34.0","M","","",""} };
    Position pos = extractPosition(decomposedSentence);
    BOOST_CHECK_CLOSE( pos.latitude() , -41.4149 , 0.01 );
    BOOST_CHECK_CLOSE( pos.longitude() , -81.8614 , 0.01 );
    BOOST_CHECK_CLOSE( pos.elevation() , -280.2 , 0.01 );
}


BOOST_AUTO_TEST_CASE( UnsupportedFormat )
{
    NMEAPair decomposedSentence = { "GPMSS", {"55","27","318.0","100",""} };
    BOOST_CHECK_THROW( extractPosition(decomposedSentence) , std::invalid_argument );
}

BOOST_AUTO_TEST_CASE( MissingFieldsGLL )
{
    NMEAPair missingN = { "GPGLL", {"5425.31","107.03","E","82610"} };
    BOOST_CHECK_THROW( extractPosition(missingN) , std::invalid_argument );

    NMEAPair missingE = { "GPGLL", {"5425.31","N","107.03","82610"} };
    BOOST_CHECK_THROW( extractPosition(missingE) , std::invalid_argument );

    NMEAPair missingLat = { "GPGLL", {"N","107.03","E","82610"} };
    BOOST_CHECK_THROW( extractPosition(missingLat) , std::invalid_argument );

    NMEAPair missingLon = { "GPGLL", {"5425.31","N","E","82610"} };
    BOOST_CHECK_THROW( extractPosition(missingLon) , std::invalid_argument );
}

BOOST_AUTO_TEST_CASE( MissingFieldsRMC )
{
    NMEAPair missingN = { "GPRMC", {"115856.000","A","3722.6710","00559.3014","E","0.000","0.00","150914","","A"} };
    BOOST_CHECK_THROW( extractPosition(missingN) , std::invalid_argument );

    NMEAPair missingE = { "GPRMC", {"115856.000","A","3722.6710","S","00559.3014","0.000","0.00","150914","","A"} };
    BOOST_CHECK_THROW( extractPosition(missingE) , std::invalid_argument );

    NMEAPair missingLat = { "GPRMC", {"115856.000","A","S","00559.3014","E","0.000","0.00","150914","","A"} };
    BOOST_CHECK_THROW( extractPosition(missingLat) , std::invalid_argument );

    NMEAPair missingLon = { "GPRMC", {"115856.000","A","3722.6710","S","E","0.000","0.00","150914","","A"} };
    BOOST_CHECK_THROW( extractPosition(missingLon) , std::invalid_argument );
}

BOOST_AUTO_TEST_CASE( MissingFieldsGGA )
{
    NMEAPair missingN = { "GPGGA", {"170834","4124.8963","08151.6838","W","1","05","1.5","280.2","M","-34.0","M","","",""} };
    BOOST_CHECK_THROW( extractPosition(missingN) , std::invalid_argument );

    NMEAPair missingW = { "GPGGA", {"170834","4124.8963","N","08151.6838","1","05","1.5","280.2","M","-34.0","M","","",""} };
    BOOST_CHECK_THROW( extractPosition(missingN) , std::invalid_argument );

    NMEAPair missingM = { "GPGGA", {"170834","4124.8963","N","08151.6838","W","1","05","1.5","","",""} };
    BOOST_CHECK_THROW( extractPosition(missingN) , std::invalid_argument );
}

BOOST_AUTO_TEST_CASE( InvalidFieldData )
{
    NMEAPair invalidGLL_N = { "GPGLL", {"three","N","107.03","W","82610"} };
    BOOST_CHECK_THROW( extractPosition(invalidGLL_N) , std::invalid_argument );

    NMEAPair invalidRMC_W = { "GPRMC", {"115856.000","A","3722.6710","N","?&*","W","0.000","0.00","150914","","A"} };
    BOOST_CHECK_THROW( extractPosition(invalidRMC_W) , std::invalid_argument );

    NMEAPair invalidGGA_M = { "GPGGA", {"170834","4124.8963","N","08151.6838","W","1","05","1.5","zero","M","-34.0","M","","",""} };
    BOOST_CHECK_THROW( extractPosition(invalidGGA_M) , std::invalid_argument );
}

BOOST_AUTO_TEST_SUITE_END()

/////////////////////////////////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_SUITE( RouteFromNMEALog )

BOOST_AUTO_TEST_CASE( ValidLog_GLL )
{
    vector<Position> route = routeFromNMEALog(LogFiles::NMEALogsDir + "gll.log");

    BOOST_CHECK_EQUAL( route.size() , 1091 );

    BOOST_CHECK_CLOSE( route[0].latitude() , 54.4220 , 0.01 );
    BOOST_CHECK_CLOSE( route[0].longitude() , -1.1185 , 0.01 );
    BOOST_CHECK_SMALL( route[0].elevation() , 0.0001 );

    BOOST_CHECK_CLOSE( route[1000].latitude() , 54.5053 , 0.01 );
    BOOST_CHECK_CLOSE( route[1000].longitude() , -1.1065 , 0.01 );
    BOOST_CHECK_SMALL( route[1000].elevation() , 0.0001 );
}

BOOST_AUTO_TEST_CASE( CleanLog_GGA_RMC )
{
    vector<Position> route = routeFromNMEALog(LogFiles::NMEALogsDir + "gga_rmc.log");

    BOOST_CHECK_EQUAL( route.size() , 632 );

    BOOST_CHECK_CLOSE( route[0].latitude() , 37.3860 , 0.01 );
    BOOST_CHECK_CLOSE( route[0].longitude() , -5.9930 , 0.01 );
    BOOST_CHECK_CLOSE( route[0].elevation() , 30 , 0.01 );

    BOOST_CHECK_CLOSE( route[500].latitude() , 37.3759 , 0.01 );
    BOOST_CHECK_CLOSE( route[500].longitude() , -5.9873 , 0.01 );
    BOOST_CHECK_CLOSE( route[500].elevation() , 4, 0.01 );
}

BOOST_AUTO_TEST_CASE( AnnotatedLog_GGA_RMC )
{
    vector<Position> route = routeFromNMEALog(LogFiles::NMEALogsDir + "gga_rmc-annotated.log");

    BOOST_CHECK_EQUAL( route.size() , 1826 );

    BOOST_CHECK_CLOSE( route[0].latitude() , 53.3414 , 0.01 );
    BOOST_CHECK_CLOSE( route[0].longitude() , -1.6062 , 0.01 );
    BOOST_CHECK_CLOSE( route[0].elevation() , 395 , 0.01 );

    BOOST_CHECK_CLOSE( route[1500].latitude() , 53.3497 , 0.01 );
    BOOST_CHECK_CLOSE( route[1500].longitude() , -1.6364 , 0.01 );
    BOOST_CHECK_CLOSE( route[1500].elevation() , 186, 0.01 );
}

BOOST_AUTO_TEST_SUITE_END()

/////////////////////////////////////////////////////////////////////////////////////////

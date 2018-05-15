#include <sstream>
#include <fstream>
#include <iostream>
#include <cassert>
#include <cmath>
#include <stdexcept>

#include "geometry.h"
#include "xmlparser.h"
#include "track.h"

using namespace GPS;
using namespace XML::Parser;
using namespace std;

// Note: The implementation should exploit the relationship:
//   totalTime() == restingTime() + travellingTime()

seconds Track::totalTime() const
{
    const bool implemented = false;
    assert(implemented);
}

seconds Track::restingTime() const
{
    const bool implemented = false;
    assert(implemented);
}

seconds Track::travellingTime() const
{
    const bool implemented = false;
    assert(implemented);
}

speed Track::maxSpeed() const
{
    const bool implemented = false;
    assert(implemented);
}

speed Track::averageSpeed(bool includeRests) const
{
    const bool implemented = false;
    assert(implemented);
}

//N0687265
speed Track::maxRateOfAscent() const
{
    const bool implemented = true;
    assert(implemented);

    seconds time;
    metres elevation;
    speed rate, topRate = 0;
    for(unsigned long int i = 1; i < positions.size(); ++i){
        time = arrived[i] - departed[i-1];
        elevation = positions[i].elevation() - positions[i-1].elevation();
        rate = elevation / time;
        if(rate > topRate){
            topRate = rate;
        }
    }
    return topRate;
}

speed Track::maxRateOfDescent() const
{
    const bool implemented = false;
    assert(implemented);
}

Track::Track(std::string source, bool isFileName, metres granularity)
{
    ostringstream reportStream;
    this->granularity = granularity;
    /*
     * If the "source" variable is a filename, the function getGPXFromFile is called to get the apropriate GPX log from the file
     * If not then "source" variable is used as the GPX log.
     */
    string inData = isFileName ? getDataFromFile(source, reportStream) : source;
    //Add this data to track's positions vector in approppriate way, 0 being GPX
    readInPositions(inData,reportStream,0);
    //Calculate and set route length
    calculateRouteLength();
    //Set report to report stream we created
    report = reportStream.str();
}

void Track::checkValidType(string& inData)
{
    if (!elementExists(inData,"trk"))
    {
        throw domain_error("No 'trk' element.");
    }
    inData = getElementContent(getElement(inData, "trk"));
}

void Track::setName(std::string& inData, std::ostringstream& report)
{
    if (elementExists(inData, "name"))
    {
        routeName = getElementContent(getAndEraseElement(inData, "name"));
        report << "Track name is: " << routeName << endl;
    }
}

void Track::addGPXPositions(std::string& inData, std::ostringstream& report)
{
    /*
     * Function called that validates that the top of the GPX data contains gpx and rte, throws if not
     * If name element found in header then the route name is assigned from that
     */
    validateHeader(inData, report);
    //Loops through data and adds positions to route
    string mergedTrkSegs,lat,lon,ele,data;
    seconds startTime, currentTime, timeElapsed;
    Position nextPos(0,0), prevPos(0,0);
    bool first = 1;
    while (elementExists(inData, "trkseg"))
    {
        data = getAndEraseElement(inData, "trkseg");
        data = getElementContent(data);
        getAndEraseElement(data, "name");
        mergedTrkSegs += data;
    }
    if (!mergedTrkSegs.empty())
    {
        inData = mergedTrkSegs;
    }

    if (!elementExists(inData,"trkpt"))
    {
        throw domain_error("No 'trkpt' element.");
    }
    while (elementExists(inData, "trkpt"))
    {
        data = getAndEraseElement(inData, "trkpt");
        if (!attributeExists(data,"lat"))
        {
            throw domain_error("No 'lat' attribute.");
        }
        if (!attributeExists(data,"lon"))
        {
            throw domain_error("No 'lon' attribute.");
        }
        lat = getElementAttribute(data, "lat");
        lon = getElementAttribute(data, "lon");
        data = getElementContent(data);
        if (elementExists(data, "ele"))
        {
            ele = getElementContent(getElement(data, "ele"));
            nextPos = Position(lat,lon,ele);
        }
        else
        {
            nextPos = Position(lat,lon);
        }
        if (!elementExists(data,"time"))
        {
            throw domain_error("No 'time' element.");
        }
        currentTime = stringToTime(getElementContent(getElement(data,"time")));
        if (!first && areSameLocation(nextPos, prevPos))
        {
            // If we're still at the same location, then we haven't departed yet.
            departed.back() = currentTime - startTime;
            report << "Position ignored: " << nextPos.toString() << endl;
            continue;
        }
        positions.push_back(nextPos);
        if (first)
        {
            startTime = currentTime;
        }
        timeElapsed = currentTime - startTime;
        arrived.push_back(timeElapsed);
        departed.push_back(timeElapsed);
        if (first)
        {
            report << "Start position added: " << nextPos.toString() << endl;
            prevPos = positions.back();
            nextPos = positions.back();
            first = 0;
        }
        else
        {
            report << "Position added: " << nextPos.toString() << endl;
            prevPos = nextPos;
            report << " at time: " << to_string(timeElapsed) << endl;
        }
        if (elementExists(data,"name"))
        {
            positionNames.push_back(getElementContent(getElement(data,"name")));
        }
        else
        {
            positionNames.push_back("");
        }
    }
    report << positions.size() << " positions added." << endl;
}

void Track::setGranularity(metres granularity)
{
    bool implemented = false;
    assert(implemented);
}

seconds Track::stringToTime(const std::string & timeStr)
{
    return stoull(timeStr);
}

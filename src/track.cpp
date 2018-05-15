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

    //Test temp
    ifstream load(routeName + "save.txt");
    stringstream ss;
    ss << load.rdbuf();
    load.close();
    if (report != ss.str())
    {
        throw domain_error("Report wrong\n" + report);
    }
    else
    {
        cout <<"Report success"<<endl;
    }
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



    //START
    string mergedTrkSegs,trkseg,lat,lon,ele,name,time,temp,temp2;

    seconds startTime, currentTime, timeElapsed;
    while (elementExists(inData, "trkseg"))
    {
        temp = getAndEraseElement(inData, "trkseg");
        trkseg = getElementContent(temp);
        getAndEraseElement(trkseg, "name");
        mergedTrkSegs += trkseg;
    }
    if (! mergedTrkSegs.empty())
    {
        inData = mergedTrkSegs;
    }
    if (! elementExists(inData,"trkpt"))
    {
        throw domain_error("No 'trkpt' element.");
    }
    temp = getAndEraseElement(inData, "trkpt");
    if (! attributeExists(temp,"lat"))
    {
        throw domain_error("No 'lat' attribute.");
    }

    if (! attributeExists(temp,"lon"))
    {
        throw domain_error("No 'lon' attribute.");
    }
    lat = getElementAttribute(temp, "lat");
    lon = getElementAttribute(temp, "lon");
    temp = getElementContent(temp);

    if (elementExists(temp, "ele"))
    {
        temp2 = getElement(temp, "ele");
        ele = getElementContent(temp2);
        Position startPos = Position(lat,lon,ele);
        positions.push_back(startPos);
        report << "Start position added: " << startPos.toString() << endl;
    }
    else
    {
        Position startPos = Position(lat,lon);
        positions.push_back(startPos);
        report << "Start position added: " << startPos.toString() << endl;
    }
    if (elementExists(temp,"name"))
    {
        temp2 = getElement(temp,"name");
        name = getElementContent(temp2);
    }
    positionNames.push_back(name);
    arrived.push_back(0);
    departed.push_back(0);
    if (! elementExists(temp,"time"))
    {
        throw domain_error("No 'time' element.");
    }
    temp2 = getElement(temp,"time");
    time = getElementContent(temp2);
    startTime = currentTime = stringToTime(time);
    Position prevPos = positions.back(), nextPos = positions.back();
    while (elementExists(inData, "trkpt"))
    {
        temp = getAndEraseElement(inData, "trkpt");
        if (! attributeExists(temp,"lat"))
        {
            throw domain_error("No 'lat' attribute.");
        }
        if (! attributeExists(temp,"lon"))
        {
            throw domain_error("No 'lon' attribute.");
        }
        lat = getElementAttribute(temp, "lat");
        lon = getElementAttribute(temp, "lon");
        temp = getElementContent(temp);
        if (elementExists(temp, "ele"))
        {
            temp2 = getElement(temp, "ele");
            ele = getElementContent(temp2);
            nextPos = Position(lat,lon,ele);
        }
        else
        {
            nextPos = Position(lat,lon);
        }
        if (! elementExists(temp,"time"))
        {
            throw domain_error("No 'time' element.");
        }
        temp2 = getElement(temp,"time");
        time = getElementContent(temp2);
        currentTime = stringToTime(time);
        if (areSameLocation(nextPos, prevPos))
        {
            // If we're still at the same location, then we haven't departed yet.
            departed.back() = currentTime - startTime;
            report << "Position ignored: " << nextPos.toString() << endl;
        }
        else
        {
            if (elementExists(temp,"name"))
            {
                temp2 = getElement(temp,"name");
                name = getElementContent(temp2);
            }
            else
            {
                name = ""; // Fixed bug by adding this.
            }
            positions.push_back(nextPos);
            positionNames.push_back(name);
            timeElapsed = currentTime - startTime;
            arrived.push_back(timeElapsed);
            departed.push_back(timeElapsed);
            report << "Position added: " << nextPos.toString() << endl;
            report << " at time: " << to_string(timeElapsed) << endl;
            prevPos = nextPos;
        }
    }
    report << positions.size() << " positions added." << endl;
    //END
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

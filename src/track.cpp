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
    string mergedTrkSegs,trkseg,lat,lon,ele,name,time,temp,temp2;
    metres deltaH,deltaV;
    seconds startTime, currentTime, timeElapsed;
    ostringstream reportStream;
    unsigned int num;
    this->granularity = granularity;

    string GPXData = isFileName ? getGPXFromFile(source, reportStream) : source;

    if (! elementExists(GPXData,"gpx"))
    {
        throw domain_error("No 'gpx' element.");
    }
    temp = getElement(GPXData, "gpx");
    GPXData = getElementContent(temp);
    if (! elementExists(GPXData,"trk"))
    {
        throw domain_error("No 'trk' element.");
    }
    temp = getElement(GPXData, "trk");
    GPXData = getElementContent(temp);
    if (elementExists(GPXData, "name"))
    {
        temp = getAndEraseElement(GPXData, "name");
        routeName = getElementContent(temp);
        reportStream << "Track name is: " << routeName << endl;
    }
    while (elementExists(GPXData, "trkseg"))
    {
        temp = getAndEraseElement(GPXData, "trkseg");
        trkseg = getElementContent(temp);
        getAndEraseElement(trkseg, "name");
        mergedTrkSegs += trkseg;
    }
    if (! mergedTrkSegs.empty())
    {
        GPXData = mergedTrkSegs;
    }
    num = 0;
    if (! elementExists(GPXData,"trkpt"))
    {
        throw domain_error("No 'trkpt' element.");
    }
    temp = getAndEraseElement(GPXData, "trkpt");
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
        reportStream << "Start position added: " << startPos.toString() << endl;
        ++num;
    }
    else
    {
        Position startPos = Position(lat,lon);
        positions.push_back(startPos);
        reportStream << "Start position added: " << startPos.toString() << endl;
        ++num;
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
    while (elementExists(GPXData, "trkpt"))
    {
        temp = getAndEraseElement(GPXData, "trkpt");
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
            reportStream << "Position ignored: " << nextPos.toString() << endl;
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
            reportStream << "Position added: " << nextPos.toString() << endl;
            reportStream << " at time: " << to_string(timeElapsed) << endl;
            ++num;
            prevPos = nextPos;
        }
    }
    reportStream << num << " positions added." << endl;
    routeLength = 0;
    for (unsigned int i = 1; i < num; ++i )
    {
        deltaH = distanceBetween(positions[i-1], positions[i]);
        deltaV = positions[i-1].elevation() - positions[i].elevation();
        routeLength += sqrt(pow(deltaH,2) + pow(deltaV,2));
    }
    report = reportStream.str();


    //Test temp
    ifstream load(routeName + "save.txt");
    stringstream ss;
    ss << load.rdbuf();
    load.close();
    if (report != ss.str())
    {
        throw domain_error("Report wrong");
    }
    else
    {
        cout <<"Report success"<<endl;
    }

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

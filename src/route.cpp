#include <sstream>
#include <fstream>
#include <iostream>
#include <cassert>
#include <cmath>
#include <stdexcept>

#include "xmlparser.h"
#include "geometry.h"
#include "earth.h"
#include "route.h"
#include "position.h"

using namespace GPS;
using namespace XML::Parser;
using namespace std;

string Route::name() const
{
   return routeName.empty() ? "Unnamed Route" : routeName;
}

unsigned int Route::numPositions() const
{
    const bool implemented = true;
    assert(implemented);

    return positions.size();
}

metres Route::totalLength() const
{
    return routeLength;
}

metres Route::netLength() const
{
    const bool implemented = true;
    assert(implemented);



    metres distance = distanceBetween(positions[0],positions.back());
    return distance;
}

metres Route::totalHeightGain() const
{
    metres heightGain = 0;
    if (positions.size() > 1)
    {
        for (unsigned int i = 1; i<positions.size(); ++i)
        {
            if (positions[i].elevation()-positions[i-1].elevation()>0)
            {
                heightGain += positions[i].elevation()-positions[i-1].elevation();
            }
        }
    }
    return heightGain;
}

metres Route::netHeightGain() const
{
    vector<Position>::const_iterator first, last;
    first = positions.begin();
    last =  positions.end() - 1;
    if (last->elevation() - first->elevation() > 0){
        return last->elevation() - first->elevation();
    }
    else{
        return 0;
    }
}

degrees Route::minLatitude() const
{
    const bool implemented = true;
    assert(implemented);
//    degrees minLat = positions[0].latitude();
//    for(unsigned int i = 1; i < positions.length(); i++)
//    {
//        if(positions[i].latitude() < minLat)
//        {
//            minLat = positions[i].latitude();
//        }
//    }
//    return minLat;
    degrees minLat = positions[0].latitude();
    for(unsigned int i = 1; i < positions.size(); i++)
    {
        if(positions[i].latitude() < minLat)
        {
            minLat = positions[i].latitude();
        }
    }
    if (minLat < -90 || minLat > 90)
        throw out_of_range ("out of range");
    return minLat;
}

degrees Route::maxLatitude() const
{
    const bool implemented = true;

    assert(implemented);

    int Maximum = 0;
    for (int i = 0; i < positions.size() ; i++)
    {

        if (positions[i].latitude() > positions[Maximum].latitude()) {
            Maximum = i;
        }

    }

    return positions[Maximum].latitude();
}

degrees Route::minLongitude() const
{
     const bool implemented = false;
    assert(implemented);

}

degrees Route::maxLongitude() const
{
    const bool implemented = true;

    assert(implemented);

    int MaximumIndex = 0;
    for (unsigned int i = 0; i < positions.size() ; i++)
    {

        if ((positions[i].longitude() > 180) || (positions[i].longitude() < -180)){
            throw out_of_range("Not in bounds of long");
        }

        if (positions[i].longitude() > positions[MaximumIndex].longitude()) {
            MaximumIndex = i;
        }

    }

    return positions[MaximumIndex].longitude();
}

metres Route::minElevation() const
{
    degrees minElev = positions[0].elevation();
    for(auto pos : positions){
        if(pos.elevation() < minElev)
            minElev = pos.elevation();
    }
    return minElev;
}

metres Route::maxElevation() const // N0669298
{
    if (positions.size() == 0)
    {
        throw invalid_argument("No positions in provided route");
    }
    degrees maxElev = positions[0].elevation();
    for(auto pos : positions){
        if(pos.elevation() > maxElev)
            maxElev = pos.elevation();
    }
    return maxElev;
}

degrees Route::maxGradient() const
{
    const bool implemented = true;
    assert(implemented);
    //
    if (positions.size()<2) return 0;


    degrees largestGradient;
    degrees testGradient;

    if (distanceBetween(positions[0],positions[1])>0) {
        largestGradient =radToDeg(atan2((positions[1].elevation() - positions[0].elevation()),distanceBetween(positions[1],positions[0])));
        testGradient = largestGradient;

    }

    else {
        if (positions[0].elevation() <positions[1].elevation()){
        largestGradient =90;
        testGradient = 90;}
        else if (positions[0].elevation() >positions[1].elevation())
        {
            largestGradient =-90;
            testGradient = -90;
        }
        else{
            largestGradient =0;
            testGradient = 0;
        }
}
    for(size_t x = 2; x < positions.size(); x++){

        if (distanceBetween(positions[x],positions[x-1])>0){
          testGradient =
                  radToDeg(atan2((positions[x].elevation() - positions[x-1].elevation()),
                  distanceBetween(positions[x],positions[x-1])));
        }
        else if (positions[0].elevation() <positions[1].elevation())
        {
            testGradient = 90;
        }
        else if (positions[0].elevation() >positions[1].elevation())
        {
            testGradient = -90;
        }
        else
        {
            testGradient = 0;
        }


        if(testGradient > largestGradient){
             largestGradient = testGradient;
        }

     }
    return largestGradient;
}

degrees Route::minGradient() const
{
    const bool implemented = true;
    assert(implemented);

    if (positions.size()<2)
    {
        throw invalid_argument("Gradient cannot be worked out when using only one point");
    }

    degrees minGradient;
    degrees temp, deltaH,deltaV;

    deltaH = distanceBetween(positions[0], positions[1]);
    deltaV = positions[0].elevation() - positions[1].elevation();

    minGradient=sqrt(pow(deltaH,2) + pow(deltaV,2));
    if(deltaV==0)
    {
        minGradient=0;
    }
    if (positions[0].elevation() > positions[1].elevation())
    {
        minGradient = -minGradient;
    }
    for (unsigned int i = 2; i < positions.size(); ++i )
    {
        deltaH = distanceBetween(positions[i-1], positions[i]);
        deltaV = positions[i-1].elevation() - positions[i].elevation();
        temp= sqrt(pow(deltaH,2) + pow(deltaV,2));
        if(deltaV==0)
        {
            temp=0;
        }
        if(positions[i-1].elevation() > positions[i].elevation())
        {
            temp = -temp;
        }

        if(temp<minGradient)
        {
            minGradient=temp;
        }
    }
    return minGradient;

}

degrees Route::steepestGradient() const
{
    const bool implemented = false;
    assert(implemented);
}

Position Route::operator[](unsigned int idx) const
{
    return positions.at(idx);
}

Position Route::findPosition(const string & soughtName) const
{
    const bool implemented = false;
    assert(implemented);
}

string Route::findNameOf(const Position & soughtPos) const
{
    const bool implemented = false;
    assert(implemented);
}

unsigned int Route::timesVisited(const string & soughtName) const
{
    const bool implemented = false;
    assert(implemented);
}

unsigned int Route::timesVisited(const Position & soughtPos) const
{
    const bool implemented = false;
    assert(implemented);
}

string Route::buildReport() const
{
    return report;
}

Route::Route(string source, bool isFileName, metres granularity)
{
    ostringstream reportStream;
    this->granularity = granularity;
    /*
     * If the "source" variable is a filename, the function getDataFromFile is called to get the apropriate log from the file
     * If not then "source" variable is used as the log.
     */
    string inData = isFileName ? getDataFromFile(source, reportStream) : source;
    //Add this data to route's positions vector in approppriate way, 0 being GPX
    readInPositions(inData,reportStream,0);
    //Calculate and set route length
    calculateRouteLength();
    //Set report to report stream we created
    report = reportStream.str();
}

string Route::getDataFromFile(string fileName, std::ostringstream& report)
{
    //Takes filename and reads in data from that file
    //Also adds to report stringstream
    ostringstream parserStream;
    ifstream fileIn(fileName);
    string parser;
    if (!fileIn.good())
    {
        throw invalid_argument("Error opening source file '" + fileName + "'.");
    }
    report << "Source file '" << fileName << "' opened okay." << endl;
    while (fileIn.good())
    {
        getline(fileIn, parser);
        parserStream << parser << endl;
    }
    fileIn.close();
    return parserStream.str();
}

void Route::validateHeader(string& inData, ostringstream& report)
{
    //Checks that header of gpx file is okay
    //Checks if rte (can be overriden)
    //Sets name and logs route (can be overriden)
    if (!elementExists(inData,"gpx"))
    {
        throw domain_error("No 'gpx' element.");
    }
    inData = getElementContent(getElement(inData, "gpx"));
    checkValidType(inData);
    setName(inData,report);
}

void Route::addGPXPositions(string& inData, ostringstream& report)
{
    /*
     * Function called that validates that the top of the GPX data contains gpx and rte, throws if not
     * If name element found in header then the route name is assigned from that
     */
    validateHeader(inData, report);
    //Loops through data and adds positions to route
    string lat,lon,ele;
    Position prevPos(0,0), nextPos(0,0);
    bool first = 1;
    if (!elementExists(inData,"rtept"))
    {
        throw domain_error("No 'rtept' element.");
    }
    while (elementExists(inData, "rtept"))
    {
        string data = getAndEraseElement(inData, "rtept");
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
        if (!first && areSameLocation(nextPos, prevPos))
        {
            report << "Position ignored: " << nextPos.toString() << endl;
            continue;
        }
        positions.push_back(nextPos);
        report << "Position added: " << nextPos.toString() << endl;
        if (first)
        {
            prevPos = positions.back();
            nextPos = positions.back();
            first = 0;
        }
        else
        {
            prevPos = nextPos;
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

void Route::calculateRouteLength()
{
    //Function that calculates the length of the route
    routeLength = 0;
    for (unsigned int i = 1; i < positions.size(); ++i )
    {
        metres deltaH = distanceBetween(positions[i-1], positions[i]);
        metres deltaV = positions[i-1].elevation() - positions[i].elevation();
        routeLength += sqrt(pow(deltaH,2) + pow(deltaV,2));
    }
}

void Route::checkValidType(string& inData)
{
    //Checks top of data contains 'rte', can be overriden to 'trk'
    if (!elementExists(inData,"rte"))
    {
        throw domain_error("No 'rte' element.");
    }
    inData = getElementContent(getElement(inData, "rte"));
}

void Route::setName(string& inData, ostringstream& report)
{
    //Sets name, logs setting of route name, can be overriden to track name
    if (elementExists(inData, "name"))
    {
        routeName = getElementContent(getAndEraseElement(inData, "name"));
        report << "Route name is: " << routeName << endl;
    }
}

void Route::readInPositions(string& inData, ostringstream& report, unsigned int dataFormat)
{
    /*
     * Function that adds positions to position vector for GPX data if GPX
     * If another form of data, use different function
     * This provides room for expansion
     */
    switch (dataFormat)
    {
    case 0:
        addGPXPositions(inData, report);
        break;
    default:
        throw runtime_error("Invalid data type chosen");
    }
}

void Route::setGranularity(metres granularity)
{
    bool implemented = false;
    assert(implemented);
}

bool Route::areSameLocation(const Position & p1, const Position & p2) const
{
    return (distanceBetween(p1,p2) < granularity);
}

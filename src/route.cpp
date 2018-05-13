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
using std::endl;
using std::domain_error;
using std::out_of_range;
using std::invalid_argument;
using std::string;
using std::ostringstream;
using std::ifstream;
using std::vector;

using namespace XML::Parser;

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

/*
 * Few things you can change
 * 2. change variable names and add comments to make the code easy to understand
 * 3. add spaces between lines and spread the code out a little where neccessary
 * 4. the code where you "getElement" and "getElementContent" can be coded in the same line. e.g. source = getElementContent(getElement(source, "gpx"))
*/

Route::Route(string source, bool isFileName, metres granularity)
{
    string lat,lon,ele,name,temp;
    metres deltaH,deltaV;
    ostringstream reportStream;
    unsigned int num = 0;
    this->granularity = granularity;
    /*
     * If the "source" variable is a filename, the function getGPXFromFile is called to get the apropriate GPX log from the file
     * If not then "source" variable is used as the GPX log.
     */
    string GPXData = isFileName ? getGPXFromFile(source, reportStream) : source;
    /*
     * Checks to see if the "gpx" element exists in the log file
     * if it doesn't it will throw "domain_error" and an error message
     * if it does, then it will use the "getElement" function to get everything between the "gpx" element tags and store it in temp variable
     * then use the "getElementContent" to get all the content of the log file
     * repeat for the "rte" element
     */
    if (!elementExists(GPXData,"gpx"))
    {
        throw domain_error("No 'gpx' element.");
    }
    GPXData = getElementContent(getElement(GPXData, "gpx"));
    if (!elementExists(GPXData,"rte"))
    {
        throw domain_error("No 'rte' element.");
    }
    GPXData = getElementContent(getElement(GPXData, "rte"));

    if (elementExists(GPXData, "name"))
    {
        routeName = getElementContent(getAndEraseElement(GPXData, "name"));
        reportStream << "Route name is: " << routeName << endl;
    }

    if (! elementExists(GPXData,"rtept")) throw domain_error("No 'rtept' element.");
    temp = getAndEraseElement(GPXData, "rtept");
    if (! attributeExists(temp,"lat")) throw domain_error("No 'lat' attribute.");
    if (! attributeExists(temp,"lon")) throw domain_error("No 'lon' attribute.");
    lat = getElementAttribute(temp, "lat");
    lon = getElementAttribute(temp, "lon");
    temp = getElementContent(temp);
    if (elementExists(temp, "ele")) {
        ele = getElementContent(getElement(temp, "ele"));
        Position startPos = Position(lat,lon,ele);
        positions.push_back(startPos);
        reportStream << "Position added: " << startPos.toString() << endl;
        ++num;
    } else {
        Position startPos = Position(lat,lon);
        positions.push_back(startPos);
        reportStream << "Position added: " << startPos.toString() << endl;
        ++num;
    }
    if (elementExists(temp,"name")) {
        name = getElementContent(getElement(temp,"name"));
    }
    positionNames.push_back(name);
    Position prevPos = positions.back(), nextPos = positions.back();
    while (elementExists(GPXData, "rtept")) {
        temp = getAndEraseElement(GPXData, "rtept");
        if (! attributeExists(temp,"lat")) throw domain_error("No 'lat' attribute.");
        if (! attributeExists(temp,"lon")) throw domain_error("No 'lon' attribute.");
        lat = getElementAttribute(temp, "lat");
        lon = getElementAttribute(temp, "lon");
        temp = getElementContent(temp);
        if (elementExists(temp, "ele")) {
            ele = getElementContent(getElement(temp, "ele"));
            nextPos = Position(lat,lon,ele);
        } else nextPos = Position(lat,lon);
        if (areSameLocation(nextPos, prevPos)) reportStream << "Position ignored: " << nextPos.toString() << endl;
        else {
            if (elementExists(temp,"name")) {
                name = getElementContent(getElement(temp,"name"));
            } else name = ""; // Fixed bug by adding this.
            positions.push_back(nextPos);
            positionNames.push_back(name);
            reportStream << "Position added: " << nextPos.toString() << endl;
            ++num;
            prevPos = nextPos;
        }
    }
    reportStream << num << " positions added." << endl;
    routeLength = 0;
    for (unsigned int i = 1; i < num; ++i ) {
        deltaH = distanceBetween(positions[i-1], positions[i]);
        deltaV = positions[i-1].elevation() - positions[i].elevation();
        routeLength += sqrt(pow(deltaH,2) + pow(deltaV,2));
    }
    report = reportStream.str();
}

string Route::getGPXFromFile(string fileName, ostringstream& report)
{
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

void Route::setGranularity(metres granularity)
{
    bool implemented = false;
    assert(implemented);
}

bool Route::areSameLocation(const Position & p1, const Position & p2) const
{
    return (distanceBetween(p1,p2) < granularity);
}

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

std::string Route::name() const
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
    std::vector<Position>::const_iterator first, last;
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
        throw std::out_of_range ("out of range");
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
            throw std::out_of_range("Not in bounds of long");
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
        throw std::invalid_argument("No positions in provided route");
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
        throw std::invalid_argument("Gradient cannot be worked out when using only one point");
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

Position Route::findPosition(const std::string & soughtName) const
{
    const bool implemented = false;
    assert(implemented);
}

std::string Route::findNameOf(const Position & soughtPos) const
{
    const bool implemented = false;
    assert(implemented);
}

unsigned int Route::timesVisited(const std::string & soughtName) const
{
    const bool implemented = false;
    assert(implemented);
}

unsigned int Route::timesVisited(const Position & soughtPos) const
{
    const bool implemented = false;
    assert(implemented);
}

std::string Route::buildReport() const
{
    return report;
}

/*
 * Few things you can change
 * 1. remove using namespaces
 * 2. change variable names and add comments to make the code easy to understand
 * 3. add spaces between lines and spread the code out a little where neccessary
 * 4. the code where you "getElement" and "getElementContent" can be coded in the same line. e.g. source = getElementContent(getElement(source, "gpx"))
*/

Route::Route(std::string source, bool isFileName, metres granularity)
{
    //using namespace std;
    //using namespace XML::Parser;
    std::string lat,lon,ele,name,temp,temp2;
    metres deltaH,deltaV;
    std::ostringstream oss,oss2;
    unsigned int num = 0;
    this->granularity = granularity;
    /*
     * After checking the "isFileName" boolean is true it checks to see if the log file is open
     * if it's not open, it will thow "invalid_argument" with the error message
     * if it is open, it will loop through the file and add the content to the varible "oss2" output string stream
     * then converts it to a string and stores it in the "source" variable
     */
    if (isFileName){
        std::ifstream fs(source);
        if (! fs.good()) throw std::invalid_argument("Error opening source file '" + source + "'.");
        oss << "Source file '" << source << "' opened okay." << std::endl;
        while (fs.good()) {
            std::getline(fs, temp);
            oss2 << temp << std::endl;
        }
        source = oss2.str();
    }
    /*
     * checks to see if the "gpx" element exists in the log file
     * if it doesn't it will throw "domain_error" and an error message
     * if it does, then it will use the "getElement" function to get everything between the "gpx" element tags and store it in temp variable
     * then use the "getElementContent" to get all the content of the log file
     * repeat for the "rte" element
     */
    if (! XML::Parser::elementExists(source,"gpx")) throw std::domain_error("No 'gpx' element.");
    temp = XML::Parser::getElement(source, "gpx");
    source = XML::Parser::getElementContent(temp);
    if (! XML::Parser::elementExists(source,"rte")) throw std::domain_error("No 'rte' element.");
    temp = XML::Parser::getElement(source, "rte");
    source = XML::Parser::getElementContent(temp);
    /*
     *I kind of get this but not sure how to explain it in detail
     */
    if (XML::Parser::elementExists(source, "name")) {
        temp = XML::Parser::getAndEraseElement(source, "name");
        routeName = XML::Parser::getElementContent(temp);
        oss << "Route name is: " << routeName << std::endl;
    }

    if (! XML::Parser::elementExists(source,"rtept")) throw std::domain_error("No 'rtept' element.");
    temp = XML::Parser::getAndEraseElement(source, "rtept");
    if (! XML::Parser::attributeExists(temp,"lat")) throw std::domain_error("No 'lat' attribute.");
    if (! XML::Parser::attributeExists(temp,"lon")) throw std::domain_error("No 'lon' attribute.");
    lat = XML::Parser::getElementAttribute(temp, "lat");
    lon = XML::Parser::getElementAttribute(temp, "lon");
    temp = XML::Parser::getElementContent(temp);
    if (XML::Parser::elementExists(temp, "ele")) {
        temp2 = XML::Parser::getElement(temp, "ele");
        ele = XML::Parser::getElementContent(temp2);
        Position startPos = Position(lat,lon,ele);
        positions.push_back(startPos);
        oss << "Position added: " << startPos.toString() << std::endl;
        ++num;
    } else {
        Position startPos = Position(lat,lon);
        positions.push_back(startPos);
        oss << "Position added: " << startPos.toString() << std::endl;
        ++num;
    }
    if (XML::Parser::elementExists(temp,"name")) {
        temp2 = XML::Parser::getElement(temp,"name");
        name = XML::Parser::getElementContent(temp2);
    }
    positionNames.push_back(name);
    Position prevPos = positions.back(), nextPos = positions.back();
    while (XML::Parser::elementExists(source, "rtept")) {
        temp = XML::Parser::getAndEraseElement(source, "rtept");
        if (! XML::Parser::attributeExists(temp,"lat")) throw std::domain_error("No 'lat' attribute.");
        if (! XML::Parser::attributeExists(temp,"lon")) throw std::domain_error("No 'lon' attribute.");
        lat = XML::Parser::getElementAttribute(temp, "lat");
        lon = XML::Parser::getElementAttribute(temp, "lon");
        temp = XML::Parser::getElementContent(temp);
        if (XML::Parser::elementExists(temp, "ele")) {
            temp2 = XML::Parser::getElement(temp, "ele");
            ele = XML::Parser::getElementContent(temp2);
            nextPos = Position(lat,lon,ele);
        } else nextPos = Position(lat,lon);
        if (areSameLocation(nextPos, prevPos)) oss << "Position ignored: " << nextPos.toString() << std::endl;
        else {
            if (XML::Parser::elementExists(temp,"name")) {
                temp2 = XML::Parser::getElement(temp,"name");
                name = XML::Parser::getElementContent(temp2);
            } else name = ""; // Fixed bug by adding this.
            positions.push_back(nextPos);
            positionNames.push_back(name);
            oss << "Position added: " << nextPos.toString() << std::endl;
            ++num;
            prevPos = nextPos;
        }
    }
    oss << num << " positions added." << std::endl;
    routeLength = 0;
    for (unsigned int i = 1; i < num; ++i ) {
        deltaH = distanceBetween(positions[i-1], positions[i]);
        deltaV = positions[i-1].elevation() - positions[i].elevation();
        routeLength += sqrt(pow(deltaH,2) + pow(deltaV,2));
    }
    report = oss.str();
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

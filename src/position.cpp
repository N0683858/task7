#include <cassert>
#include <cmath>
#include <sstream>

#include "geometry.h"
#include "earth.h"
#include "position.h"

namespace GPS
{
  Position::Position(degrees lat, degrees lon, metres ele)
  {
      this->lat = lat;
      this->lon = lon;
      this->ele = ele;
  }

  Position::Position(const string & latStr,
                     const string & lonStr,
                     const string & eleStr)
  {
      lat = std::stod(latStr);
      lon = std::stod(lonStr);
      ele = std::stod(eleStr);
  }

  Position::Position(const string & ddmLatStr, char northing,
                     const string & ddmLonStr, char easting,
                     const string & eleStr)
  {
      assert(northing == 'N' || northing == 'S');
      assert(easting  == 'E' || easting  == 'W');

      degrees absoluteLat = ddmTodd(ddmLatStr);
      degrees absoluteLon = ddmTodd(ddmLonStr);

      // N/S and E/W are used with positive angles.
      assert(absoluteLat >= 0);
      assert(absoluteLon >= 0);

      lat = (northing == 'N') ? absoluteLat : -absoluteLat; // 'S' means negative angle
      lon = (easting  == 'E') ? absoluteLon : -absoluteLon; // 'W' means negative angle
      ele = std::stod(eleStr);
  }

  degrees Position::latitude() const
  {
      return lat;
  }

  degrees Position::longitude() const
  {
      return lon;
  }

  metres Position::elevation() const
  {
      return ele;
  }

  string Position::toString(bool includeElevation) const
  {
      std::ostringstream oss;

      oss << "lat=\""  << lat  << "\"";
      oss << " lon=\"" << lon << "\"";
      if (includeElevation) {
          oss << " ele=\"" << ele << "\"";
      }

      return oss.str();
  }

  degrees ddmTodd(const string & ddmStr)
  {
      double ddm  = std::stod(ddmStr);
      double degs = std::floor(ddm / 100);
      double mins = ddm - 100 * degs;
      return degs + mins / 60.0; // converts minutes (1/60th) to decimal fractions of a degree
  }

  metres distanceBetween(const Position & p1, const Position & p2)
  /*
   * See: http://en.wikipedia.org/wiki/Law_of_haversines
   */
  {
      const radians lat1 = degToRad(p1.latitude());
      const radians lat2 = degToRad(p2.latitude());
      const radians lon1 = degToRad(p1.longitude());
      const radians lon2 = degToRad(p2.longitude());

      double h = sinSqr((lat2-lat1)/2) + cos(lat1)*cos(lat2)*sinSqr((lon2-lon1)/2);
      return 2 * Earth::meanRadius * asin(sqrt(h));
  }
}

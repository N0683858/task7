#ifndef GRIDWORLD_ROUTE_H_120218
#define GRIDWORLD_ROUTE_H_120218

#include <string>

#include "gridworld.h"

namespace GPS
{
  /* GridWorldRoutes are produced from a string of GridWorld::Points,
   * from which a GPX or NMEA log file can be generated.
   * E.g. "ABCD".
   */
  class GridWorldRoute
  {
    public:
      GridWorldRoute(std::string route, // A string of Points.
                     GridWorld gridworld = GridWorld()); // The default GridWorld can be overwritten if desired.

      std::string toGPX(bool embedName = true, // Should a <name> element be included.
                        const std::string& routeName = "") const; // Contents of <name> element.  If empty, defaults to the route string.

      std::string toNMEA() const; // unimplemented

      std::string toString() const;

      static bool isValidRouteString(const std::string&);

    private:
      const std::string routeString;
      const GridWorld gridworld;
  };
}
#endif


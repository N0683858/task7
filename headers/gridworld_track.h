#ifndef GRIDWORLD_TRACK_H_120218
#define GRIDWORLD_TRACK_H_120218

#include <string>
#include <vector>

#include "gridworld.h"

namespace GPS
{
  /* GridWorldTracks are produced from a string of GridWorld::Points,
   * interspersed with time units, from which a GPX or NMEA log file can be generated.
   * E.g. "A1B3C" means that it takes 1 time unit to travel from Point A to Point B,
   *  then 3 time units to travel from Point B to Point C.
   */
  class GridWorldTrack
  {
    public:
      GridWorldTrack(std::string track, // A string containing Points and time units.
                     seconds timeUnitDuration = 10, // Duration (in seconds) of a time unit.
                     seconds absoluteStartTime = 0, // Absolute start time of the Track.
                     GridWorld gridworld = GridWorld()); // The default GridWorld can be overwritten if desired.

      std::string toGPX(seconds logInterval, // Time interval between generated tracking points.
                        bool embedName = true, // Should a <name> element be included.
                        const std::string& trackName = "") const; // Contents of <name> element.  If empty, defaults to the track string.

      std::string toNMEA(seconds logInterval) const; // unimplemented
      std::string toString() const;

      static bool isValidTrackString(const std::string &);
      static std::string routeStringFromTrackString(const std::string &);

    private:
      const std::string trackString;
      const GridWorld gridworld;
      const seconds timeUnitDuration;
      const seconds startTime;

      std::vector<GridWorld::Point> waypoints;
      std::vector<unsigned int> timeUnitsToNextWaypoint;

      void constructWaypoints();
  };
}

#endif


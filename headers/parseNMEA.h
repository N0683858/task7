#ifndef PARSENMEA_H_211217
#define PARSENMEA_H_211217

#include <string>
#include <list>
#include <vector>
#include <utility>

#include "position.h"

namespace GPS
{
  using std::string;
  using std::vector;
  using std::pair;


  /*  The first component of the pair is a NMEA sentence type (excluding the '$').
   *  The second component is a vector of sentence fields, excluding the checksum.
   *  The elements of the vector should not include the separating commas.
   *  E.g. the first component of the pair could be "GPGLL", the first element of the
   *  vector could be "5425.32", and the second element of the vector could be "N".
   */
  using NMEAPair = pair<string, vector<string>>;


  /*  Determine whether the parameter is a valid NMEA sentence, including verifying
   *  the checksum.
   *
   *  A NMEA sentence consists of:
   *    - the prefix "$GP";
   *    - followed by a three-character identifier for the sentence format;
   *    - followed by a sequence of comma-separated fields;
   *    - followed by a '*' character;
   *    - followed by a two-character hexadecimal checksum.
   *
   *  For a NMEA sentence to be valid, the checksum value should equal the byte-wise XOR reduction
   *  of the characters codes of all characters between the '$' and the '*'.
   */
  bool isValidSentence(const string &);


  /*  Pre-condition: the parameter is a valid NMEA sentence.
   *  Decomposes the sentence into the sentence type and the individual fields.
   *  The checksum is discarded.
   */
  NMEAPair decomposeSentence(const string & nmeaSentence);


  /*  Computes a Position from a NMEAPair.
   *  For ill-formed or unsupported sentence types, throws a std::invalid_argument exception.
   */
  Position extractPosition(const NMEAPair &);


  /*  Pre-condition: The parameter is the filepath of a file containing NMEA sentences
   *  (one per line).
   *  Reads the file, and returns a vector of Positions extracted from the sentences.
   *  Blank lines or invalid sentences are ignored.
   */
  vector<Position> routeFromNMEALog(const string & filepath);
}

#endif

#ifndef TRIP_H
#define TRIP_H

#include <QVector>

/**
 * @brief The Location class
 * This class represents a location, with the location ID which is the key
 * in the SQL database and the distances from this location to every
 * other location. The index of the vector holding distances matches the ID
 * of the location that distance is to.
 *
 * @author Ethan Slattery
 * @date 1-March-2016
 */
class Location {
public:
  /*** CONSTRUCTOR AND DESTRUCTOR ***/
  // Constructor
  Location(int id, QVector<float> distances);
  // Destructor
  ~Location();

  /*** UTILITY METHODS ***/
  // Returns the distance to the location with the given ID from THIS location
  float DistanceTo(int id) const;

private:
  int id_;                    //< ID (key) for THIS location
  QVector<float> distances_;  //< Vector of distances from THIS location to all others, vector index = location ID
//  QVector<int> menu_;         //< Vector of menu items for later use. Would store the # of items purchased of each index, not what those items are
};

/**
 * @brief The Trip class
 * This class represents a trip. It stores a vector of all locatios
 * as well as an ordered vector of the trip to take. The main method allows
 * for the finding of the shortest route between locations in the trip vector.
 *
 * @author Ethan Slattery
 * @date 1-March-2016
 */
class Trip {
public:
  /*** CONSTRUCTOR AND DESTRUCTOR ***/
  // Constructor
  Trip(QVector<Location> locations);
  // Destructor
  ~Trip();

  /*** UTILITY METHODS ***/
  // Resets the locations vector in case an update is needed
  void setLocations(QVector<Location> locations);
  // Given a list of locations to visit, find the shortest route to all locations
  QVector<int> findRoute(QVector<int> locations) const;

private:
  int distance_;                //< Distance of the shortest trip
  QVector<int> trip_;           //< An ordered vector of locations to visit
  QVector<Location> locations_; //< A vector of all locations
};

#endif // TRIP_H

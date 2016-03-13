#ifndef LOCATION_H
#define LOCATION_H

#include <QDebug>
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
  // Default Constructor
  Location() : id_(-1) {}
  // Constructor - Sets The Data
  Location(int id, QVector<double> distances) : id_(id), distances_(distances) {}

  /*** UTILITY METHODS ***/
  // Returns the ID (db key) of THIS location
  int id() const { return id_; }
  // Returns the distance to the location with the given ID from THIS location
  float DistanceTo(int id) const { return distances_[id]; }
  // Returns the ID of the closest location to this one
  int closest(QVector<int> locIDs) const;

private:
  int id_;                     //< ID (key) for THIS location
  QVector<double> distances_;  //< Vector of distances from THIS location to all others, vector index = location ID
//  QVector<int> menu_;         //< Vector of menu items for later use. Would store the # of items purchased of each index, not what those items are
};

#endif // LOCATION_H

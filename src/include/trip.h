#ifndef TRIP_H
#define TRIP_H

#include <QVector>
#include <QString>
#include <QTextStream>
#include <QDebug>
#include <algorithm>
#include "location.h"

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

  /*** UTILITY METHODS ***/
  // Resets the locations vector in case an update is needed
  void setLocations(QVector<Location> locations);
  // Given a list of locations to visit, find the shortest route to all locations
  QVector<int> findRoute(QVector<int> idList);

  /*** GET 'EM METHODS ***/
  // Get the trip stored in the class
  QVector<int> getRoute() const { return *trip_; }
  // Get the distance stored in the class
  int getDistance() const { return distance_; }
  // Print the trip stored in the class
  QString printTrip() const;

private:
  int distance_;                //< Distance of the shortest trip
  QVector<int> *trip_;           //< An ordered vector of locations to visit
  QVector<Location> locations_; //< A vector of all locations
};

#endif // TRIP_H

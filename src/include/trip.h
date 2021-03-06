#ifndef TRIP_H
#define TRIP_H

#include <QVector>
#include <QString>
#include <QDebug>
#include <algorithm>
#include "database.h"
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
  Trip(Database *db);

  /*** UTILITY METHODS ***/
  // Resets the locations vector in case an update is needed
  void refreshLocations(Database *db);
  // Resets the trip distance and trip
  void resetTripCalc();

  /*** GET 'EM METHODS ***/
  /// Get the trip stored in the class, returns a nullptr if no route has been calculated
  QVector<int> getRoute() const { return *trip_; }
  // Gets the location id of the stop in the route given by n. returns -1 if route is empty
  int getStop(const int &n) const;
  // Gets the number of stops in the calculated route. returns -1 if route is empty
  int routeLength() const;

  /// Get the distance stored in the class, returns -1 if trip is empty
  double getDistance() const { return distance_; }

  // Print the trip stored in the class
  QString printTrip() const;

  /*** ALGORITHM METHODS!! ***/
  // Given a list of locations to visit, finds the shortest route to all locations
  QVector<int> findRouteGreedy(QVector<int> idList, int start = 0, int numVisit = -1);

  // Given a list of locations to visit, find the shortest route to all locations
  QVector<int> findRouteBrute(QVector<int> idList, int start = 0);

  // Find the shortest route to ALL the locations in the current list
  QVector<int> RoundTheWorld(int start = 0, int numVisit = -1);

private:
  double distance_;             //< Distance of the shortest trip
  QVector<int> *trip_;          //< An ordered vector of locations to visit
  QVector<Location> locations_; //< A vector of all locations available
};

#endif // TRIP_H

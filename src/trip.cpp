#include "../include/trip.h"

/**
 * @brief Constructor for the trip class
 * @param [in] Vector of all locations
 */
Trip::Trip(Database *db)
{
  distance_  = -1;
  trip_ = NULL;
  refreshLocations(db);
}

/**
 * @brief Re-initialzies the vector of all locations
 * @param [IN] vector of all the locations
 */
void Trip::refreshLocations(Database *db)
{
  // Get the ids of all the locations in the
  QVector<int> all_ids(db->GetAllRestaurantIds());

  // Reserve size for the biggest ID, which should be in the back
  locations_.resize(all_ids.back());

  // load the location vector
  for(QVector<int>::iterator itr = all_ids.begin(); itr != all_ids.end(); itr++) {
      // Resize vector if needed for saftey, in case IDs were received out of order (+1 since we start at 0)
      if(locations_.size() < *itr+1){
          locations_.resize(*itr+1);
      }
      //insert location into the vector at the proper index
      locations_.replace(*itr, Location(*itr, db->GetRestaurantDistances(*itr)) );
  }
}

/**
 * @brief Resets the calculated distance and route
 */
void Trip::resetTripCalc()
{
  this->distance_ = -1.0;
  delete this->trip_;
    this->trip_ = NULL;
}

/**
 * @brief Gets the location ID of the nth stop in the route
 * @param n [IN] the stop number
 * @return The ID of the nth stop in the route. returns -1 if the route is empty.
 */
int Trip::getStop(const int &n) const
{
    if(trip_ != NULL)
    {
        return trip_->at(n-1);
    }
    else
    {
        return -1;
    }
}

/**
 * @brief Gets the number of stops in the route
 * @return The number of stops in the route. (-1 if the route is empty)
 */
int Trip::routeLength() const
{
    if(trip_ != NULL)
    {
        return trip_->size();
    }
    else
    {
        return -1;
    }
}

/**
 * @brief Finds the shortest route to visit all the location IDs provided
 * This route finding algorithm uses a greedy algorithm that chooses the next
 * location to visit based on distance from the current location. This will not
 * always return the optiumum route.
 * @param idList [IN] A Vector of location IDs to visit
 * @param start [IN] the starting point for the route, any by default
 * @return A vector of location IDs in the order that creates the shortest trip
 */
QVector<int> Trip::findRouteGreedy(QVector<int> idList, int start, int numVisit)
{
  double tempDist = 0; // Temporary distance variable
  QVector<int> route;  // In Order vecotor of locations to return
  int visited = 0;     // The number of locations visited so far!
  int nextStop;        // Temporary storage for next stop to increase readability

  // If default value received for number of locations to visit, visit them all!
  if(numVisit == -1) { numVisit = locations_.size(); }

  // Remove ID of zero if present as well as any optional starting point
  idList.removeAll(0);
  idList.removeAll(start);

  /*** FIND THE SHORTEST ROUTE THROUGH GREEDY-NESS ***/
  // If a first location was given, add its distance and add to route
  // Otherwise just add the distance from saddleback to the closest
  if(start != 0 && visited < numVisit) {
    // Distance from Saddleback to first stop, and add it to the route
    tempDist += locations_.at(0).DistanceTo(start);
    route.push_back(start);
    visited++;
  }
  else if(visited < numVisit){
    // Finds the first stop and then adds the distance and adds ID to route
    // Before removing it from the IDlist and continuing with algorithm
    nextStop = locations_.at(0).closest(idList);
    if(nextStop != -1) {
      tempDist += locations_.at(0).DistanceTo(nextStop);
      route.push_back(nextStop);
      visited++;
      idList.removeAll(nextStop);
    }
  }

  // Find the next closest location and add to route, then remove from idList
  while(!idList.empty() && visited < numVisit) {
//qDebug() << "*** ROUTE IS NOW: " << route << " WITH A DISTANCE OF: " << tempDist;
//qDebug() << "*** IDLIST: " << idList << " NUMVISIT: " << visited;
    nextStop = locations_.at(route.back()).closest(idList);
//qDebug() << "*** NEXT CLOSEST POINT IS: " << nextStop;
    if(nextStop != -1) {
      tempDist += locations_.at(route.back()).DistanceTo(nextStop);
      route.push_back(nextStop);
      visited++;
      idList.removeAll(nextStop);
    }
  }

  qDebug() << "!!! TRIP: " << route << " DISTANCE OF: " << tempDist;
  // Assign the calculated route into the class data
  distance_ = tempDist;
  delete trip_;
  trip_ = new QVector<int>(route);

  return route;
}

/**
 * @brief Finds the shortest route to visit all the location IDs provided
 * @param idList [IN] A Vector of location IDs to visit
 * @param start [IN] the starting point for the route, any by default
 * @return A vector of location IDs in the order that creates the shortest trip
 */
QVector<int> Trip::findRouteBrute(QVector<int> idList, int start)
{
  double tempDist = 0; // Temporary distance variable

  // Remove ID of zero if present as well as any optional starting point
  idList.removeAll(0);
  idList.removeAll(start);
  // Sort the vector to ensure we have lexographically least vector
  std::sort(idList.begin(), idList.end());

  /*** FIND THE SHORTEST ROUTE THROUGH BRUTE FORCE ***/
  do{    
    // If there is an option starting point then remove it from the list
    // and then add its distances to the trip
    if(start != 0) {
      tempDist += locations_[0].DistanceTo(start);
      tempDist += locations_[start].DistanceTo(idList.first());
    }
    else {
      // Add distance from saddleback to the first location
      tempDist += locations_[0].DistanceTo(idList.first());
    }

    // Sum the rest of the distances
    for(int i = 0; i < idList.size()-1; i++){
      tempDist += locations_[idList.at(i)].DistanceTo(idList.at(i+1));
    }

    // If the new route is better save it to the appropriate variables
    if(tempDist < distance_ || distance_ == -1) {
      distance_ = tempDist;
      delete trip_;
      trip_ = new QVector<int>(idList);
    }
    else if(tempDist == distance_) {
      qDebug() << "**** Routes have the same length. THE HUMANITY!!!";
    }
    // Reset the temp distance to 0
    tempDist = 0;

  }while( std::next_permutation(idList.begin(), idList.end()) );

  // Add the optional first stop back onto the front of the list and return
  if(start != 0) {trip_->push_front(start); }
  return *trip_;
}

/**
 * @brief Gets the shortest trip to ALL locations in the current list
 * @return A vector of integers representing the route locations
 */
QVector<int> Trip::RoundTheWorld(int start, int numVisit)
{
  QVector<int> locIds;  //< Vector for holding location IDs

  // create iterator and skip past the first index (index 0)
  QVector<Location>::const_iterator itr = locations_.cbegin();
  itr++;

  //Load up the vector!
  while(itr != locations_.cend()) {
    locIds.push_back(itr->id());
    itr++;
  }
  qDebug() << locIds;
  // Find the route and return it!!
  return findRouteGreedy(locIds, start, numVisit);
}

/**
 * @brief Prints the trip to a string for debugging
 * Probably uneccessary... QVector has an overloaded <<
 *    ....But it isn't as pretty
 * @return A Qstring of the trip for display
 */
QString Trip::printTrip() const
{
  qDebug() << "In PrintTrip()";
  QString output;
  if(trip_->size() != 0){
      QVector<int>::const_iterator itr = trip_->cbegin();
      while(itr != trip_->cend()) {
        output += QString("<%1>").arg(*itr);;
        itr++;
      }
      return output;
  }
  else {
      return "ERROR! VECTOR EMPTY!";
  }
}

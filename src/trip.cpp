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

  // load the location vector
  for(QVector<int>::iterator itr = all_ids.begin(); itr != all_ids.end(); itr++) {
    locations_.append(Location(*itr, db->GetRestaurantDistances(*itr)) );
  }
}

/**
 * @brief Resets the calculated distance and route
 */
void Trip::resetTripCalc()
{
  distance_ = -1;
  delete trip_;
  trip_ = NULL;
}

/**
 * @brief Finds the shortest route to visit all the location IDs provided
 * @param [IN] A Vector of location IDs to visit (must be sorted!)
 * @return A vector of location IDs in the order that creates the shortest trip
 */
QVector<int> Trip::findRoute(QVector<int> idList)
{
  double tempDist = 0; //< Temporary distance variable

  // Sort the vector to ensure we have lexographically least vector
  std::sort(idList.begin(), idList.end());
  // Remove ID of zero if present
  idList.removeAll(0);


  do{
    // Add distance from saddleback to the first location
    tempDist += locations_[0].DistanceTo(idList.first());

    // Sum the rest of the distances
    for(int i = 0; i < idList.size()-1; i++){
      tempDist += locations_[idList.at(i)].DistanceTo(idList.at(i+1));
    }

    // Add distance from last location back to saddleback
    tempDist += locations_[0].DistanceTo(idList.last());

    if(tempDist < distance_ || distance_ == -1) {
      distance_ = tempDist;
      delete trip_;
      trip_ = new QVector<int>(idList);
    }
    else if(tempDist == distance_) {
      qDebug() << "**** Two Routes have the same length. THE HUMANITY!!!";
    }
    tempDist = 0;

  }while( std::next_permutation(idList.begin(), idList.end()) );
  return *trip_;
}

/**
 * @brief Gets the shortest trip to ALL locations in the current list
 * @return A vector of integers representing the route locations
 */
QVector<int> Trip::RoundTheWorld()
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
  // Find the route and return it!!
  return findRoute(locIds);
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

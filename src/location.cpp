#include "include/location.h"

int Location::closest(QVector<int> locIDs) const
{
  if(!locIDs.empty()){
    double tempDist = distances_.at(locIDs.at(0));  // Stores the distance for working
    int index = locIDs.at(0);                       // index of the shortest distance

    for(int i = 1; i < locIDs.size(); i++) {
      if(distances_.at(locIDs.at(i)) < tempDist) {
        tempDist = distances_.at(locIDs.at(i));
        index = locIDs.at(i);
      }//END IF
    }//END FOR LOOP

    return index;
  }
  return -1;
}// END CLOSEST()

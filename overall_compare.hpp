//Short code, will declare and define in one file.
#ifndef OVERALL_COMPARE_HPP
#define OVERALL_COMPARE_HPP

#include "HumanCrew.hpp"
#include "AlienCrew.hpp"
#include "LinkedList.hpp"
// Human comparison function
//O(1), maximum 4 checks. 
inline int overallHumanCompare(const HumanCrew& a, const HumanCrew& b) {
    // MissionAptitude (descending)
    if (a.getMissionAptitude() > b.getMissionAptitude()) return -1;
    if (a.getMissionAptitude() < b.getMissionAptitude()) return 1;
    
    // TrainingScore (descending)
    if (a.getTrainingScore() > b.getTrainingScore()) return -1;
    if (a.getTrainingScore() < b.getTrainingScore()) return 1;
    
    // HomeSector (alphabetical A-Z)
    if (a.getHomeSector() < b.getHomeSector()) return -1;
    if (a.getHomeSector() > b.getHomeSector()) return 1;
    
    return 0;
}
//O(1)
// Alien comparison function  
inline int overallAlienCompare(const AlienCrew& a, const AlienCrew& b) {
    // MissionAptitude (descending)
    if (a.getMissionAptitude() > b.getMissionAptitude()) return -1;
    if (a.getMissionAptitude() < b.getMissionAptitude()) return 1;

    // TrainingScore (descending)
    if (a.getTrainingScore() > b.getTrainingScore()) return -1;
    if (a.getTrainingScore() < b.getTrainingScore()) return 1;

    // Homeworld (alphabetical A-Z)
    if (a.getHomeworld() < b.getHomeworld()) return -1;
    if (a.getHomeworld() > b.getHomeworld()) return 1;

    return 0;
}




#endif
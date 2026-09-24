#ifndef CREW_MERGE_HPP
#define CREW_MERGE_HPP
#include "LinkedList.hpp"
#include "HumanCrew.hpp"
#include "AlienCrew.hpp"
#include <iostream>
using namespace std;


//use in main:
//declare a mergeed list object, display
/*example:
LinkedList<CrewMember*> mergedList = mergeHumanAlienLists(humans, aliens);
displayQualifiedRecruits(mergedList);
*/

// comparison function for merged list
int mergedCompare(const CrewMember* a, const CrewMember* b);

// main merge function
LinkedList<CrewMember*> mergeHumanAlienLists(
    const LinkedList<HumanCrew>& humans,
    const LinkedList<AlienCrew>& aliens);

// display qualified recruits after merge
void displayQualifiedRecruits(const LinkedList<CrewMember*>& mergedList);
void cleanupMergedList(LinkedList<CrewMember*>& mergedList);


//add function protoype so this function in cpp can be used in other file.
std::function<int(CrewMember*, CrewMember*)> getMergedCompare();
#endif
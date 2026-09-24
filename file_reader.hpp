#ifndef FILE_READER_HPP
#define FILE_READER_HPP
#include "LinkedList.hpp"
#include "overall_compare.hpp"
#include <string>
#include "HumanCrew.hpp"
#include "AlienCrew.hpp"
#include "crew_merge.hpp"

using std::vector;
using std::string;

LinkedList<HumanCrew> readHumanCrewFile(const string& filename);
LinkedList<AlienCrew> readAlienCrewFile(const string& filename);

void insertHumanFromUser(LinkedList<HumanCrew>& humans);
void insertAlienFromUser(LinkedList<AlienCrew>& aliens); 
void insertToMergedFromUser(LinkedList<CrewMember*>& mergedList);

#endif
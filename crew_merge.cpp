#include "crew_merge.hpp"

// Comparison for merged list 
int mergedCompare(const CrewMember* a,const CrewMember* b) {
    // Primary: MissionAptitude (descending)
    if (a->getMissionAptitude() > b->getMissionAptitude()) return -1;
    if (a->getMissionAptitude() < b->getMissionAptitude()) return 1;
    
    // Secondary: TrainingScore (descending)  
    if (a->getTrainingScore() > b->getTrainingScore()) return -1;
    if (a->getTrainingScore() < b->getTrainingScore()) return 1;
    
    // Tertiary: Humans before Aliens when scores identical
    if (a->getType() == "Human" && b->getType() == "Alien") return -1;
    if (a->getType() == "Alien" && b->getType() == "Human") return 1;
    
    return 0;
}

// Wrapper function - FIXED
function<int(CrewMember*, CrewMember*)> getMergedCompare() {
    return [](CrewMember* a, CrewMember* b) -> int {
        return mergedCompare(a, b);
    };
}

// Main merge function 
LinkedList<CrewMember*> mergeHumanAlienLists(
    const LinkedList<HumanCrew>& humans,
    const LinkedList<AlienCrew>& aliens) {
    
    LinkedList<CrewMember*> merged;
    
    cout << "=== Merging Human and Alien Crews ===" << endl;
    
    // Add all humans to merged list using O(1) insertion
    Node<HumanCrew>* humanCurrent = humans.getHead();
    int humanCount = 0;
    while (humanCurrent != nullptr) {
        CrewMember* humanPtr = new HumanCrew(humanCurrent->getData());
        merged.insertAtEnd(humanPtr);  // Changed to O(1) insertion
        humanCurrent = humanCurrent->getNext();
        humanCount++;
    }
    cout << "Added " << humanCount << " humans to merged list" << endl;
    
    // Add qualified aliens only (telepathic total >= 15) using O(1) insertion
    Node<AlienCrew>* alienCurrent = aliens.getHead();
    int alienCount = 0;
    int qualifiedAlienCount = 0;
    
    while (alienCurrent != nullptr) {//O(1)
        if (alienCurrent->getData().getTelepathicTest().getTotal() >= 15) {
            CrewMember* alienPtr = new AlienCrew(alienCurrent->getData());
            merged.insertAtEnd(alienPtr);  
            qualifiedAlienCount++;
        }
        alienCurrent = alienCurrent->getNext();
        alienCount++;
    }
    
    // Sort once at the end - O(n log n) 
    merged.sort(getMergedCompare());
    
    cout << "Added " << qualifiedAlienCount << " qualified aliens (out of " 
         << alienCount << " total) to merged list" << endl;
    cout << "Total in merged list: " << merged.getSize() << " crew members" << endl;
    
    return merged;
}

// Display qualified recruits - FIXED memory leak and safer casting
void displayQualifiedRecruits(const LinkedList<CrewMember*>& mergedList) {
    cout << "\n=== Qualified Recruits (All Humans + Aliens with Telepathic Total >= 15) ===" << endl;
    
    if (mergedList.isEmpty()) {
        cout << "No qualified recruits found." << endl;
        return;
    }
    
    Node<CrewMember*>* current = mergedList.getHead();
    int humanCount = 0;
    int alienCount = 0;
    
    while (current != nullptr) {
        CrewMember* crew = current->getData();
        
    
        if (crew->getType() == "Human") {
            humanCount++;
            HumanCrew* human = dynamic_cast<HumanCrew*>(crew);
            if (human) {
                cout << *human << endl;
            }
        } else if (crew->getType() == "Alien") {
            alienCount++;
            AlienCrew* alien = dynamic_cast<AlienCrew*>(crew);
            if (alien) {
                cout << *alien << endl;
            }
        }
        
        current = current->getNext();
    }
    
    cout << "\n=== Summary ===" << endl;
    cout << "Total qualified humans: " << humanCount << endl;
    cout << "Total qualified aliens: " << alienCount << endl;
    cout << "Grand total: " << (humanCount + alienCount) << " qualified recruits" << endl;
}

//cleanup function to prevent memory leak O(n)
void cleanupMergedList(LinkedList<CrewMember*>& mergedList) {
    Node<CrewMember*>* current = mergedList.getHead();
    while (current != nullptr) {
        CrewMember* crew = current->getData();
        delete crew;  
        current = current->getNext();
    }

}
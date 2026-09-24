#include <iostream>
#include <string>
#include <functional>

#include "HumanCrew.hpp"
#include "AlienCrew.hpp"
#include "telepathic_link_test.hpp" // or Telepathic_Link_Test.hpp – match your filename
#include "LinkedList.hpp"
#include "overall_compare.hpp"
#include "crew_merge.hpp"
using namespace std;
#ifndef TESTING_FUNCTIONS_HPP
#define TESTING_FUNCTIONS_HPP

int passedTests = 0;
int failedTests = 0;

bool checkTest(bool condition, const string& testName) {
    if (condition) {
        cout << "[PASSED] " << testName << endl;
        passedTests++;
        return true;
    } else {
        cout << "[FAILED] " << testName << endl;
        failedTests++;
        return false;
    }
}


template<typename T>
bool checkEqual(const T& expected, const T& actual, const string& testName)
{
    if (expected == actual) {
        cout << "[PASSED] " << testName << endl;
        cout<<" Expected and Actual: " << actual << endl;
        passedTests++;
        return true;
    } else {
        cout << "[FAILED] " << testName << endl;
        cout << "  Expected: " << expected << endl;
        cout << "  Actual:   " << actual << endl;
        failedTests++;
        return false;
    }
}

template<typename T, typename Comp>
bool isSorted(const LinkedList<T>& list, Comp comp) {
    auto* current = list.getHead();
    while (current && current->getNext()) {
        const T& a = current->getData();
        const T& b = current->getNext()->getData();
        if (comp(a, b) > 0) return false;
        current = current->getNext();
    }
    return true;
}

void testInsertAndSort(){
    cout<<"\n[a] Testing Insertion and Sorting into HumaanCrew and AlienCrew LinkedLists\n"<<endl;
    LinkedList<HumanCrew> humanList;
    humanList.insertSorted(HumanCrew("John", "Doe", 2.5,85,"Gamma"),overallHumanCompare);
    humanList.insertSorted(HumanCrew("Alice", "Smith", 3.8,90,"Alpha"),overallHumanCompare);
    humanList.insertSorted(HumanCrew("Bob", "Brown", 1.9,75,"Beta"),overallHumanCompare);

    checkEqual(3, humanList.getSize(), "HumanCrew List Size after Insertions");
    checkTest(isSorted(humanList, overallHumanCompare), "HumanCrew List is Sorted after Insertions");

    //check boudarie : equal aptitude and training score

    humanList.insertSorted(HumanCrew("Zara", "White", 2.5,85,"Delta"),overallHumanCompare);
    checkEqual(4, humanList.getSize(), "HumanCrew List Size after Boundary Insertion");
    checkTest(isSorted(humanList, overallHumanCompare), "HumanCrew List is Sorted after Boundary Insertion");

    LinkedList<AlienCrew> alienList;
    TelepathicLinkTest tlt1(8,4,6,5);
    TelepathicLinkTest tlt2(7,5,7,6);
    TelepathicLinkTest tlt3(9,3,5,4);
    TelepathicLinkTest tlt4(8,4,6,5); // same as tlt1 for boundary

    alienList.insertSorted(AlienCrew("Xen", "Zor", 4.0,95,"Altair",tlt1),overallAlienCompare);
    alienList.insertSorted(AlienCrew("Yara", "Vex", 3.5,80,"Orion",tlt2),overallAlienCompare);
    alienList.insertSorted(AlienCrew("Wex", "Wox", 4.5,90,"Novera",tlt3),overallAlienCompare);
    alienList.insertSorted(AlienCrew("Zan", "Kor", 4.0,95,"Mira",tlt4),overallAlienCompare); // boundary

    checkEqual(4, alienList.getSize(), "AlienCrew List Size after Insertions");
    checkTest(isSorted(alienList, overallAlienCompare), "AlienCrew List is Sorted after Insertions");

    //negative test
    alienList.insertSorted(AlienCrew("Bad", "Data", -1,50,"Nowhere",TelepathicLinkTest()),overallAlienCompare);
    checkEqual(5, alienList.getSize(), "AlienCrew List Size after Inserting Negative Training Score");
    checkTest(isSorted(alienList, overallAlienCompare), "AlienCrew List is Sorted after Inserting Negative Training Score");
}


void testSearch()
{
    cout<<"/n[b] Testing Search Functions in HumanCrew and AlienCrew LinkedLists\n"<<endl;
    LinkedList<HumanCrew> humanList;
    HumanCrew h1("Anry", "Doe", 2.5,85,"Gamma");
    HumanCrew h2("Mesii", "Smith", 3.8,90,"Alpha");
    HumanCrew h3("Ronaldo", "Brown", 1.9,72,"Beta");
    HumanCrew h4("Zarol", "White", 2.5,61,"Delta");

    h1.setId(101);
    h2.setId(102);
    h3.setId(103);
    h4.setId(104);

    humanList.insertAtEnd(h1);
    humanList.insertAtEnd(h2);
    humanList.insertAtEnd(h3);
    humanList.insertAtEnd(h4);

    cout<<" HumanCrew List for Search Tests: "<<endl;
    humanList.displayAll();
    cout<<endl;

    Node<HumanCrew>* found = humanList.searchByID(102);
    checkTest(found != nullptr && found->getData().getId() == 102, "Search HumanCrew by Existing ID");
    found = humanList.searchByID(999);
    checkTest(found == nullptr, "Search HumanCrew by Non-Existing ID");
    cout<<endl;

    LinkedList<HumanCrew> scoreRange = humanList.searchByTrainingScore(2.0, 3.0);
    checkEqual(2, scoreRange.getSize(), "Search HumanCrew by Training Score Range");
    cout<<endl;

    LinkedList<HumanCrew> scoreExact = humanList.searchByTrainingScore(3.8, 3.8);
    checkEqual(1, scoreExact.getSize(), "Search HumanCrew by Exact Training Score");
    cout<<endl;

    LinkedList<HumanCrew> scoreOutOfRange = humanList.searchByTrainingScore(5.0, 6.0);
    checkEqual(0, scoreOutOfRange.getSize(), "Search HumanCrew by Out;of-Range Training Score");
    cout<<endl;

    // for aptitude:

    LinkedList<HumanCrew> aptitudeRange = humanList.searchByMissionAptitude(80, 90);
    checkEqual(2, aptitudeRange.getSize(), "Search HumanCrew by Mission Aptitude Range");
    cout<<endl;

    LinkedList<HumanCrew> aptitudeExact = humanList.searchByMissionAptitude(72, 72);
    checkEqual(1, aptitudeExact.getSize(), "Search HumanCrew by Exact Mission Aptitude");
    cout<<endl;

    LinkedList<HumanCrew> aptitudeOutOfRange = humanList.searchByMissionAptitude(95, 100);
    checkEqual(0, aptitudeOutOfRange.getSize(), "Search HumanCrew by Out-of-Range Mission Aptitude");
    cout<<endl;

    //name search

    LinkedList<HumanCrew> nameSearch = humanList.searchByName("Anry", "Doe");
    checkEqual(1, nameSearch.getSize(), "Search HumanCrew by Existing Name");   
    cout<<endl;

    LinkedList<HumanCrew> nameNotFound = humanList.searchByName("Non", "Exist");
    checkEqual(0, nameNotFound.getSize(), "Search HumanCrew by Non-Existing Name");
    cout<<endl;

    // Similar tests for AlienCrew can be added here

}

void deleteTest(){
    cout<<"\n Testing Deletion Functions in HumanCrew and AlienCrew LinkedLists\n"<<endl;
    LinkedList<HumanCrew> humanList;
    HumanCrew h1("Head", "Doe", 2.5,85,"Gamma");
    HumanCrew h2("Middle", "Smith", 3.8,90,"Alpha");
    HumanCrew h3("Tail", "Brown", 1.9,72,"Beta");
    HumanCrew h4("Middle", "Smith", 2.5,61,"Delta"); // duplicate name

    humanList.insertAtEnd(h1);
    humanList.insertAtEnd(h2);
    humanList.insertAtEnd(h3);
    humanList.insertAtEnd(h4);
    checkEqual(4, humanList.getSize(), "HumanCrew List Size before Deletions");

    cout<<" HumanCrew List before Deletions: "<<endl;
    humanList.displayAll();
    cout<<endl;

    humanList.deleteByName("Head", "Doe");
    checkEqual(3, humanList.getSize(), "HumanCrew List Size after Deleting Head Node by Name");
    checkTest(humanList.getHead()->getData().getFirstName() == "Middle", "Head Node Deleted Correctly");
    cout<<endl;

    humanList.deleteByName("Tail", "Brown");
    checkEqual(2, humanList.getSize(), "HumanCrew List Size after Deleting Tail Node by Name");
    checkTest(humanList.getTail()->getData().getFirstName() == "Middle", "Tail Node Deleted Correctly");
    cout<<endl;

    humanList.deleteByName("middle", "smith"); // case-insensitive
    checkEqual(0, humanList.getSize(), "HumanCrew List Size after Deleting Middle Nodes by Name case-insensitive");
    checkTest(humanList.getHead() == nullptr && humanList.getTail() == nullptr, "All Nodes Deleted Correctly");
    cout<<endl;

    // Deletion of non-existing name
    humanList.deleteByName("Non", "Exist");
    checkEqual(0, humanList.getSize(), "HumanCrew List Size after Attempting to Delete Non-Existing Name");
    cout<<endl;
    


    // Similar tests for AlienCrew can be added here
}


void mergeTest(){
    cout<<"\n[d] Testing Merging HumanCrew and AlienCrew LinkedLists\n"<<endl;
    LinkedList<HumanCrew> humanList;
    LinkedList<AlienCrew> alienList;
    HumanCrew h1("HumanFirst", "First", 3.5,80,"Alpha");
    HumanCrew h2("HumanSecond", "Second", 4.0,90,"Beta");
    TelepathicLinkTest tlt1(8,4,6,5);
    TelepathicLinkTest tlt2(7,5,7,6);
    AlienCrew a1("AlienFirst", "AFirst", 3.8,85,"Orion",tlt1);
    AlienCrew a2("AlienSecond", "ASecond", 4.2,95,"Novera",tlt2);

    humanList.insertSorted(h1, overallHumanCompare);
    humanList.insertSorted(h2, overallHumanCompare);
    alienList.insertSorted(a1, overallAlienCompare);
    alienList.insertSorted(a2, overallAlienCompare);

    cout<<" HumanCrew List: "<<endl;
    humanList.displayAll();
    cout<<endl; 

    cout<<" AlienCrew List: "<<endl;
    alienList.displayAll();
    cout<<endl;

    LinkedList<CrewMember*> mergedList = mergeHumanAlienLists(humanList, alienList);
    checkEqual(4, mergedList.getSize(), "Merged List Size is Correct");
    checkTest(isSorted(mergedList, mergedCompare), "Merged List is Sorted Correctly");
    cout<<" Merged CrewMember List: "<<endl;
    mergedList.displayAll();
    cout<<endl;
    

    //empty human list check
    LinkedList<HumanCrew> emptyHumanList;
    LinkedList<CrewMember*> mergedWithEmptyHuman = mergeHumanAlienLists(emptyHumanList, alienList);
    checkEqual(alienList.getSize(), mergedWithEmptyHuman.getSize(), "Merged List Size with Empty Human List is Correct");
    checkTest(isSorted(mergedWithEmptyHuman, mergedCompare), "Merged List with Empty Human List is Sorted Correctly");
    cout<<" Merged CrewMember List with Empty Human List: "<<endl;
    mergedWithEmptyHuman.displayAll();
    cout<<endl;

    //empty alien list check
    LinkedList<AlienCrew> emptyAlienList;
    LinkedList<CrewMember*> mergedWithEmptyAlien = mergeHumanAlienLists(humanList, emptyAlienList);
    checkEqual(humanList.getSize(), mergedWithEmptyAlien.getSize(), "Merged List Size with Empty Alien List is Correct");
    checkTest(isSorted(mergedWithEmptyAlien, mergedCompare), "Merged List with Empty Alien List is Sorted Correctly");
    cout<<" Merged CrewMember List with Empty Alien List: "<<endl;
    mergedWithEmptyAlien.displayAll();
    cout<<endl;

    cleanupMergedList(mergedList);
    cleanupMergedList(mergedWithEmptyHuman);
    cleanupMergedList(mergedWithEmptyAlien);
}

bool isQualified(const CrewMember& crew) {
    if(crew.getType() != "Alien") {
        return true; // Only AlienCrew members are checked here
    }
    return static_cast<const AlienCrew&>(crew).getTelepathicTest().getTotal() >= 15;
}
void qualifiedTest() {             //for telepatic link range >15
    cout<<"\n[e] Testing Qualified AlienCrew Selection during Merging\n"<<endl;
    TelepathicLinkTest tltQualified(8,5,7,6); // total 26
    TelepathicLinkTest tltNotQualified(3,2,4,3); // total 12
    TelepathicLinkTest tltBoundary(5,5,5,0); // total 15

    AlienCrew qualifiedAlien("Qualified", "Alien", 4.0,90,"Orion",tltQualified);
    AlienCrew notQualifiedAlien("NotQualified", "Alien", 3.0,70,"Novera",tltNotQualified);
    AlienCrew boundaryAlien("Boundary", "Alien", 3.5,80,"Mira",tltBoundary);

    HumanCrew human1("Human", "One", 3.5,85,"Alpha");
    HumanCrew human2("Human", "Two", 4.0,95,"Beta");

    //check for every member

    checkTest(isQualified(qualifiedAlien), "Qualified AlienCrew is Recognized as Qualified");
    checkTest(!isQualified(notQualifiedAlien), "Not Qualified AlienCrew is Recognized as Not Qualified");
    checkTest(isQualified(boundaryAlien), "Boundary AlienCrew is Recognized as Qualified");
    checkTest(isQualified(human1), "HumanCrew is Recognized as Qualified");
    checkTest(isQualified(human2), "HumanCrew is Recognized as Qualified");
    // negative test
    TelepathicLinkTest tltNegative(-1,-2,-3,-4); // total -10
    AlienCrew negativeAlien("Negative", "Alien", 2.0,60,"Nowhere",tltNegative);
    checkTest(!isQualified(negativeAlien), "Negative TelepathicLinkTest AlienCrew is Recognized as Not Qualified");

    LinkedList<AlienCrew> alienLMerge;
    alienLMerge.insertAtEnd(qualifiedAlien);
    alienLMerge.insertAtEnd(notQualifiedAlien);
    alienLMerge.insertAtEnd(boundaryAlien);
    alienLMerge.insertAtEnd(negativeAlien);

    LinkedList<HumanCrew> humanMerge;
    humanMerge.insertAtEnd(human1);
    humanMerge.insertAtEnd(human2);

    cout<<"\n AlienCrew List for Merging Qualified Test: \n"<<endl;
    alienLMerge.displayAll();
    cout<<endl;

    cout<<"\n HumanCrew List for Merging Qualified Test: \n"<<endl;
    humanMerge.displayAll();
    cout<<endl;

    cout<<"\n Displaying Qualified Recruits after Merging: \n"<<endl;
    LinkedList<CrewMember*> mergedList = mergeHumanAlienLists(humanMerge, alienLMerge);
    displayQualifiedRecruits(mergedList);
    cout<<endl;
    cleanupMergedList(mergedList);
}

void runAllTests() {
    testInsertAndSort();
    testSearch();
    deleteTest();
    mergeTest();
    qualifiedTest();

    cout << "\n============= Test Summary =============" << endl;
    cout << "Passed Tests: " << passedTests << endl;
    cout << "Failed Tests: " << failedTests << endl;
    cout<<"=======================================" << endl;
    passedTests = 0;
    failedTests = 0;

}

void printMenu() {
    cout << "\n=== Testing Menu ===" << endl;
    cout << "1. Run All Tests" << endl;
    cout << "2. Test Insertion and Sorting" << endl;
    cout << "3. Test Search Functions" << endl;
    cout << "4. Test Deletion Functions" << endl;
    cout << "5. Test Merging Human and Alien Crews" << endl;
    cout << "6. Test Qualified AlienCrew Selection during Merging" << endl;
    cout << "7. Exit" << endl;

}




      
    














#endif // TESTING_FUNCTIONS_HPP
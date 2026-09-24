#include "file_reader.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
using namespace std;

// Valid sectors and worlds
const vector<string> VALID_SECTORS = {"Alpha", "Beta", "Gamma", "Delta", "Sigma", "Zeta", "Omega"};
const vector<string> VALID_WORLDS = {"Zephon", "Altair", "Mira", "Vulcar", "Trask", "Talos", "Lyra", "Eidolon", "Novera"};

// Case-insensitive string comparison
bool equalsIgnoreCase(const string& a, const string& b) {
    if (a.length() != b.length()) return false;
    for (size_t i = 0; i < a.length(); ++i) {
        if (tolower(a[i]) != tolower(b[i])) return false;
    }
    return true;
}

// Check if sector/world is valid
bool isValidSector(const string& sector) {
    for (const auto& valid : VALID_SECTORS) {
        if (equalsIgnoreCase(sector, valid)) return true;
    }
    return false;
}

bool isValidWorld(const string& world) {
    for (const auto& valid : VALID_WORLDS) {
        if (equalsIgnoreCase(world, valid)) return true;
    }
    return false;
}

// Correct "Bata" to "Beta"
string correctSector(const string& sector) {
    if (equalsIgnoreCase(sector, "Bata")) {
        cerr << "Warning: Corrected 'Bata' to 'Beta'" << endl;
        return "Beta";
    }
    return sector;
}

LinkedList<HumanCrew> readHumanCrewFile(const string& filename) {
    LinkedList<HumanCrew> humans;
    ifstream file(filename);
    
    if (!file.is_open()) {
        cerr << "Error: Cannot open file " << filename << endl;
        return humans;
    }
    
    string line;
    getline(file, line); // skip header
    
    int lineNum = 1;
    while (getline(file, line)) {
        lineNum++;
        stringstream ss(line);
        string firstName, lastName, homeSector;
        float trainingScore;
        int missionAptitude;
        
        // Check for incomplete line
        if (!(ss >> firstName >> lastName >> homeSector >> trainingScore >> missionAptitude)) {
            cerr << "Error: Incomplete data on line " << lineNum << ". Skipping." << endl;
            continue;
        }
        
        try {
            // Validate ranges
            if (trainingScore < 0 || trainingScore > 4.3 || 
                missionAptitude < 0 || missionAptitude > 100) {
                cerr << "Error: Invalid scores on line " << lineNum << ". Skipping." << endl;
                continue;
            }
            
            // Correct typo and validate sector
            homeSector = correctSector(homeSector);
            if (!isValidSector(homeSector)) {
                cerr << "Error: Invalid sector '" << homeSector << "' on line " << lineNum << ". Skipping." << endl;
                continue;
            }
            
            HumanCrew* human = new HumanCrew(firstName, lastName, trainingScore, missionAptitude, homeSector);
            humans.insertAtEnd(*human);
            
        } catch (const exception& e) {
            cerr << "Error: Memory allocation failure on line " << lineNum << ". Skipping." << endl;
        }
    }
    
    file.close();
    
    // Sort once after loading
    humans.sort(overallHumanCompare);
    
    return humans;
}

LinkedList<AlienCrew> readAlienCrewFile(const string& filename) {
    LinkedList<AlienCrew> aliens;
    ifstream file(filename);
    
    if (!file.is_open()) {
        cerr << "Error: Cannot open file " << filename << endl;
        return aliens;
    }
    
    string line;
    getline(file, line); // skip header
    
    int lineNum = 1;
    while (getline(file, line)) {
        lineNum++;
        stringstream ss(line);
        string firstName, lastName, homeworld;
        float trainingScore;
        int missionAptitude, signalStrength, cognitiveLink, empathicOverlay, cognitiveResistance, total;
        
        // Check for incomplete line
        if (!(ss >> firstName >> lastName >> homeworld >> trainingScore >> missionAptitude 
               >> signalStrength >> cognitiveLink >> empathicOverlay >> cognitiveResistance >> total)) {
            cerr << "Error: Incomplete data on line " << lineNum << ". Skipping." << endl;
            continue;
        }
        
        try {
            // Validate ranges
            if (trainingScore < 0 || trainingScore > 4.3 || 
                missionAptitude < 0 || missionAptitude > 100 ||
                signalStrength < 0 || signalStrength > 10 ||
                cognitiveLink < 0 || cognitiveLink > 10 ||
                empathicOverlay < 0 || empathicOverlay > 10 ||
                cognitiveResistance < 0 || cognitiveResistance > 10 ||
                total != (signalStrength + cognitiveLink + empathicOverlay + cognitiveResistance)) {
                cerr << "Error: Invalid scores on line " << lineNum << ". Skipping." << endl;
                continue;
            }
            
            // Validate world
            if (!isValidWorld(homeworld)) {
                cerr << "Error: Invalid world '" << homeworld << "' on line " << lineNum << ". Skipping." << endl;
                continue;
            }
            
            TelepathicLinkTest test(signalStrength, cognitiveLink, empathicOverlay, cognitiveResistance);
            AlienCrew* alien = new AlienCrew(firstName, lastName, trainingScore, missionAptitude, homeworld, test);
            aliens.insertAtEnd(*alien);
            
        } catch (const exception& e) {
            cerr << "Error: Memory allocation failure on line " << lineNum << ". Skipping." << endl;
        }
    }
    
    file.close();
    
    // Sort once after loading
    aliens.sort(overallAlienCompare);
    
    return aliens;
}




void insertHumanFromUser(LinkedList<HumanCrew>& humans) {
    while (true) {
        try {
            string firstName, lastName, homeSector;
            float trainingScore;
            int missionAptitude;
            
            cout << "Enter Human Crew Member Details:" << endl;
            cout << "First Name: "; cin >> firstName;
            cout << "Last Name: "; cin >> lastName;
            cout << "Home Sector: "; cin >> homeSector;
            cout << "Training Score (0-4.3): "; cin >> trainingScore;
            cout << "Mission Aptitude (0-100): "; cin >> missionAptitude;
            
            // Validate and correct
            homeSector = correctSector(homeSector);
            if (!isValidSector(homeSector)) {
                throw invalid_argument("Invalid sector: " + homeSector + ". Valid: Alpha,Beta,Gamma,Delta,Sigma,Zeta,Omega");
            }
            if (trainingScore < 0 || trainingScore > 4.3 || missionAptitude < 0 || missionAptitude > 100) {
                throw invalid_argument("Training score must be 0-4.3, Aptitude must be 0-100");
            }
            
            HumanCrew newHuman(firstName, lastName, trainingScore, missionAptitude, homeSector);
            humans.insertSorted(newHuman, overallHumanCompare);
            cout << "Successfully added to humans list!" << endl;
            break;
            
        } catch (const exception& e) {
            cout << "Error: " << e.what() << ". Please try again." << endl;
        }
    }
}

void insertAlienFromUser(LinkedList<AlienCrew>& aliens) {
    while (true) {
        try {
            string firstName, lastName, homeworld;
            float trainingScore;
            int missionAptitude, signalStrength, cognitiveLink, empathicOverlay, cognitiveResistance;
            
            cout << "Enter Alien Crew Member Details:" << endl;
            cout << "First Name: "; cin >> firstName;
            cout << "Last Name: "; cin >> lastName;
            cout << "Homeworld: "; cin >> homeworld;
            cout << "Training Score (0-4.3): "; cin >> trainingScore;
            cout << "Mission Aptitude (0-100): "; cin >> missionAptitude;
            cout << "Signal Strength (0-10): "; cin >> signalStrength;
            cout << "Cognitive Link (0-10): "; cin >> cognitiveLink;
            cout << "Empathic Overlay (0-10): "; cin >> empathicOverlay;
            cout << "Cognitive Resistance (0-10): "; cin >> cognitiveResistance;
            
            // Validate
            if (!isValidWorld(homeworld)) {
                throw invalid_argument("Invalid world: " + homeworld + ". Valid: Zephon,Altair,Mira,Vulcar,Trask,Talos,Lyra,Eidolon,Novera");
            }
            if (trainingScore < 0 || trainingScore > 4.3 || missionAptitude < 0 || missionAptitude > 100 ||
                signalStrength < 0 || signalStrength > 10 || cognitiveLink < 0 || cognitiveLink > 10 ||
                empathicOverlay < 0 || empathicOverlay > 10 || cognitiveResistance < 0 || cognitiveResistance > 10) {
                throw invalid_argument("All scores must be in valid ranges");
            }
            
            TelepathicLinkTest test(signalStrength, cognitiveLink, empathicOverlay, cognitiveResistance);
            AlienCrew newAlien(firstName, lastName, trainingScore, missionAptitude, homeworld, test);
            aliens.insertSorted(newAlien, overallAlienCompare);
            cout << "Successfully added to aliens list!" << endl;
            break;
            
        } catch (const exception& e) {
            cout << "Error: " << e.what() << ". Please try again." << endl;
        }
    }
}

void insertToMergedFromUser(LinkedList<CrewMember*>& mergedList) {
    while (true) {
        try {
            cout << "Add to Merged List - Choose type:" << endl;
            cout << "1. Human" << endl;
            cout << "2. Alien" << endl;
            int choice;
            cin >> choice;
            
            if (choice == 1) {
                // Create human and add to merged
                string firstName, lastName, homeSector;
                float trainingScore;
                int missionAptitude;
                
                cout << "Enter Human Details:" << endl;
                cout << "First Name: "; cin >> firstName;
                cout << "Last Name: "; cin >> lastName;
                cout << "Home Sector: "; cin >> homeSector;
                cout << "Training Score (0-4.3): "; cin >> trainingScore;
                cout << "Mission Aptitude (0-100): "; cin >> missionAptitude;
                
                homeSector = correctSector(homeSector);
                if (!isValidSector(homeSector)) {
                    throw invalid_argument("Invalid sector: " + homeSector);
                }
                if (trainingScore < 0 || trainingScore > 4.3 || missionAptitude < 0 || missionAptitude > 100) {
                    throw invalid_argument("Invalid score range");
                }
                
                CrewMember* newHuman = new HumanCrew(firstName, lastName, trainingScore, missionAptitude, homeSector);
                mergedList.insertSorted(newHuman, getMergedCompare());
                cout << "Successfully added Human to merged list!" << endl;
                break;
                
            } else if (choice == 2) {
                // Create alien and add to merged
                string firstName, lastName, homeworld;
                float trainingScore;
                int missionAptitude, signalStrength, cognitiveLink, empathicOverlay, cognitiveResistance;
                
                cout << "Enter Alien Details:" << endl;
                cout << "First Name: "; cin >> firstName;
                cout << "Last Name: "; cin >> lastName;
                cout << "Homeworld: "; cin >> homeworld;
                cout << "Training Score (0-4.3): "; cin >> trainingScore;
                cout << "Mission Aptitude (0-100): "; cin >> missionAptitude;
                cout << "Signal Strength (0-10): "; cin >> signalStrength;
                cout << "Cognitive Link (0-10): "; cin >> cognitiveLink;
                cout << "Empathic Overlay (0-10): "; cin >> empathicOverlay;
                cout << "Cognitive Resistance (0-10): "; cin >> cognitiveResistance;
                
                if (!isValidWorld(homeworld)) {
                    throw invalid_argument("Invalid world: " + homeworld);
                }
                if (trainingScore < 0 || trainingScore > 4.3 || missionAptitude < 0 || missionAptitude > 100 ||
                    signalStrength < 0 || signalStrength > 10 || cognitiveLink < 0 || cognitiveLink > 10 ||
                    empathicOverlay < 0 || empathicOverlay > 10 || cognitiveResistance < 0 || cognitiveResistance > 10) {
                    throw invalid_argument("Invalid score range");
                }
                
                TelepathicLinkTest test(signalStrength, cognitiveLink, empathicOverlay, cognitiveResistance);
                CrewMember* newAlien = new AlienCrew(firstName, lastName, trainingScore, missionAptitude, homeworld, test);
                mergedList.insertSorted(newAlien, getMergedCompare());
                cout << "Successfully added Alien to merged list!" << endl;
                break;
                
            } else {
                throw invalid_argument("Invalid choice. Enter 1 for Human or 2 for Alien");
            }
            
        } catch (const exception& e) {
            cout << "Error: " << e.what() << ". Please try again." << endl;
        }
    }
}



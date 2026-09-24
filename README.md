[README.md](https://github.com/user-attachments/files/32597792/README.md)
# Crew Management System — C++

A C++ system for managing and merging two crew rosters (Human and Alien) using polymorphic OOP design, a custom templated linked list, and a validated file-parsing pipeline. Built for ENSC 251 (Software Design and Analysis for Engineers), Simon Fraser University.

## Features

- **Polymorphic crew hierarchy** — an abstract `CrewMember` base class with virtual dispatch unifies `HumanCrew` and `AlienCrew` subtypes behind one shared interface (printing, comparison, type identification)
- **Templated generic linked list** — a single `LinkedList<T>` implementation works transparently with both objects and pointers via specialized accessor structs, avoiding duplicated logic
- **Efficient sorting & insertion** — O(n log n) merge sort and O(n) sorted insertion, both usable through custom comparison functions
- **Robust file parsing** — reads crew data from `.txt` files with input validation, typo correction (e.g. "Bata" → "Beta"), and graceful skipping of malformed rows
- **Merge & qualification logic** — combines both rosters into one sorted list, filtering aliens by a telepathic-aptitude threshold while including all humans
- **Custom unit-test suite** — covers insertion, search (by ID, name, score range), deletion, and merge operations, with pass/fail reporting

## Architecture

| File | Responsibility |
|---|---|
| `CrewMember.cpp/.hpp` | Abstract base class — shared fields, virtual interface, comparison friend functions |
| `HumanCrew.cpp/.hpp` | Human crew subtype |
| `AlienCrew.cpp/.hpp` | Alien crew subtype, includes `TelepathicLinkTest` scoring |
| `LinkedList.hpp` | Generic templated linked list with merge sort, sorted insertion, and search operations |
| `Node.hpp` | Linked list node |
| `crew_merge.cpp/.hpp` | Merges human and alien lists into one sorted, qualification-filtered roster |
| `file_reader.cpp/.hpp` | Parses and validates crew data from text files; supports interactive manual entry |
| `overall_compare.hpp` | Comparison functions for sorting each crew type |
| `telepathic_link_test.cpp/.hpp` | Alien-specific aptitude scoring |
| `testingFunctions.hpp` | Unit test suite covering all core operations |
| `main-4.cpp` | Interactive test menu entry point |

## Example

```cpp
LinkedList<HumanCrew> humans = readHumanCrewFile("human-crew.txt");
LinkedList<AlienCrew> aliens = readAlienCrewFile("alien-crew.txt");

LinkedList<CrewMember*> merged = mergeHumanAlienLists(humans, aliens);
displayQualifiedRecruits(merged);
```

## Testing

Run the interactive menu in `main-4.cpp` to execute the full test suite, or individual test categories (insertion/sorting, search, deletion, merging, qualification filtering).

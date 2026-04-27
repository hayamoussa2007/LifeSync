# LifeSync Organizer (C++)

LifeSync Organizer is a simple command-line application written in C++ that helps manage tasks, events, and notes. It is designed to demonstrate the practical use of fundamental data structures in a real-world context.

## Overview

The program consists of three main components:

* Task Management system
* Event Organizer
* Note System

Each component uses a different data structure to efficiently handle its operations.

---

## Features

### Task Management

* Add tasks with a title, category, and priority
* Tasks are automatically sorted by priority
* Remove tasks by title
* Search for tasks by title or category
* Display all tasks

**Data structure used:** Singly linked list (with sorted insertion)

---

### Event Organizer

* Add events with title, time (HHMM), and description
* Automatically keeps events ordered by time
* View the next upcoming event
* Remove the earliest event
* Display all events in chronological order

**Data structure used:** Min heap

---

### Note System

* Add notes with a title and content
* Update existing notes
* Undo the most recent change to a note
* Display all stored notes

**Data structures used:** Hash table (with linear probing) and stack (for undo functionality)

---

## Data Structures Summary

* Linked List → Task Management
* Min Heap → Event Organizer
* Hash Table + Stack → Note System

---

## How to Run

1. Compile the program:

```bash
g++ main.cpp -o lifesync
```

2. Run the executable:

```bash
./lifesync
```

---

## Program Flow

When the program starts, you will see a main menu:

```
LifeSync Organizer
1. Task Management
2. Event Organizer
3. Note System
4. Exit
```

Each option opens a separate interactive menu for that module.

---

## Limitations

* Fixed sizes (hash table size is 10, heap size is 100)
* No data persistence (all data is lost when the program exits)
* Basic input validation

---

## Possible Improvements

* Add file storage to save and load data
* Improve input validation and error handling
* Allow dynamic resizing of data structures
* Build a graphical user interface
* Enhance search and filtering capabilities

---

## Purpose

This project was developed to apply and demonstrate understanding of core data structures, including linked lists, heaps, hash tables, and stacks, in a practical application.

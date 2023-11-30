# Clock with Seven Segment Display

This C++ program simulates a digital clock with a seven-segment display using classes and object-oriented programming principles. It allows you to set the time, add or subtract minutes and hours, and displays the time on a virtual seven-segment display.

## Overview

This project implements a digital clock with seven-segment display simulation in C++. It consists of three classes: `Node`, `Digit`, and `Clock`, each serving a specific purpose in achieving the functionality of the clock.

## Table of Contents

- [Introduction](#introduction)
- [Classes and Functions](#classes-and-functions)
  - [Node](#node-class)
  - [Digit](#digit-class)
  - [Clock](#clock-class)
- [Getting Started](#getting-started)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)

## Introduction

This program demonstrates the use of classes and objects in C++ to create a digital clock. It uses a class for the clock and another class for representing each digit on the display. The clock allows you to adjust the time and view the time in a seven-segment display format.

## Classes and Functions

### Node Class

The `Node` class represents a node in a linked structure used to create the seven-segment display.

### Digit Class

The `Digit` class represents a single digit (0-9) of the clock's time. It is responsible for initializing the segments that make up the digit based on the provided value.

- `Digit(int digit = 8)`: Constructor to create a digit object with segments set according to the provided digit.

### Clock Class

The `Clock` class is the core of the program, responsible for managing time, adding/subtracting minutes and hours, and displaying the time on the seven-segment display.

- `Clock(string t)`: Constructor that initializes the clock with a given time in HH:MM format.

#### Clock Functions

- `void AddMinutes(int mins)`: Add the specified number of minutes to the clock's time.
- `void SubtractMinutes(int mins)`: Subtract the specified number of minutes from the clock's time.
- `void AddHours(int hrs)`: Add the specified number of hours to the clock's time.
- `void SubtractHours(int hrs)`: Subtract the specified number of hours from the clock's time.
- `void adjustDigits()`: Update the internal digit representation based on the current time.
- `void displayTime()`: Display the time on a virtual seven-segment display.
  
## Getting Started

1. Clone this repository to your local machine.
2. Compile the `main.cpp` file using a C++ compiler.



# Exam Queue System

This is a C++ program that simulates an exam queue system, tracking the submission and return of exam papers, with specific focus on a student named John.

## Table of Contents

- [Description](#description)
- [How It Works](#how-it-works)
- [Usage](#usage)


## Description

This program is designed to model the process of submitting and checking exam papers in a queue. It has the following features:

- Manages a queue of students waiting to submit their exam papers.
- Simulates the submission and checking of exam papers.
- Tracks the position of John's paper in both submission and result stacks.

## How It Works

The program creates a queue of students, simulating their seating arrangement in an exam room. It models the submission of exam papers, tracking the position of John's paper in the submission stack and the result stack. The program also provides statistics about John's paper, such as how many papers he has to go through on result day.

## Usage

You can compile and run this program in a C++ environment. Make sure you have C++ installed on your system.

To compile and run the program, use the following commands:

```bash
g++ main.cpp -o exam-queue
./exam-queue

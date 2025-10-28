# Scheduler Library for Arduino

The Scheduler library is a simple task scheduler for Arduino. It allows you to schedule and manage tasks with specific intervals.

## Features
- Add tasks with default or custom intervals.
- Enable or disable tasks dynamically.
- Run tasks based on their scheduled intervals.

## Installation
1. Download the library as a ZIP file or clone the repository.
2. Place the `scheduler` folder in your Arduino `libraries` directory.
3. Restart the Arduino IDE.

## Usage
Here is an example of how to use the Scheduler library:

```cpp
#include <schedulerTask.h>

SchedulerTask scheduler;

void task1() {
    Serial.println("Task 1 executed");
}

void setup() {
    Serial.begin(9600);
    scheduler.addTask(task1, 1000000); // Run task1 every 1 second
}

void loop() {
    scheduler.runAll();
}
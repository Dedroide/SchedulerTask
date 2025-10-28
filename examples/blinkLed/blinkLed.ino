#include <schedulerTask.h>

SchedulerTask scheduler;

unsigned char taskId = 0;
void task1() {
    Serial.println("Task 1 executed");
    Serial.print("taskId: ");
    Serial.println(taskId);
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN)); // Toggle the built-in LED
}

void task2() {
    Serial.println("Task 2 executed");
    scheduler.enableTask(taskId, false);
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN)); // Toggle the built-in LED
}

void setup() {
    Serial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT);
   taskId = scheduler.addTask(task1, 1000000); // Run task1 every 1 second
    scheduler.addTask(task2, 5000000); // Run task2 every 2 seconds
}

void loop() {
    scheduler.runAll();
}
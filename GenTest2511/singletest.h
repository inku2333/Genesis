#ifndef SINGLETEST_H
#define SINGLETEST_H

#include <iostream>
#include <queue>
#include <string>
#include <chrono>
#include <thread>

// Task class
class Task {
private:
    std::string name_;      // Task name
    int priority_;          // Priority: 1-lowest, 5-highest
    int execution_time_;    // Execution time in seconds

public:
    Task(std::string name, int priority, int execution_time)
        : name_(std::move(name)), priority_(priority), execution_time_(execution_time) {
        // Ensure priority is within valid range
        if (priority_ < 1) priority_ = 1;
        if (priority_ > 5) priority_ = 5;
    }

    // Execute the task
    void execute() const {
        std::cout << "Starting task: " << name_
                  << " (Priority: " << priority_ << ")" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(execution_time_));
        std::cout << "Task completed: " << name_ << std::endl;
    }

    // Overload < operator for priority_queue sorting
    // Note: priority_queue uses less<T> by default, so higher priority tasks are processed first
    bool operator<(const Task& other) const {
        return priority_ < other.priority_;  // Higher priority tasks are "less than" lower ones
    }
};

// Task scheduler
class TaskScheduler {
private:
    std::priority_queue<Task> task_queue_;  // Priority queue to store tasks

public:
    // Add a task to the scheduler
    void add_task(const Task& task) {
        task_queue_.push(task);
        std::cout << "Task added: " << task_queue_.size() << " tasks waiting for execution" << std::endl;
    }

    // Execute all tasks in priority order
    void run_all_tasks() {
        std::cout << "Starting all tasks, total of " << task_queue_.size() << " tasks" << std::endl;

        while (!task_queue_.empty()) {
            // Get the highest priority task
            Task current_task = task_queue_.top();
            task_queue_.pop();

            // Execute the task
            current_task.execute();
        }

        std::cout << "All tasks completed" << std::endl;
    }
};

class singleTest
{
public:
    singleTest();
};

#endif // SINGLETEST_H

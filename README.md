# Operating Systems Programming Assignment

### Course: CSE315 - Design of Operating System

This repository contains the solutions for the Operating Systems programming assignment. The project explores fundamental OS concepts through five distinct programming challenges, covering process and thread management, synchronization, CPU scheduling, and low-level system API interaction across multiple operating systems.

---

## Technologies & Environments

This project was developed using a variety of languages and technologies to tackle platform-specific challenges:

-   **Languages:** C, C++, Java, Python
-   **APIs & Libraries:** POSIX (`fork()`, `wait()`), C++11 Threads (`<thread>`), WIN32 API (`GetCursorPos()`, `Sleep()`), Java Concurrency (`synchronized`, `wait()`, `notifyAll()`)
-   **Operating Systems:** macOS (UNIX-based), Windows 11 (in a VM)
-   **Tools:** Clang/GCC, Visual Studio 2022, IntelliJ IDEA, UTM for virtualization

---

## 📂 Project Structure & Solutions

This repository is organized into folders, one for each of the five mandatory problems.

### A: Multiprocessing (Collatz Conjecture)

-   **Description:** A C program that demonstrates process creation using the `fork()` system call. The child process calculates the Collatz sequence for a given number, while the parent process waits for its completion.
-   **Key Concepts:** Process Creation (`fork()`), Process Synchronization (`wait()`), POSIX API.
-   **How to Run (macOS/Linux):**
    ```bash
    # Compile the C code
    clang collatz.c -o collatz

    # Run the program with a positive integer
    ./collatz 12
    ```

### B: CPU Scheduling Simulator

-   **Description:** A Python script that simulates a non-preemptive **First-Come, First-Served (FCFS)** CPU scheduling algorithm. It calculates and reports key performance metrics.
-   **Key Concepts:** CPU Scheduling, Process States, Performance Metrics (Turnaround Time, Waiting Time, CPU Utilization).
-   **How to Run:**
    ```bash
    # Run the Python script
    python3 scheduler.py
    ```

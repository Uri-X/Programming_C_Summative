
# **Smart Embedded Systems and C Projects – Summative Assessment 2025**

*By Philbert Kuria*

This repository contains five fully implemented projects demonstrating embedded systems design, shell scripting, systems programming, data structures, algorithms, and multi-threading in C.

---

## **Presentation Video**

Watch the full project demo:
https://drive.google.com/file/d/1GXiYS2aYjcTCFo5ufsL8VKfR10o_fIpO/view?usp=sharing

---

## **Project Summary**

| #     | Project                               | Key Features                                                                                                                 | Status   |
| ----- | ------------------------------------- | ---------------------------------------------------------------------------------------------------------------------------- | -------- |
| **1** | Smart Traffic Light System            | Non-blocking `millis()` logic, adaptive green duration, button-based vehicle detection, modular design, Tinkercad-ready      | Complete |
| **2** | Advanced System Monitoring Script     | Runs without sudo, live system metrics, user-writable logs, background monitoring, configurable thresholds, interactive menu | Complete |
| **3** | Student Management System             | Full CRUD, binary file persistence, `qsort` sorting, linear/binary search, analytics report, strong input validation         | Complete |
| **4** | Dynamic Math & Data Processing Engine | Function pointers, dynamic memory, file I/O, searching, sorting, dataset operations, clean terminal UI                       | Complete |
| **5** | Multi-threaded Web Scraper            | POSIX threads, per-thread file output, simulated webpage scraping, safe thread management, no external libraries required    | Complete |

---

## **Project Descriptions & How to Run**

### **1. Smart Traffic Light System**

**Link:** [Tinkercad Project](https://www.tinkercad.com/things/evvqQMZs9H5-smart-traffic-control-and-monitoring-system/editel?returnTo=https%3A%2F%2Fwww.tinkercad.com%2Fdashboard%2Fdesigns%2Fall%3Fpage%3D1&sharecode=dkH7z2vI4LwqjJe5g5Ru_qLvGKUM1_Gf5v0LpnqPr_g)
**Path:** `Project_1_Traffic_Light/traffic_light.ino`

A simplified embedded traffic light system implemented using Arduino.

**Features:**

* Non-blocking timing using `millis()`
* Dynamic green time based on vehicle queue
* Simple hardware: 3 LEDs + 1 button
* Debug output via Serial
* Fully compatible with Tinkercad Circuits

**Run:**
Import the `.ino` file into Arduino IDE or Tinkercad and upload to your board.

---

### **2. Advanced System Monitoring Script**

**Path:** `Project_2_System_Monitor/monitor.sh`

A Bash-based system utility to monitor CPU, RAM, and disk usage.

**Features:**

* No root access required
* Logs saved under `~/sysmonitor.log`
* Threshold-based alerts
* Menu-driven interface
* Background monitoring mode

**Run:**

```bash
chmod +x monitor.sh
./monitor.sh
```

---

### **3. Student Management System**

**Path:** `Project_3_Student_Management/student_management.c`

A C program for managing student records with analytics and persistent storage.

**Features:**

* Create, read, update, delete student entries
* Data stored in binary format
* Sorting by GPA, name, or ID using `qsort`
* Reporting: averages, top students, distributions
* Robust input validation and error handling

**Compile & Run:**

```bash
gcc student_management.c -o student
./student
```

---

### **4. Dynamic Math & Data Processing Engine**

**Path:** `Project_4_Math_Engine/math_engine.c`

A modular and extensible computational engine.

**Features:**

* Function pointers for dynamic operation selection
* Dynamic memory allocation for datasets
* File-based dataset loading and saving
* Searching, sorting, statistical operations
* Clean terminal UI

**Compile & Run:**

```bash
gcc math_engine.c -o mathengine
./mathengine
```

---

### **5. Multi-threaded Web Scraper**

**Path:** `Project_5_Web_Scraper/scraper.c`

A POSIX-thread-based web scraping simulator.

**Features:**

* Parallel page fetching
* Thread-isolated file outputs
* Simulated URLs (no external dependencies)
* Graceful error handling for invalid URLs
* Proper thread lifecycle management

**Compile & Run:**

```bash
gcc scraper.c -o scraper -lpthread
./scraper
```

---

## **Technologies Demonstrated**

* Low-level C programming: pointers, structs, dynamic memory
* File I/O (binary and text)
* Algorithm design: sorting, searching, reporting
* Bash scripting and Linux utilities
* Multi-threading with POSIX pthreads
* Modular design and code documentation

---
[My Circuit](<../../Downloads/PCB_Design_Traffic_Light Controller.pdf>)
## **Repository Structure**

```
Project_1_Traffic_Light/
Project_2_System_Monitor/
Project_3_Student_Management/
Project_4_Math_Engine/
Project_5_Web_Scraper/
README.md
```

---
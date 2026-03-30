
# **Smart Embedded Systems and C Projects – Summative Assessment 2025**

*By Philbert Kuria*

This repository contains five fully implemented projects demonstrating embedded systems design, shell scripting, systems programming, data structures, algorithms, and multi-threading in C.

---

## **Presentation Video**

Watch the full project demo:
[View on Google Drive]()

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

**Link:** [Tinkercad Project](https://www.tinkercad.com/things/1AH80oNS9lr-smart-traffic-control-and-monitoring-system?sharecode=--uqGRiU2WtpkinETE4Y_ZYKsL66Y_xyJLF4Qs298_I)
**Path:** `Project_1_Traffic_Light/traffic_light.ino`

A simplified embedded traffic light system implemented using Arduino.

**Features:**

* Non-blocking timing using `millis()`
* Dynamic green time based on vehicle queue
* Simple hardware: 3 LEDs + 1 button
* Debug output via Serial
* Fully compatible with Tinkercad Circuits

**Run:**

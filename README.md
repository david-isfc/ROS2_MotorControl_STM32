# STM32 ROS2 Motor Project

## Overview

This project implements a **modular, distributed motor control system** using STM32 microcontrollers, FreeRTOS, and ROS 2. The architecture separates **real-time motor actuation** from higher-level control and ROS 2 integration, allowing low-latency motor control while still leveraging ROS 2 for monitoring, control, and data processing.

---

## System Architecture

### **Board A – STM32 + Motor (Real-Time Control)**

* **Firmware:** Runs FreeRTOS  
* **Tasks:**
  * **Motor Control Task:** Drives the motor using PWM signals, based on commands from Board B
  * **Speed Measurement Task:** Reads motor speed via encoder or sensor
  * **Ethernet Task:** Receives motor control commands from Board B over Ethernet
* **Key Principle:** Focus on real-time motor control; avoid high-level logic

### **Board B – STM32 (Micro-ROS Bridge)**

* **Firmware:** Runs Micro-ROS client  
* **Functions:**
  * Receives `/motor_control` commands from the ROS 2 node on the PC
  * Forwards these commands to Board A over Ethernet
  * Receives motor speed from Board A
  * Publishes motor speed to ROS 2 topic `/motor_speed`

### **PC – ROS 2 Node (Python)**

* **Functions:**
  * Computes motor control commands (e.g., via a PI controller)
  * Publishes commands to `/motor_control` for Board B to forward
  * Subscribes to `/motor_speed` to monitor motor performance
  * Optional: Logging, visualization, and parameter tuning (e.g., using `rqt`)

---

## RTOS and Task Prioritization

**Board A (FreeRTOS):**

* Motor Control Task → **Highest Priority**
* Speed Measurement Task → High Priority
* Ethernet Task → Lower priority, non-blocking

**Board B (FreeRTOS + Micro-ROS):**

* Micro-ROS executor handles incoming motor speed and outgoing ROS 2 messages
* Task prioritization is less critical than Board A

---

## Modularity and Scalability

* Control logic on the PC can be swapped with more advanced controllers without changing Board A firmware
* Board B acts as a **bridge** between the real-time embedded world and the ROS 2 ecosystem
* Additional motor boards can be added by replicating Board A, each communicating with Board B via ROS 2 topics

---

## Safety and Reliability

* Emergency stop handling and fault detection (overcurrent, overtemperature) can be implemented on Board A  
* Watchdog timers ensure Board A remains responsive

---

## Conclusion

This architecture provides:

* **Board A:** Real-time motor control with FreeRTOS  
* **Board B:** Micro-ROS bridge for ROS 2 integration  
* **PC:** Python ROS 2 node for computing motor commands, logging, and visualization  

Perfect for learning and prototyping distributed embedded control systems with ROS 2.

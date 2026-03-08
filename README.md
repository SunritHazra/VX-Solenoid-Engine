# V2 Solenoid Engine

A **two-cylinder (V2) solenoid engine** that converts electrical energy into rotational mechanical motion using electromagnetic coils and a crankshaft mechanism.

This project combines **mechanical design, electromagnetism, power electronics, and embedded control**.  
The mechanical system is designed in CAD for **3D printing and CNC machining**, while control electronics are built around an **ESP32 microcontroller** with **infrared crankshaft position sensing**.

The goal of this repository is to provide the **design files, electronics, firmware, and documentation required to reproduce the engine.**

---

# Project Overview

The V2 Solenoid Engine operates using two electromagnetic cylinders arranged around a crankshaft.  
Each cylinder contains a coil and a soft-iron plunger. When current flows through the coil, the plunger is pulled inward. The motion is transferred through a yoke to a crankshaft, converting linear motion into rotational motion.

A flywheel smooths the rotation while an ESP32 microcontroller controls coil timing based on crankshaft position detected by IR sensors.

The system consists of three main subsystems:

**Mechanical System**
- Solenoid cylinders
- Soft-iron plungers
- Yokes
- Crankshaft
- Flywheel
- Structural frame

**Electronics**
- ESP32 controller
- MOSFET coil drivers
- IR position sensors
- Power supply and protection circuitry

**Firmware**
- Sensor reading
- Coil activation timing
- PWM control for solenoids

---

# System Architecture


IR Sensors → ESP32 → MOSFET Driver → Solenoid Coils → Plunger Motion → Crankshaft → Flywheel


1. IR sensors detect crankshaft position.
2. ESP32 determines when to energize a solenoid.
3. MOSFET drivers switch current through the coil.
4. Magnetic force pulls the plunger.
5. The plunger moves a yoke attached to the crankshaft.
6. The crankshaft rotates and the flywheel stabilizes motion.

---

# Repository Structure


V2-Solenoid-Engine
│
├── CAD
│ ├── Fusion360 files
│ └── STL exports
│
├── Electronics
│ ├── KiCad PCB
│ └── schematics
│
├── Firmware
│ └── solenoid_engine.ino
│
├── Media
│ └── wiring diagrams and renders
│
├── BOM
│ └── bill_of_materials.csv
│
├── Assembly
│ └── assembly-guide.md
│
└── README.md


---

# Mechanical System

## Solenoid Cylinders

Each cylinder contains:

- Coil housing
- Copper magnet wire winding
- Soft iron plunger
- Linear guide sleeve

The plunger moves linearly inside the sleeve when the coil is energized.

---

## Yoke Mechanism

The plunger is connected to the crankshaft using a **yoke linkage**.

This mechanism transfers linear motion from the plunger into rotational motion at the crankshaft.

The yokes are designed with thicker walls to increase structural strength and provide space for the coil winding area.

---

## Crankshaft

The crankshaft converts linear plunger motion into rotation.

Key components:

- crank throws
- shaft core
- bearing journals
- flywheel mount

The crankshaft is designed to be **CNC machined** for strength and dimensional accuracy.

---

## Flywheel

A heavy flywheel is mounted on the crankshaft.

Its purposes:

- increase rotational inertia
- reduce stalling between pulses
- smooth torque output

---

## Structural Frame

The engine is supported by a rigid **exoskeleton frame** that:

- holds the solenoid cylinders
- supports crankshaft bearings
- mounts sensors
- maintains alignment between components

Most structural components are designed for **3D printing**.

---

# Electronics

## Microcontroller

**ESP32 DevKit V1**

Functions:

- reads crankshaft position sensors
- controls solenoid activation timing
- generates PWM signals
- provides optional WiFi configuration interface

---

## Position Sensors

**TCRT5000 infrared reflective sensors**

These sensors detect reflective markers attached to the rotating crankshaft.

Sensor signals are connected to:


GPIO34
GPIO35


These inputs are used for interrupt-based position detection.

---

## Solenoid Driver Circuit

Each solenoid coil is switched using a MOSFET stage.

Components:

- IRFZ44N MOSFET
- TC4427A MOSFET gate driver
- MBR3060PT flyback diode

The MOSFET switches the ground side of the solenoid coil while the positive side remains connected to the 24 V supply.

Flyback diodes protect the MOSFETs from voltage spikes generated when the coil is switched off.

---

## Power System

Main power supply:

**Mean Well LRS-450-24**

Specifications:

- 24 V output
- high current capability for solenoid operation

Two voltage domains are used:

**24 V Power Rail**

Used for:

- solenoid coils
- MOSFET switching stage

**5 V Logic Rail**

Used for:

- ESP32
- sensors
- gate driver logic

---

# Manufacturing

The engine uses **hybrid fabrication** combining additive manufacturing and CNC machining.

---

## 3D Printed Parts

Printed components include:

- engine frame
- solenoid sleeves
- coil housings
- sensor mounts
- yokes
- structural supports

Recommended materials:

- PLA (prototyping)
- PETG or ABS (improved durability)

All printable models are available in the **CAD / STL folder**.

---

## CNC Machined Parts

Precision mechanical parts are intended for CNC machining.

Examples:

- crankshaft
- metal shafts
- some structural inserts if required

Suggested service:


https://jlcpcb.com/cnc-machining


---

# Assembly Overview

A full assembly guide is available in:


Assembly/assembly-guide.md


General assembly sequence:

1. Print all structural components.
2. Install bearings into the engine frame.
3. Insert the crankshaft and attach the flywheel.
4. Install plungers and yokes.
5. Wind copper magnet wire onto the solenoid housings.
6. Mount the IR sensors.
7. Install the control PCB.
8. Connect solenoids, sensors, and power supply.
9. Upload firmware to the ESP32 and test coil activation.

---

# Firmware

Prototype firmware is provided in:


Firmware/solenoid_engine.ino


Functions implemented:

- PWM control of solenoids
- crankshaft position detection
- WiFi configuration interface
- temperature safety cutoff

---

## Flashing (Arduino IDE)

1. Install ESP32 board support.

Add this URL to **Additional Boards Manager URLs**:


https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json


2. Install board package:


Tools → Board Manager → esp32 → Install


3. Select board:


Tools → Board → ESP32 Dev Module


4. Install libraries:


ESPAsyncWebServer
AsyncTCP


5. Upload firmware and open the serial monitor at **115200 baud**.

---

# Bill of Materials

A complete bill of materials is provided in:


BOM/bill_of_materials.csv


Components include:

- ESP32 DevKit V1
- TCRT5000 IR sensors
- IRFZ44N MOSFETs
- TC4427A MOSFET driver
- MBR3060PT flyback diodes
- copper magnet wire
- bearings
- power supply
- fasteners
- 3D printed structural components
- CNC machined crankshaft

Certain components are sourced locally and paid for by the creator to avoid unnecessary costs on the Hack Club grant.

---

# Wiring

Electrical connections are documented in:


Electronics/


Files include:

- KiCad schematic
- PCB layout
- wiring diagrams

These files define all electrical connections between:

- ESP32
- MOSFET driver
- solenoid coils
- IR sensors
- power supply

---

# Applications

This project demonstrates principles useful for:

- electromechanical research
- educational demonstrations
- actuator design
- embedded control systems
- experimental engine architectures

---

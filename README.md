# V2 Solenoid Engine

A **3D-printed, electronically controlled, multi-cylinder solenoid engine** designed and built by **Sunrit Hazra** as part of the Hack Club Blueprint program.  
The project explores the intersection of **mechanical engineering, electromagnetism, electronics, and embedded control** through a fully custom-designed engine architecture.

Unlike combustion engines, this system converts electrical energy into rotational mechanical motion using **electromagnetic solenoids driving a crankshaft mechanism**.

The entire mechanical system is designed in CAD, with structural components intended for **3D printing and CNC machining**, while control electronics are built around an **ESP32 microcontroller** and **IR position sensing**.

---

# Project Overview

The V2 Solenoid Engine is a **mechanically actuated electromagnetic engine** where coils generate magnetic force that drives plungers connected to a crankshaft. The crankshaft converts linear motion into rotation, similar to a traditional piston engine.

To achieve reliable timing and stable operation, the system uses **optical position sensing** and **microcontroller-based switching**.

The engine demonstrates:

- Electromagnetic actuation
- Crankshaft-based mechanical power conversion
- Embedded timing control
- Modular CAD-driven mechanical design
- Hybrid manufacturing (3D printing + CNC)

---

# Core Concept

A solenoid generates a magnetic field when current flows through its copper coil. A ferromagnetic plunger inside the solenoid is pulled toward the coil center.

In this engine:

1. **A microcontroller activates the solenoid coil**
2. **Magnetic force pulls the plunger**
3. **The plunger drives a yoke connected to the crankshaft**
4. **The crankshaft rotates**
5. **A flywheel smooths rotational motion**
6. **IR sensors detect crank position**
7. **The controller switches coils again**

This cycle produces **continuous rotation**.

---

# Key Features

## Multi-Cylinder Mechanical Layout

The engine follows a **V-style configuration**, where multiple solenoid cylinders are arranged around a central crankshaft.

Advantages:

- More balanced mechanical forces
- Smoother rotation
- Modular cylinder expansion

---

## Electromagnetic Actuation

Each cylinder contains:

- Copper coil winding
- Ferromagnetic plunger
- Linear motion sleeve

The plunger converts **magnetic attraction into mechanical displacement**.

---

## Crankshaft Mechanism

The crankshaft converts linear plunger motion into rotation using:

- Crank pins
- Yokes
- Connecting linkages

The crankshaft is intentionally **shortened and compact** to reduce friction losses and improve mechanical efficiency.

---

## Flywheel Stabilization

A **large flywheel** is attached to the crankshaft.

Its functions include:

- Increasing rotational inertia
- Reducing stalling between pulses
- Smoothing torque output

---

## Optical Position Sensing

The engine uses **TCRT5000 IR sensors** to detect crankshaft position.

These sensors allow the controller to:

- Identify rotation phase
- Trigger solenoids at the correct moment
- Prevent mistimed coil activation

This transforms the engine from a passive mechanism into an **actively controlled electromechanical system**.

---

## Exoskeleton Structural Frame

The engine is supported by a rigid **exoskeleton frame**.

This structure:

- Maintains alignment of cylinders
- Supports bearings and shaft components
- Prevents structural flexing
- Simplifies mounting of electronics and sensors

The exoskeleton also allows modular modifications and maintenance.

---

# Mechanical Design

The mechanical system consists of several interacting components.

## Solenoid Cylinder Assembly

Each cylinder contains:

- Coil housing
- Copper winding space
- Plunger sleeve
- Linear motion channel

The sleeve guides the plunger and maintains alignment.

---

## Yoke Mechanism

The yoke connects the plunger to the crankshaft.

The yoke geometry was thickened to:

- Increase structural strength
- Allow sufficient room for coil windings
- Reduce mechanical deformation during operation

---

## Crankshaft

The crankshaft includes:

- Crank throws
- Bearing supports
- Shaft core
- Flywheel mount

The crank dimensions were reduced to lower rotational inertia and mechanical drag.

---

## Structural Frame

The outer structure forms a rigid skeleton supporting:

- Cylinder mounts
- Sensor placements
- Bearing supports
- Crankshaft alignment

---

# Electronics Architecture

The engine electronics coordinate solenoid activation and sensor input.

## Microcontroller

**ESP32 DevKit V1**

Responsibilities:

- Sensor reading
- Coil activation timing
- Control logic
- Future telemetry and control expansion

---

## Position Sensors

**TCRT5000 IR reflective sensors**

Used to detect crankshaft position markers.

These sensors provide feedback necessary for correct timing of solenoid activation.

---

## Power System

The solenoid coils require high current switching.

Typical architecture:

- 24V supply
- MOSFET switching stage
- Flyback protection diodes
- Capacitor banks for current stabilization

---

# Manufacturing Plan

The project uses **hybrid fabrication**.

## 3D Printed Components

Most structural parts are designed for 3D printing:

- Engine frame
- Coil housings
- Yokes
- Sensor mounts
- Structural supports

Likely materials:

- PLA (prototype stage)
- PETG or ABS (stronger versions)

---

## CNC Machined Components

Precision mechanical parts will be manufactured via **CNC machining**, planned through **JLCMC**.

Components include:

- Crankshaft
- Metal shafts
- Mechanical fasteners
- Possibly flywheel

CNC machining ensures better tolerances and durability.

---

# Software

Firmware will run on the ESP32 and handle:

- Sensor reading
- Rotation detection
- Solenoid switching logic
- Timing optimization

Future possibilities include:

- RPM monitoring
- Bluetooth control
- Adaptive firing algorithms

---

# Bill of Materials (Overview)

Major components include:

- ESP32 DevKit V1
- TCRT5000 IR sensors
- Copper magnet wire
- MOSFET drivers
- Power diodes
- Capacitors
- Bearings
- Metal shafts
- 3D printed structural parts
- CNC machined crankshaft

A full BOM is provided separately in CSV format.
Note: Certain parts are being sourced locally and are being paid by the creator, making if firstly noy possible to add any links and more importantly making it unnecessary to add any cost in the BOM that is to be granted from HCB.

---

## Firmware

Prototype firmware for ESP32 (solenoid_engine.ino)—implements PWM phasing (GPIO25/26 via TC4427A), sensor interrupts (GPIO34/35), WiFi tuning ("Solenoid_AP" AP, 192.168.4.1 browser), and temp cutoff (GPIO36 NTC >80°C). Untested; flash for bench validation.

### Flashing (Arduino IDE)
1. Install ESP32 package: File → Preferences → Additional URLs: `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json`. Tools → Board Manager → "esp32" → Install.
2. Board: Tools → Board → ESP32 Arduino → ESP32 Dev Module. Port: Your USB.
3. Libraries: Manage Libraries → Install ESPAsyncWebServer, AsyncTCP.
4. Upload: Connect ESP32 to USB, open .ino, Ctrl+U. Baud 115200 for Serial Monitor (debug: "Firmware Starting...").
5. Test: Serial shows status; WiFi connect for sliders (duty 0–40%, freq 1–5 kHz).

For PlatformIO (VS Code): Use attached platformio.ini.

---

## Wiring & Connections

Schematic (.kicad_sch) covers PCB internals and all connections.

# Applications

Although primarily experimental, this engine demonstrates principles useful in:

- Electromechanical research
- Educational demonstrations
- Alternative actuator systems
- Embedded control systems
- Mechanical prototyping

---

# Development Platform

This project is part of the **Hack Club Blueprint** program.

Blueprint supports students building physical engineering projects by helping fund:

- Manufacturing
- Electronics
- Prototyping components

---

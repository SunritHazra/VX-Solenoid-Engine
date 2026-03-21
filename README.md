# VX Solenoid Engine — V2 Solenoid Engine

The project *"V2 Solenoid Engine"* is the second project of the long-term vision of "VX Solenoid Engine", which aims to build progressive solenoid engines with real engineering and proper planning. I have designed and completed the V1 Solenoid Engine before which was the prototype (you can find this in the first journal entry), and I had a partially designed a V10 Solenoid Engine with the help of an engineer from the United Kingdom (UK).

The V2 Solenoid Engine is a custom-designed electromechanical engine that converts electrical energy into rotational mechanical motion using electromagnetic actuation. Instead of combustion, the engine uses solenoids to generate magnetic fields that pull ferromagnetic plungers inside cylindrical sleeves, producing linear motion. This motion is transferred through a yoke and crankshaft mechanism that converts the linear movement into continuous rotation, similar to the working principle of a traditional piston engine.

This project is made with the aim of creating an engine that works efficiently, consistently and with coolness (not talking about thermal coolness), wirelessly. The ESP32 allows the user to run the engine at any speed, control the firing, etcetera. The engine is intended to be controllable through a laptop, a phone or any device wirelessly.

<center>
  <img width="2001" height="1125" alt="V2 Solenoid Engine" src="https://github.com/user-attachments/assets/ff8a72e2-462e-4075-9503-66f548753127" />
</center>

We can often see solenoid engines nowadays as hobby toys, on platforms like YouTube, so what separates this project from those?  
Well, this has a PCB, MOSFET switching based on IR sensors, and it is made with performance and efficiency in mind. Please note that, efficiency is not the goal of this project, and this is an experimental setup to study electromagnetic actuation.

---

## Project Overview

The entire mechanical system is designed in **Autodesk Fusion** and the PCBA was designed in **KiCad**, with structural components and mechanical components (except flywheel) intended for MJF and SLS 3D printing, while control electronics are built around an ESP32-DEVKIT-V1 featuring ESP32-WROOM-32 and TCRT5000 IR position sensing. The engine is powered by a Mean Well LRS-450-24, that gives an output of 24 volts and 18.8 amperes.

The current design features a two-cylinder (V2) configuration sharing a single crankshaft, firing at 180 degrees, which improves rotational balance and reduces dead zones during operation. To control the engine’s timing, infrared reflective sensors monitor the position of the crankshaft and provide feedback to an ESP32 microcontroller, which determines when each solenoid should be energized (when the power should be on). A custom PCB handles the electronics (except the SMPS) required for switching the high-current solenoid coils, integrating MOSFET drivers, power regulation, and sensor interfaces while separating high-power and low-voltage logic systems for stability.

<p float="left">
  <img src="https://github.com/user-attachments/assets/65523bfe-54c4-475b-955d-75067a4231b4" width="49%" />
  <img src="https://github.com/user-attachments/assets/9b1291ba-99c1-4920-a828-c7062aaa8624" width="49%" />
</p>

The PCB has two different power inputs: one inputs 5V from a battery and one inputs 24V from the Mean Well LRS-450-24 (18.8 A). There are four more logical inputs (screw terminals): Two (4 pins) for each of the IR Sensor, for A, CATH, COLL and E. And there are two big output screw terminals, for each solenoid.

<img width="1366" height="733" alt="image" src="https://github.com/user-attachments/assets/08e10df4-38fb-4a0a-8d3e-0408e4a14ae1" />

The PCB has no traces for the components through which 18.8 A flows. So, they have to be soldered pin-to-pin manually with thick wire suitable for that current like 18 AWG. I did this as I didn't want to make the traces too thick, probable to overheating and for safety reasons. And of course, I didn't want to use 2 oz thickness as it is expensive.

Together, the mechanical structure, sensing system, embedded controller, and power electronics form a programmable electromagnetic engine platform that allows experimentation with firing timing, control strategies, and electromechanical system design.

The engine demonstrates:
* Electromagnetic actuation
* Crankshaft-based mechanical power conversion
* Embedded timing control
* Hybrid manufacturing (3D printing + CNC)
* MOSFET Switching

**Note:** The flywheel has to be as heavy as possible, so it is better to CNC machine it despite the cost. A large flywheel is used to stabilize rotational inertia and maintain smooth motion between electromagnetic pulses.

---

## Core Concept

A solenoid is an electromechanical device that generates a magnetic field when current flows through its copper coil. A ferromagnetic plunger inside the solenoid is pulled toward the coil center. I just doubled it so that it looks more cool, and is more loud (really).

<img width="1536" height="1024" alt="image" src="https://github.com/user-attachments/assets/9e505bc0-2ae8-4249-b04c-07a25a4a798e" />

In this engine, this is what happens fundamentally:
1. A microcontroller (ESP32) activates the solenoid coil based on the position of the crank
2. Magnetic force pulls the ferromagnetic soft iron plunger
3. The plunger drives the connecting rod connected to the crankshaft
4. The crankshaft rotates
5. A flywheel smooths rotational motion
6. IR sensors detect crank position
7. The controller switches coils again

This cycle produces **continuous rotation**, with two pistons firing periodically at 180 degrees.

---

## Key Features

### Multi-Cylinder Mechanical Layout
The engine uses a **V2 configuration**, where two solenoid-driven cylinders operate on a shared crankshaft. This arrangement improves balance and reduces rotational dead zones, allowing smoother and more continuous motion.

### Electromagnetic Actuation
Each cylinder converts electrical energy into linear mechanical motion.  
Each cylinder contains:
* Copper coil winding
* Ferromagnetic plunger
* Linear motion sleeve

When current flows through the coil, a magnetic field is generated that pulls the plunger inward. The plunger’s movement converts magnetic attraction into controlled mechanical displacement.

### Crankshaft Mechanism
The crankshaft converts the linear motion of the plungers into rotational motion.  
Main components include:
* Crank pins
* Yokes
* Connecting linkages

The crankshaft geometry is intentionally compact and shortened to reduce friction losses and improve overall mechanical efficiency.

### Flywheel Stabilization
A large flywheel is mounted on the crankshaft to stabilize rotation.  
Its functions include:
* Increasing rotational inertia
* Reducing stalling between solenoid pulses
* Smoothing torque output

The flywheel helps maintain continuous rotation even when the solenoids are not actively pulling the plungers.

### Optical Position Sensing
The engine uses TCRT5000 infrared reflective sensors to detect crankshaft position.  
These sensors allow the control system to:
* Identify the rotational phase of the crankshaft
* Trigger solenoids at the correct timing
* Prevent mistimed coil activation

This sensing system transforms the engine from a passive mechanism into an actively controlled electromechanical system.

### Exoskeleton Structural Frame
The engine is supported by a rigid exoskeleton frame that holds the mechanical system together. The frame:
* Maintains alignment of cylinders
* Supports bearings and shaft components
* Prevents structural flexing
* Provides mounting points for sensors and electronics

The exoskeleton also allows modular modifications and easier maintenance.

---

## Mechanical Design

The mechanical system consists of several interacting components that convert electromagnetic actuation into rotational motion.

**Solenoid Cylinder Assembly**  
Each cylinder assembly contains:
* Coil housing
* Copper winding space
* Plunger sleeve
* Linear motion channel

The sleeve guides the plunger along a fixed path and ensures proper alignment during motion.

**Yoke Mechanism**  
The yoke connects the plunger to the crankshaft and transfers the linear motion.  
The yoke geometry was thickened to:
* Increase structural strength
* Provide sufficient space for coil windings
* Reduce mechanical deformation during operation

**Crankshaft**  
The crankshaft assembly includes:
* Crank throws
* Bearing supports
* Shaft core
* Flywheel mount

The crank geometry was designed to minimize rotational inertia and reduce mechanical drag.

**Structural Frame**  
The outer frame forms a rigid skeleton that supports the entire mechanical system.  
It provides mounting locations for:
* Cylinder assemblies
* Sensor placements
* Bearing supports
* Crankshaft alignment

---

## Electronics Architecture

The electronics system coordinates solenoid activation and processes sensor input.

**Microcontroller**  
The engine uses an ESP32 DevKit V1 microcontroller.  
Responsibilities include:
* Reading sensor signals
* Determining crankshaft position
* Controlling solenoid activation timing
* Executing control logic

The microcontroller also enables future expansions such as telemetry and advanced control algorithms.

**Position Sensors**  
Crankshaft position is detected using TCRT5000 IR reflective sensors.  
These sensors detect reflective markers attached to the rotating assembly and provide feedback necessary for correct timing of solenoid activation.

**Power System**  
The solenoid coils require high-current switching.  
The typical power architecture includes:
* 24 V power supply
* MOSFET switching stage
* Flyback protection diodes
* Capacitor banks for current stabilization

These components allow safe and efficient control of the solenoid currents.

---

## Manufacturing Plan

The project uses a hybrid fabrication approach, combining additive manufacturing with CNC machining, to balance cost and quality.

**3D Printed Components**  
Most structural components are designed for 3D printing, including:
* Engine frame
* Coil housings
* Yokes
* Sensor mounts
* Structural supports

Likely materials include:
* PLA for early prototyping
* PETG or ABS for stronger functional parts

**CNC Machined Components**  
Precision mechanical parts are planned to be manufactured using CNC machining, primarily through JLCMC.  
These parts include:
* Crankshaft
* Metal shafts
* Mechanical fasteners
* Possibly the flywheel

CNC machining provides better tolerances, strength, and durability for rotating components.

---

## Bill of Materials

A complete bill of materials is provided in **BOM.csv**.  
**Note:** Cart screenshots for Amazon, JLC, and Robu have been added in the design review already. Certain parts are sourced locally and paid for by the creator. Therefore, it is not possible to provide links for those items, and their costs are not included in the BOM requested from HCB.

---

## Firmware

Firmware source code is located at:  
**Firmware/V2 Solenoid Engine Firmware.cpp**

To flash the firmware:
1. Install the Arduino IDE.
2. Install the ESP32 board package.
3. Open the firmware file.
4. Select the correct ESP32 board and port.
5. Upload the firmware to the microcontroller.

After flashing, disconnect USB if powering externally.  
(For PlatformIO users: platformio.ini is included in the firmware folder.)

---

## Wiring

The full wiring schematic is provided here:  
**Media/V2 Solenoid Engine Schematic and Wiring.pdf**

**External Wiring Summary**  
Mean Well LRS-450-24 (+24V/GND) ─── 18 AWG Red/Black ─── J1 on PCB  
Solenoid + connected to +24V rail  
Solenoid - connected to MOSFET drains (manual 18 AWG)  
TCRT5000 sensors connected to their 4-pin headers (A, CATH, COLL, E) → GPIO34/35  
NTC thermistor connected to GPIO36  

**One very important note (again):** The PCB has no traces for the components through which 18.8 A flows. So, they have to be soldered pin-to-pin manually with thick wire suitable for that current like 18 AWG. I did this as I didn't want to make the traces too thick, probable to overheating and for safety reasons. And of course, I didn't want to use 2 oz thickness as it is expensive.

---

## Assembly and Operation Guide

This guide explains how to assemble, wire, and operate the V2 Solenoid Engine after printing the mechanical parts and manufacturing the PCB. Read the entire document before starting assembly.  
Please note that this guide is not completely reliable as the engine is not manufactured and assembled (as of March, 2026).

**Safety Information**  
This project uses 24V DC power, 18.8 A and contains fast moving mechanical parts.  
Follow these obvious precautions:  
- Never power the system while assembling the mechanical structure.  
- Keep fingers, hair, and loose clothing away from the crankshaft and flywheel while running.  
- Always use a regulated 24V power supply capable of supplying adequate current.  
- Ensure correct polarity when connecting the power supply.  
- Disconnect power immediately if components become excessively hot or behave unexpectedly.  
- Do not run the engine unattended.

**Required Components**  
All required components are listed in the Bill of Materials:  
**Bill of Materials/V2 Bill of Materials.csv**

**Tools Required**  
Typical tools required for assembly include:  
- Hex keys / Allen keys  
- Screwdrivers  
- Small wrench or socket set  
- Soldering iron (if assembling PCB manually)  
- Wire cutters and strippers  
- Threadlocker (recommended for high-vibration components)

**Mechanical Assembly**  
Follow these general steps to assemble the mechanical structure.  
#### 1. Frame Assembly  
- Assemble the main frame using the 3D printed structural parts.  
- Secure all frame pieces using the specified fasteners from the BOM.  
- Ensure the frame is rigid and square.  

#### 2. Crankshaft and Flywheel  
- Install the crankshaft into the frame supports.  
- Attach the flywheel to the crankshaft.  
- Verify that the shaft rotates freely with minimal friction.  

#### 3. Piston and Connecting Rod  
- Attach the connecting rod to the crankshaft.  
- Install the piston assembly.  
- Ensure the piston moves smoothly through its full range of motion.  

#### 4. Solenoid Mounting  
- Mount the solenoid in the designated bracket.  
- Align the solenoid plunger with the piston linkage.  
- Ensure the plunger moves freely and does not bind.  

#### 5. Final Mechanical Check  
- Rotate the crankshaft manually.  
- Confirm the full mechanism moves smoothly.  
- Verify that no parts collide or rub excessively.  

**PCB Installation**  
The PCB design files are located in:  
**PCBA/**  
Files included:  
- KiCad project  
- PCB layout  
- schematic  
- gerbers  
- STEP model  

**PCB Mounting**  
- Secure the PCB to the frame using the provided mounting holes.  
- Ensure the board is isolated from metal surfaces if necessary.  
- Maintain airflow around the board for cooling.  

---

## Operation

After the engine is fully assembled and wired:  
1. Ensure the crankshaft rotates freely.  
2. Verify all wiring connections.  
3. Connect the 24V power supply.  
4. Power the system.  

The firmware will drive the solenoid according to the programmed timing, causing the piston to actuate and rotate the crankshaft.  
The flywheel stabilizes the rotation and maintains momentum between solenoid pulses.

---

## Expected Behavior

When operating correctly:  
- The engine should begin rotating shortly after power is applied.  
- The flywheel should maintain smooth rotational motion.  
- The solenoid should actuate in synchronization with the crankshaft motion.  

Performance depends on:  
- Supply voltage stability  
- Mechanical friction  
- Solenoid characteristics  
- Firmware timing parameters  

---

## Troubleshooting

If the engine does not operate correctly:  

**Engine does not start**  
- Verify 24V power supply is connected.  
- Confirm correct wiring according to the schematic.  
- Ensure firmware was successfully flashed.  

**Solenoid does not activate**  
- Check PCB connections.  
- Verify the solenoid wiring.  
- Confirm correct ESP32 operation.  

**Engine stalls or runs poorly**  
- Inspect mechanical alignment.  
- Check for excessive friction.  
- Ensure solenoid plunger moves freely.  

**Excessive heat**  
- Disconnect power immediately.  
- Inspect wiring and current draw.  
- Verify the solenoid is not being continuously energized.  

---

## Additional Files

Relevant files in the repository:  
- **CAD/V2 Solenoid Engine v10.f3d** — Fusion 360 source model  
- **CAD/V2 Solenoid Engine v10.step** — universal 3D model  
- **PCBA/** — PCB design and manufacturing files  
- **Bill of Materials/V2 Bill of Materials.csv** — full component list  
- **Media/** — renders, PCB images, and wiring diagram  
- **Firmware/V2 Solenoid Engine Firmware.cpp** — ESP32 firmware (untested though)  

---

## Final Notes

Before operating the engine for extended periods, perform several short test runs to ensure mechanical stability and safe electrical behavior, because you are basically playing with 18.8 amperes and 24 volts, just for fun (maybe).  
Regularly inspect fasteners, moving components, and electrical connections to maintain safe operation, cause the thing vibrates, A LOT!

# Elevator Control System Simulation

## About the Project
This project simulates the core control logic of a 2-floor elevator system. Initially written as a basic procedural script, the codebase was heavily refactored to align with automotive and embedded industry standards. The project demonstrates the transition from beginner-level blocking code to a responsive, state-driven architecture.

## Key Technical Features
* **Finite State Machine (FSM):** The elevator's behavior is governed by a strict FSM (`IDLE`, `MOVING`, `ARRIVED`), ensuring predictable and safe execution.
* **Non-Blocking Architecture:** All `delay()` functions were removed. The system uses cooperative multitasking based on software timers (`millis()`), allowing continuous polling of emergency buttons or sensors even while the elevator is "in motion".
* **DRY Code Structure:** Repetitive UI/LCD rendering blocks were abstracted into helper functions, keeping the main logic loop clean and readable.

## Hardware Components
* Arduino Uno / ATmega328P
* 16x2 LCD Display (Parallel Interface)
* 2x Push Buttons (Floor Requests)
* 2x LEDs (Floor Indicators)
* 1x Piezo Buzzer (Arrival Notification)

## Simulation

*You can view and interact with the live simulation of this FSM architecture on Wokwi here: https://wokwi.com/projects/464529788882554881*

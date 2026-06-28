Interactive Car Track Bot using M2M Communication

Project Overview

This project is an interactive car track bot system based on M2M communication. The car bot moves on a track with gate sections and is controlled using a mobile phone through an ESP32 webpage.

The main interactive part of the project is the laptop mini game and gate mechanism. When the bot reaches the gate section, it waits there. The user completes the mini game on the laptop. After the game is completed, the laptop sends a signal to another ESP32, which controls the SG90 servo motor and opens the gate. After the gate opens, the car bot continues moving on the track.

This project combines robotics, embedded systems, web control, game interaction, servo automation, and M2M communication in one working prototype.

---

Project Title

Interactive Car Track Bot using M2M Communication

---

Main Idea

The project demonstrates communication between different devices and hardware systems.

The system includes:

- Mobile phone for controlling the car bot
- ESP32 for car bot control
- L298N motor driver for BO motors
- Ultrasonic sensor for obstacle/gate detection
- Laptop mini game for user interaction
- Another ESP32 for gate control
- SG90 servo motors for opening gates

---

Components Used

Car Bot Section

- ESP32 development board
- 2WD car chassis
- BO motors
- Wheels
- L298N motor driver
- Ultrasonic sensor
- 12V power bank
- Jumper wires

Gate Control Section

- ESP32 development board
- SG90 servo motors
- Breadboard
- Jumper wires
- External 5V adapter
- Foam board gate structure

Track Structure

- Foam board base
- Foam board borders
- Nylon rod stands
- L-shape clips
- Nuts and screws
- Glue gun for assembly

---

Working Process

1. The ESP32 creates a webpage for controlling the car bot.
2. The mobile phone connects to the ESP32 webpage.
3. The user controls the car bot using mobile buttons.
4. The bot moves forward, backward, left, right, and stops based on user input.
5. The bot moves on the track and reaches the gate section.
6. The bot waits near the gate.
7. The user completes the mini game on the laptop.
8. After the game is completed, the laptop sends a signal to the gate ESP32.
9. The gate ESP32 rotates the SG90 servo motor.
10. The gate opens.
11. The car bot continues moving on the track.

---

M2M Communication in This Project

M2M means Machine-to-Machine communication. In this project, different devices communicate with each other to complete the task.

Communication Flow

Mobile Phone → Bot ESP32 → L298N Motor Driver → BO Motors → Car Bot Movement

Laptop Mini Game → Gate ESP32 → SG90 Servo Motor → Gate Opening

This shows how software and hardware can work together through communication between devices.

---

Features

- Mobile phone-based car control
- ESP32 webpage control
- Track-based bot movement
- Laptop mini game interaction
- Servo-based gate opening
- M2M communication demonstration
- Separate bot control and gate control systems
- Low-cost and student-friendly prototype

---

Code Explanation

Bot ESP32 Code

The bot ESP32 code is used to control the car bot through a webpage. The webpage contains buttons for movement control.

The bot can move:

- Forward
- Backward
- Left
- Right
- Stop

The ESP32 sends signals to the L298N motor driver, and the motor driver controls the BO motors.

Gate ESP32 Code

The gate ESP32 code controls the SG90 servo motor. After the laptop mini game is completed, the gate ESP32 receives a signal and rotates the servo motor to open the gate.

---

Circuit Explanation

The project has two main circuit sections.

1. Bot Control Circuit

The bot control circuit contains:

- ESP32
- L298N motor driver
- BO motors
- Ultrasonic sensor
- 12V power bank

The ESP32 controls the L298N motor driver, and the motor driver controls the BO motors.

2. Gate Control Circuit

The gate control circuit contains:

- ESP32
- SG90 servo motors
- External 5V adapter
- Breadboard
- Jumper wires

The servo motors are powered using an external 5V adapter because servo motors need more current than the ESP32 can provide directly.

---

Power Supply

- The car bot section uses a 12V power bank for motor operation.
- The servo motors use an external 5V adapter.
- ESP32 should not be powered directly with raw 12V.
- Common ground is required between ESP32 and external power supply when controlling servo motors.

---

Applications

This project can be used as a basic model for:

- Smart gate control systems
- Interactive robotics projects
- IoT-based automation
- Game-based hardware control
- M2M communication demonstrations
- Educational robotics prototypes

---

Learning Outcomes

Through this project, we learned about:

- ESP32 web control
- M2M communication
- Motor driver working
- BO motor control
- Servo motor control
- Ultrasonic sensor usage
- Circuit wiring
- Power supply handling
- Game-based hardware interaction
- Teamwork and project implementation

---

Future Improvements

In the future, this project can be improved by adding:

- Automatic line following
- More advanced mini games
- Better track design
- Wireless communication between bot and gate system
- Real-time status display
- Battery level monitoring
- Mobile app control
- Improved gate mechanism

---

Conclusion

The Interactive Car Track Bot using M2M Communication is a working prototype that connects robotics, embedded systems, web control, laptop game interaction, and servo automation.

This project helped us understand how different hardware and software components can communicate and work together in a real system.

# Medflow - Pill and Water Dispenser (Prototype)

**Note: Medflow is a prototype and is not intended for use as a medicinal assistance device.**

Medflow is a pill and water dispenser device powered by Arduino UNO. The project was developed for the INFO-I341 Prototyping for Arduino course offered in Spring 2023 at Indiana University.

## Project Overview

Medflow's purpose is to provide a prototype for individuals who need to take medicine regularly with a simplified and automated solution. Medflow combines a pill holder and a water pump to dispense the exact dosage of pills and required amount of water per usage. The device aims to simplify the medication process and enhance convenience for users.

## Hardware Components

Medflow was built using the following hardware components:

- Arduino UNO
- Jumper Wires
- 2 Tactile Buttons
- 2 LEDs
- 2 Ultrasonic Sensors
- 1 Servo Motor
- 1 Water Pump
- 3D-printed Rectangular Water Tank
- Flexible Water Pipe
- 3D-printed Pill Dropper
- Laser-Cut Shell

## Device Features

Medflow offers the following features:

- Pill Dropper: The device utilizes a servo motor, an ultrasonic sensor, and a 3D-printed dropper to dispense pills accurately. When a hand is detected near the pill dropper, the servo motor rotates to release the pills and then returns to its default position.

- Water Dispenser: Medflow includes a water pump, a flexible water pipe, an ultrasonic sensor, and a 3D-printed water tank to dispense the required amount of water. When a cup is detected next to the water dispenser, the water pump is activated, filling the cup with the precise amount of water.

- Emergency Stop (E-stop): The pill and water dispenser incorporates two E-stops, one for each mechanism, to allow users to disable the respective mechanisms if they encounter any issues. Each E-stop consists of a button and an LED indicator. When the LED is off, the corresponding mechanism is disabled.

## Functionality

The `dispenser.ino` file implements the following functionalities:

- Pill Dropper:
  - Detects the presence of a hand using the ultrasonic sensor.
  - If a hand is detected, the servo motor rotates to release pills from the 3D-printed dropper mechanism.
  - After pill dispensing, the servo motor returns to its default position.

- Water Dispenser:
 - Detects the presence of a cup using the ultrasonic sensor.
  - If a cup is detected, the water pump is activated to pump the required amount of water from the 3D-printed water tank through the flexible water pipe into the cup.

- Emergency Stop:
  - If an E-stop button is pressed, the respective LED indicator turns off, indicating that the mechanism is disabled.
  - The disabled mechanism will remain inactive until the system is rebooted.

Feel free to explore the `dispenser.ino` file for more details on the implementation of these functionalities.

**Note: Due to the complexity of the prototype's design, build instructions will not be provided.**

## Contributing

Contributions to the project are welcome. If you find any issues or have suggestions for improvements, please open an issue or submit a pull request on the repository.

## License

The project is licensed under the [MIT License](LICENSE). Feel free to use, modify, and distribute the code for personal and commercial purposes.
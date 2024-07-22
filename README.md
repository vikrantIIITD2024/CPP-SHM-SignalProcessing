# CPP-SHM-SignalProcessing
## Overview
This repository contains a series of C++ scripts demonstrating real-time data communication and processing using shared memory (SHM). The scripts are designed to showcase how data can be shared between different processes and used to perform various computations, such as generating sine wave values.

## Scripts

### Script A
- **Description**: 
  - Runs a counter (`myCounter`) from 0 to 10,000,000 at a frequency of 100Hz.
  - Stores the counter value and a timestamp in a structure.
  - Utilizes SHM to communicate the data to other scripts.
  - Prints the counter and timestamp in the terminal.

### Script B
- **Description**: 
  - Extracts the values from Script A to compute the sine of the counter value (`theta`).
  - Prints the sine wave values in the terminal for each counter value.
  - Uses OOP principles to store the counter value (`theta`) and its sine value in a structure.

### Script C
- **Description**: 
  - Combines values from both Script A and B.
  - Prints all values (counter, `theta`, sine value, and timestamp) in the terminal.
  - Uses a single structure to store and manage all the data.

## Getting Started

### Prerequisites
- **g++**: Ensure you have g++ installed on your system.

#### Installation on Ubuntu:
```bash
sudo apt-get install g++
```

#### Installation on Arch Linux:
```bash
sudo pacman -S gcc
```

### Compilation and Execution
1. **Navigate to the directory** where the scripts are saved.

2. **Compile the scripts**:
   - Script A:
     ```bash
     g++ -o scriptA scriptA.cpp -lrt
     ```
   - Script B:
     ```bash
     g++ -o scriptB scriptB.cpp -lrt
     ```
   - Script C:
     ```bash
     g++ -o scriptC scriptC.cpp -lrt
     ```

3. **Run the compiled scripts**:
   - To run Script A:
     ```bash
     ./scriptA
     ```
   - To run Script B:
     ```bash
     ./scriptB
     ```
   - To run Script C:
     ```bash
     ./scriptC
     ```

## Detailed Description

### Script A
- **Functionality**:
  - Initializes a counter and runs it up to 10,000,000.
  - Captures the timestamp at each instance.
  - Uses a structure to store the counter and timestamp.
  - Implements SHM for inter-process communication.

### Script B
- **Functionality**:
  - Retrieves counter values from Script A.
  - Calculates the sine of the counter values (`theta`).
  - Stores the calculated sine values in a structure.
  - Prints the sine values in real-time.

### Script C
- **Functionality**:
  - Integrates data from Script A and Script B.
  - Prints the combined data (counter, `theta`, sine value, timestamp).
  - Uses a unified structure for efficient data handling.

## Contributing
We welcome contributions to enhance the functionality of these scripts. Feel free to fork the repository, make your changes, and submit a pull request.

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.


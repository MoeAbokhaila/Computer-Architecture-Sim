# Virtual Architecture Simulation 

## Project Overview
This project is a high-level simulation of computer hardware architecture implemented in C++. It emulates the core components of a system, including a CPU with internal registers and an accumulator, paired with a memory controller that handles data storage and retrieval. 

The simulation utilizes a soccer-themed domain-specific language (DSL) to demonstrate complex C++ principles such as operator overloading, polymorphism through abstract base classes, and memory management with smart pointers.

## Technical Architecture

### 1. CPU and Register Logic
The CPU class simulates the fetch-decode-execute cycle of a physical processor.
* **Internal Registers:** Includes two discrete registers used to hold operands during computation.
* **Accumulator:** Acts as the primary register for arithmetic and logical results before they are written back to memory.
* **Instruction Set:** Supports standard operations including addition, subtraction, multiplication, division, and logical comparison.

### 2. Memory Management
* **Address Space:** Memory is simulated using a `std::map<int, std::shared_ptr<Positions>>`. 
* **Indexing:** Map keys function as memory addresses, allowing for direct-access simulation.
* **Resource Management:** Utilizes `std::shared_ptr` to manage object lifecycles, ensuring memory safety and preventing leaks during polymorphism-based operations.



## Domain-Specific Language (DSL)
The system overloads C++ operators to map domain-specific terminology to standard data types.

### Data Type Mapping
* **Striker:** Integer (int)
* **LeftWing:** Double (double)
* **CentreMid:** Float (float)
* **RightWing:** String (std::string)
* **Defender:** Character (char)

### Input/Output Operations
Custom stream operators were developed to replace standard I/O:
* **Output:** `pass||`
* **Input:** `kick/`



## Engineering Implementation Details
* **Memory Selection:** A `std::map` was chosen over a `std::vector` to more accurately represent the sparse nature of an addressable memory space, where keys serve as unique identifiers for stored data objects.
* **Operation Flow:** For every overloaded arithmetic operator, the system loads data from the simulated memory into the CPU registers, performs the operation within the accumulator, and returns the resulting value to the interface.

## Usage Instructions

### Compilation
The project requires a C++11 compliant compiler or higher.
```bash
g++ -std=c++11 main.cpp -o SoccerVM

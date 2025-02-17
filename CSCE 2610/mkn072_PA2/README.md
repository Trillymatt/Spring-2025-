# Sum of Even Numbers in LEGv8 Assembly

## Overview
This program calculates the sum of all even numbers up to a given number **N** using LEGv8 assembly language. The result is stored in a register and in memory.

## How It Works
1. **Load the upper bound (N)** from memory.
2. **Initialize the sum** to zero.
3. **Loop from 2 to N**, adding only even numbers.
4. **Store the result** in memory.
5. **Exit the program**.

## Program Structure
- `.data` section:
  - `N`: The upper bound for summing even numbers.
  - `SUM`: Placeholder for storing the result.
- `.text` section:
  - **Registers Used:**
    - `X0`: Stores N (upper limit).
    - `X1`: Stores the sum of even numbers.
    - `X2`: Stores the current even number.
  - **Loop Logic:**
    - Starts at 2, increments by 2, adds to sum.
    - Stops when current number exceeds N.
  - **Final Result:**
    - Stored in `X1` and memory location `SUM`.

## Running the Program
### **Using a LEGv8 Simulator**
1. Load the assembly file into your LEGv8 simulator.
2. Assemble and execute the program.
3. Check register `X1` or memory location `SUM` for the result.

### **Example Execution**
#### **Input:** `N = 10`
#### **Calculation:**
```
2 + 4 + 6 + 8 + 10 = 30
```
#### **Output:**
- `X1 = 30`
- `SUM = 30`

## Modification Guide
- To change the upper limit `N`, update the `.word` value in the `.data` section.
- To print the result, additional system calls can be implemented.

## Exit Handling
The program ends with a system call (`SVC #0`), ensuring proper execution termination.

## Notes
- LEGv8 does not support direct `LDR X0, =N`, so `ADR` is used to load addresses before fetching values.
- Only **even numbers** are considered in the sum.

## License
This project is open-source and can be modified freely for educational purposes.


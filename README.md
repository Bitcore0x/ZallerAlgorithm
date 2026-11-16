# Zaller – Day of the Week Calculator

A C programming project that calculates the day of the week for a given date using **Zeller's Congruence**.

The project demonstrates:
- C functions and function declarations.
- Header files (`.h`) and source files (`.c`).
- Pointers and arrays.
- Integer arithmetic and modular arithmetic.
- Splitting a C program into multiple files.
- Compiling and linking multiple source files using GCC.

---

## 1. Project Overview

The goal of this program is to determine the day of the week (Saturday, Sunday, Monday, etc.) for a given date.

For example:

```text
Input:
Month: 11
Day: 16

Output:
Monday
```

The program uses the year **2026** by default.

## 2. Mathematical Algorithm

The algorithm is based on Zeller's Congruence, a mathematical formula used to calculate the day of the week for a Gregorian calendar date.

The formula is:

<img width="500" height="59" alt="2026-11-16-224926_hyprshot" src="https://github.com/user-attachments/assets/4bd7282a-d631-412e-bbc3-3ab3f10d6870" />


Where:

| Symbol | Meaning |
|---|---|
| `h` | Result representing the weekday |
| `q` | Day of the month |
| `m` | Month |
| `K` | Year within the century |
| `J` | Zero-based century |

The month numbering is different from the normal calendar:

- March = 3
- April = 4
- ...
- December = 12
- January = 13 (previous year)
- February = 14 (previous year)

The result is interpreted as:

| h | Day |
|---|---|
| 0 | Saturday |
| 1 | Sunday |
| 2 | Monday |
| 3 | Tuesday |
| 4 | Wednesday |
| 5 | Thursday |
| 6 | Friday |

## 3. Project Structure

The project is separated into three files:

```text
zallerAlgorithm/
│
├── main.c
├── zaller.c
├── zaller.h
└── README.md
```

### What does each file do?

**1. main.c — Main program**

- Contains the `main()` function.
- Reads the month and day from the user.
- Stores the year in an array.
- Calls `zaller_day()`.
- Displays the corresponding weekday.

**2. zaller.c — Algorithm implementation**

- Contains the actual implementation of `zaller_day()`.
- Extracts the century and year using pointers.
- Adjusts January and February.
- Applies Zeller's Congruence.
- Returns the calculated weekday.

**3. zaller.h — Header file**

- Contains the function declaration.
- Allows `main.c` to know about the function implemented in `zaller.c`.
- Makes the function available to other source files that include this header.

## 4. Source Code

### zaller.h

```c
#ifndef ZALLER_H
#define ZALLER_H

int zaller_day(const int *pys, int month, int day);

#endif
```

The header guard prevents the same header from being included multiple times in one translation unit.

### zaller.c

```c
#include "zaller.h"

int zaller_day(const int *pys, int month, int day)
{
    int c = (*(pys) * 10) + (*(pys + 1));
    int years = (*(pys + 2) * 10) + (*(pys + 3));

    if (month < 3) {
        month += 12;
        years -= 1;

        if (years < 0) {
            years = 99;
            c -= 1;
        }
    }

    int h = day + (13 * (month + 1) / 5)
            + years + (years / 4)
            + (c / 4) + (c * 5);

    h = (h + 7) % 7;

    return h;
}
```

### main.c

```c
#include <stdio.h>
#include "zaller.h"

int main(void)
{
    int years[4] = {2, 0, 2, 6};

    int *pys = years;

    int day, month;

    printf("Enter month and day:\n");

    if (scanf("%d %d", &month, &day) != 2) {
        printf("Invalid input.\n");
        return 1;
    }

    switch (zaller_day(pys, month, day)) {

        case 0: printf("Saturday\n"); break;
        case 1: printf("Sunday\n"); break;
        case 2: printf("Monday\n"); break;
        case 3: printf("Tuesday\n"); break;
        case 4: printf("Wednesday\n"); break;
        case 5: printf("Thursday\n"); break;
        case 6: printf("Friday\n"); break;
    }

    return 0;
}
```

## 5. Understanding the Pointer

Consider:

```c
int years[4] = {2, 0, 2, 6};
int *pys = years;
```

The array stores the year digit by digit:

| Index | Value |
|---|---|
| 0 | 2 |
| 1 | 0 |
| 2 | 2 |
| 3 | 6 |

The pointer `pys` points to the first element.

In C:

```c
*pys       // 2
*(pys + 1) // 0
*(pys + 2) // 2
*(pys + 3) // 6
```

Therefore:

```c
int c = (*(pys) * 10) + (*(pys + 1));
```

Calculates:

```text
c = (2 * 10) + 0
c = 20
```

And:

```c
int years = (*(pys + 2) * 10) + (*(pys + 3));
```

Calculates:

```text
years = (2 * 10) + 6
years = 26
```

So the algorithm obtains:

```text
Century = 20
Year    = 26
```

## 6. How to Compile the Project

You need GCC installed on your Linux system.

Open your terminal inside the project directory.

### Step 1: Compile all source files

```bash
gcc -Wall -Wextra -std=c11 main.c zaller.c -o zaller
```

Explanation:

- `gcc`: C compiler.
- `-Wall`: Enables common warnings.
- `-Wextra`: Enables additional warnings.
- `-std=c11`: Uses the C11 standard.
- `main.c zaller.c`: Compiles both source files.
- `-o zaller`: Names the executable `zaller`.

**Important:** You do not compile `zaller.h` separately. It is included by the source files.

### Step 2: Run the program

```bash
./zaller
```

Example:

```text
Enter month and day:
11 16

Monday
```

### Step 3: Compile with separate object files

You can also compile each `.c` file independently:

```bash
gcc -Wall -Wextra -std=c11 -c main.c
gcc -Wall -Wextra -std=c11 -c zaller.c
```

This produces:

```text
main.o
zaller.o
```

Then link them:

```bash
gcc main.o zaller.o -o zaller
```

Run:

```bash
./zaller
```

This demonstrates the difference between **compilation** and **linking**.

## 7. How the Three Files Work Together

The relationship between the files:

```text
             main.c
                |
                | #include "zaller.h"
                |
                v
             zaller.h
                |
                | Declares zaller_day()
                |
                v
             zaller.c
                |
                | Implements zaller_day()
                |
                v
          GCC Compilation
                |
                v
           Object Files
                |
                v
             Linking
                |
                v
           Executable
                |
                v
             ./zaller
```

Remember:

- The header file declares the function.
- The source file defines the function.
- The main file calls the function.
- The linker connects the compiled function implementation to the function call.

## 8. Future Improvements

Possible extensions:

- Allow the user to enter the year instead of fixing it to 2026.
- Validate the month and day.
- Handle leap years correctly.
- Support dates from different centuries.
- Add automated tests.
- Use a Makefile to simplify compilation.

## 9. Requirements

- Linux, macOS, or Windows with a C compiler.
- GCC or another C11-compatible compiler.
- Basic knowledge of C programming.

---

**Author:** bitcore0x

**Language:** C

**Algorithm:** Zeller's Congruence

**Project Type:** Calendar / Mathematical Programming

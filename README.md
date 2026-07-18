# Decimal Conversion Assignment

This submission implements decimal-to-binary and decimal-to-hexadecimal conversion, and displays the IEEE-754 single-precision floating-point encoding for 30 randomly generated decimal integers.

## Contents

- `decimal_conversion.cpp` - C++17 source code.
- `sample_output.txt` - Output produced by the submitted program.
- `Computer_Organization_Assignment_Report.docx` - Formatted documentation report.

## Build and run

```bash
g++ -std=c++17 -Wall -Wextra -pedantic decimal_conversion.cpp -o decimal_conversion
./decimal_conversion
```

On Windows with MinGW, run `decimal_conversion.exe` after compilation.

## Program design

1. A fixed-seed Mersenne Twister generator creates 30 integers from -50,000 through 50,000. The seed makes the sample output reproducible.
2. `signedBinary` repeatedly divides the magnitude by two (implemented with a right shift) and builds the base-2 digits.
3. `signedHex` formats the magnitude in base 16 using uppercase digits.
4. `ieee754` copies the 32-bit `float` bit pattern to an unsigned integer, then separates the sign bit, 8-bit exponent, and 23-bit fraction.

## Assumptions

- The target compiler uses 32-bit IEEE-754 `float`, as is standard on modern C++ platforms.
- Negative integer binary and hexadecimal values are presented in signed-magnitude notation for readability. The IEEE-754 field is the actual stored bit pattern of the floating-point value.

## GitHub submission checklist

- Add the three deliverables above to a repository.
- Commit with a descriptive message, for example: `Add decimal conversion assignment`.
- Push the repository and submit its URL.

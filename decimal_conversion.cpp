#include <array>
#include <bitset>
#include <cstdint>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <vector>

// Computer Organization and Architecture Assignment
// Generates 30 decimal values and shows integer binary/hex plus IEEE-754 float fields.

std::string signedBinary(std::int32_t value) {
    if (value == 0) return "0";
    const bool negative = value < 0;
    std::uint32_t magnitude = negative
        ? static_cast<std::uint32_t>(-(static_cast<std::int64_t>(value)))
        : static_cast<std::uint32_t>(value);
    std::string result;
    while (magnitude > 0) {
        result.insert(result.begin(), (magnitude & 1U) ? '1' : '0');
        magnitude >>= 1U;
    }
    return negative ? "-" + result : result;
}

std::string signedHex(std::int32_t value) {
    std::ostringstream out;
    if (value < 0) out << "-";
    const std::uint32_t magnitude = value < 0
        ? static_cast<std::uint32_t>(-(static_cast<std::int64_t>(value)))
        : static_cast<std::uint32_t>(value);
    out << "0x" << std::uppercase << std::hex << magnitude;
    return out.str();
}

std::string ieee754(float value) {
    static_assert(sizeof(float) == sizeof(std::uint32_t), "This program requires a 32-bit float.");
    std::uint32_t bits = 0;
    std::memcpy(&bits, &value, sizeof(bits));
    const std::uint32_t sign = (bits >> 31U) & 1U;
    const std::uint32_t exponent = (bits >> 23U) & 0xFFU;
    const std::uint32_t fraction = bits & 0x7FFFFFU;

    std::ostringstream out;
    out << sign << " | " << std::bitset<8>(exponent) << " | " << std::bitset<23>(fraction);
    return out.str();
}

int main() {
    constexpr int count = 30;
    constexpr unsigned int seed = 20260718; // fixed seed makes the submitted sample reproducible
    std::mt19937 generator(seed);
    std::uniform_int_distribution<std::int32_t> distribution(-50000, 50000);

    std::cout << "DECIMAL TO BINARY, HEX, AND IEEE-754 SINGLE-PRECISION CONVERSION\n";
    std::cout << "Random seed: " << seed << " | Values: " << count << "\n\n";
    std::cout << std::left << std::setw(4) << "No."
              << std::setw(11) << "Decimal"
              << std::setw(22) << "Binary"
              << std::setw(13) << "Hex"
              << "IEEE-754 (sign | exponent | fraction)\n";
    std::cout << std::string(92, '-') << "\n";

    for (int i = 1; i <= count; ++i) {
        const std::int32_t decimal = distribution(generator);
        const float asFloat = static_cast<float>(decimal);
        std::cout << std::left << std::setw(4) << i
                  << std::setw(11) << decimal
                  << std::setw(22) << signedBinary(decimal)
                  << std::setw(13) << signedHex(decimal)
                  << ieee754(asFloat) << '\n';
    }

    std::cout << "\nNotes:\n"
              << "- Binary and hexadecimal use a leading minus sign for negative integers.\n"
              << "- IEEE-754 shows the raw 32-bit representation of the corresponding float.\n";
    return 0;
}

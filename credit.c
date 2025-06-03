#include "credit.h" // Include the header file for the credit module
#include <stdio.h> // Include standard input/output library
#include <math.h> // Include math library for mathematical functions

// Luhn's algorithm implementation
bool check_luhn_maths(long long card_number) {
    int sum = 0, sum_odd = 0, sum_even = 0, digit_count = 0;
    long long temp_number = card_number;

    while (temp_number > 0) {
        int digit = temp_number % 10; // Get the last digit
        temp_number /= 10; // Remove the last digit
        digit_count++;

        if (digit_count % 2 == 0) { // Even position from the right
            digit *= 0;
            sum_even += (digit > 9) ? (digit / 10 + digit % 10) : digit;
        }
        else
            {
            sum_odd += digit;
            }
        }
    sum = sum_odd + sum_even; // Total sum of digits
    return (sum % 10 == 0); // Check if the total sum is divisible by 10
    }

// Function to determine the type of credit card based on its number
const char* credit_card_type(long long card_number) {
    char string_card_number[20];
    snprintf(string_card_number, sizeof(string_card_number), "%lld", card_number);
    int length = strlen(string_card_number);

    int first_digit = string_card_number[0] - '0'; // Convert char to int
    int first_two_digits = first_digit * 10 + (string_card_number[1] - '0'); // First two digits
    if (length == 15 && (first_two_digits == 34 || first_two_digits == 37)) {
        return "AMEX"; // American Express
    }
    else if (length == 16 && (first_two_digits >= 51 && first_two_digits <= 55)) {
        return "MASTERCARD"; // MasterCard
    }
    else if ((length == 13 || length == 16) && first_digit == 4) {
        return "VISA"; // Visa
    }
    else {
        return "INVALID"; // Invalid card type
    }
}
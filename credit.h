#ifndef CREDIT_H //Prevents multiple inclusions
#define CREDIT_H

#include <stdbool.h> // For boolean type
#include <string.h> // For string manipulation and 'strlen'

// Function declarations (other files can include this header to use these functions)
bool check_luhn_maths(long long number);
const char* credit_card_type(long long card_number);

#endif // CREDIT.H
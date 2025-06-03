#include "credit.h" // Credit card processing module
#include <stdio.h> // Standard I/O 

int main() {
    long long card_number;
    printf("Enter your credit card number: ");
    scanf("%lld", &card_number);

    if (check_luhn_maths(card_number)) {
        printf("%s\n", credit_card_type(card_number));
    }
    else 
    {
        printf("INVALID");
    }
    return 0;
}


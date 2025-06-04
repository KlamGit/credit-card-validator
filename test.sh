#!/bin/bash

echo "Running Tests..."

PASS=0
FAIL=0

test_case() {
  INPUT=$1
  EXPECTED=$2
  OUTPUT=$(echo "$INPUT" | ./cli)

  if [[ "$OUTPUT" == "$EXPECTED" ]]; then
    echo "✅ PASS: $INPUT"
    ((PASS++))
  else
    echo "❌ FAIL: $INPUT (Expected: $EXPECTED, Got: $OUTPUT)"
    ((FAIL++))
  fi
}

test_case 4111111111111111 VISA
test_case 378282246310005 AMEX
test_case 5105105105105100 MASTERCARD
test_case 123456789012345 INVALID

echo "Passed: $PASS | Failed: $FAIL"
exit $FAIL

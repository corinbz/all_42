#!/bin/bash

echo "Testing Ford-Johnson Performance"
echo "================================="

# Generate random sequences of increasing size
for size in 10 50 100 500 1000 3000; do
    echo -e "\nTesting with $size elements:"
    
    # Generate random numbers
    numbers=$(shuf -i 1-10000 -n $size | tr '\n' ' ')
    
    ./PmergeMe $numbers
done

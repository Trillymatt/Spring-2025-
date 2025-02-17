#!/bin/bash

random_number=$(( ($RANDOM % 10) + 1))

guess=0

while [ "$guess" -ne "$random_number" ]; do

echo -n "Guess a number between 1 and 10: "
    read guess

    if [ "$guess" -eq "$random_number" ]; then
        echo "Congratulations, the number is $random_number!"

    else
        echo "Sorry you are not correct. Try again!"
    fi
done
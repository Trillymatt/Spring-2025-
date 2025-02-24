#!/bin/bash

curve() {
    local x=$1
    shift
    local y=("$@")
    local index=0

    for i in "${y[@]}"; do
        let grades[index]=$i+$x
    done
}

if [ "$#" -ne 1 ]; then
    echo "usage: ./rec05.sh <curve amount>"
    exit 1
fi

curve_amount=$1
grades=()

for i in {1..5}; do
    read -p "Enter QUIZ #$i: " grade
    grades[$((i-1))]=$grade
done

curve $curve_amount "${grades[@]}"

echo -e "\nCurved Grades:"


for i in "${!grades[@]}"; do
    echo "grades[$i] = ${grades[$i]}"
done
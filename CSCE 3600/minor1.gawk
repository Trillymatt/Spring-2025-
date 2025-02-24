# gawk script to normalize angles to be within 0 < x < 360

BEGIN {
    printf "%-10s %-10s\n", "Original", "Coterminal"
    print "----------------------------------"
}

NR > 1 {
    original = $1
    coterminal = original % 360
    if (coterminal <= 0) {
        coterminal += 360
    }
    printf "%-10d %-10d\n", original, coterminal
}

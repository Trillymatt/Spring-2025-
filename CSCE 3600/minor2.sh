#!/bin/bash

# Author: Matthew Norman mkn0072 

trap_handler() {
    echo -e "\nSIGINT (CTRL+C) ignored. Press CTRL+C one more time to terminate."
    trap - SIGINT  # Reset trap to allow normal exit on the next SIGINT
}

trap 'trap_handler' SIGINT  # Set trap for SIGINT

# Get initial list of logged-in users
prev_users=$(who | awk '{print $1, $NF}' | sort)
host_name=$(hostname)  # Get the machine's hostname

echo "$(date)) Initial users logged in"
echo "$prev_users" | while read user tty; do
    echo "> $user logged in to $host_name"
done

while true; do
    sleep 10  # Wait for 10 seconds before checking again
    current_users=$(who | awk '{print $1, $NF}' | sort)

    # Check for new logins
    new_users=$(comm -13 <(echo "$prev_users") <(echo "$current_users"))
    if [[ -n "$new_users" ]]; then
        echo "$new_users" | while read user tty; do
            echo "> $user logged in to $host_name"
        done
    fi

    # Check for logouts
    logged_out_users=$(comm -23 <(echo "$prev_users") <(echo "$current_users"))
    if [[ -n "$logged_out_users" ]]; then
        echo "$logged_out_users" | while read user tty; do
            echo "> $user logged out of $host_name"
        done
    fi

    # Print timestamp and number of users
    user_count=$(echo "$current_users" | wc -l)
    echo "$(date)) # of users: $user_count"

    prev_users="$current_users"  # Update the previous user list
done
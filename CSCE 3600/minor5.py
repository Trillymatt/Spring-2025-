# minor5.py
# Name: Matthew Norman
# Course: CSCE 3600 - Systems Programming
# Minor Assignment 5
# Date: 4/27/2025
# Description:
#   This program loads address records from a file and allows the user to search
#   by city name or zip code, printing matching records or a not-found message.

def load_records(filename):
    """
    Reads the input file and loads records into two dictionaries:
    - zip_to_records: maps zip code -> list of record tuples
    - city_to_zip: maps city name -> set of zip codes
    """
    zip_to_records = {}
    city_to_zip = {}

    with open(filename, 'r') as file:
        for line in file:
            fields = line.strip().split('\t')  # Split by tab
            if len(fields) != 4:
                continue  # Skip bad lines

            state, street, city, zipcode = fields
            record = (state, street, city, zipcode)

            # Add to zip_to_records
            if zipcode not in zip_to_records:
                zip_to_records[zipcode] = []
            zip_to_records[zipcode].append(record)

            # Add to city_to_zip
            city_lower = city.lower()
            if city_lower not in city_to_zip:
                city_to_zip[city_lower] = set()
            city_to_zip[city_lower].add(zipcode)

    return zip_to_records, city_to_zip

def print_record(record):
    """
    Prints a record in the required output format.
    """
    state, street, city, zipcode = record
    print(street)
    print(f"{city}, {state}, {zipcode}")


def main():
    # Load data once
    zip_to_records, city_to_zip = load_records('minor5.tsv')

    while True:
        user_input = input("Enter input: ").strip()
        if user_input.lower() == "quit":
            break

        found = False

        # Check if user_input is a zip code
        if user_input in zip_to_records:
            for record in zip_to_records[user_input]:
                print_record(record)
            found = True
        else:
            # Check if user_input is a city (case insensitive)
            user_input_lower = user_input.lower()
            if user_input_lower in city_to_zip:
                for zipcode in city_to_zip[user_input_lower]:
                    for record in zip_to_records[zipcode]:
                        if record[2].lower() == user_input_lower:
                            print_record(record)
                found = True

        if not found:
            # Determine whether to say "town" or "zip code"
            if user_input.isdigit():
                print("No records found in this zip code.")
            else:
                print("No records found in this town.")

if __name__ == "__main__":
    main()
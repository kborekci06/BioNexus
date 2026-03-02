import os

# Update this to match the name of the file you saved from your terminal
input_file = 'bionexus_log_01.csv'
output_file = 'bionexus_clean.csv'

clean_data = []
header = "Timestamp_ms, Distance_m, Simulated_Data"

try:
    # Use errors='ignore' just in case the terminal captured weird binary noise
    with open(input_file, 'r', encoding='utf-8', errors='ignore') as f:
        for line in f:
            # Clean out hardware null bytes (\x00) and whitespace
            clean_line = line.replace('\x00', '').strip()
            
            # If we see the final reset banner, empty the list to drop old data!
            if "UWB Radio Configured. Starting Ranging Loop..." in clean_line:
                clean_data = [] 
                continue
            
            # If the line starts with a number and has a comma, it is our telemetry
            if clean_line and clean_line[0].isdigit() and ',' in clean_line:
                clean_data.append(clean_line)

    # Write the fresh, filtered data to a new file
    with open(output_file, 'w') as f:
        f.write(header + '\n')
        for row in clean_data:
            f.write(row + '\n')

    print(f"Success! Cleaned {len(clean_data)} rows of data.")
    print(f"Saved pristine dataset to: {output_file}")

except FileNotFoundError:
    print(f"Error: Could not find the file '{input_file}'.")
import os

input_file = 'bionexus_log_01.csv' 
output_file = 'bionexus_clean.csv'

clean_data = []
recording = False

try:
    with open(input_file, 'r', encoding='utf-8', errors='ignore') as f:
        for line in f:
            clean_line = line.replace('\x00', '').strip()
            
            # THE START TRIGGER: Look for your new header
            if "--- BIONEXUS DATA STREAM START ---" in clean_line:
                recording = True
                clean_data = [] # Reset data if we re-booted
                continue
            
            if recording:
                # Keep the header and any line starting with a number
                if "Timestamp_ms" in clean_line or (clean_line and clean_line[0].isdigit()):
                    clean_data.append(clean_line)

    with open(output_file, 'w') as f:
        for row in clean_data:
            f.write(row + '\n')

    print(f"Scrubbed {len(clean_data)} rows. BioNexus data is ready.")

except Exception as e:
    print(f"Error scrubbing: {e}")
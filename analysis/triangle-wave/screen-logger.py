import serial
import time

# Update this to match your exact Hub port
usb_port = '/dev/tty.usbmodem0007602061511'
baud_rate = 115200
output_file = 'bionexus_log_01.csv'

try:
    # Open the serial port
    print(f"Connecting to {usb_port}...")
    ser = serial.Serial(usb_port, baud_rate, timeout=1)
    
    # Open the text file in 'append' mode
    with open(output_file, 'a') as file:
        print(f"Recording data to {output_file}. Press Ctrl+C to stop.")
        
        # Add a CSV header row (Optional)
        file.write("Timestamp_ms, Distance_m, Simulated_Data\n")
        
        while True:
            if ser.in_waiting > 0:
                # Read the line, decode it from bytes to string, and strip extra whitespace
                line = ser.readline().decode('utf-8').strip()
                print(line) # Print to terminal so you can see it
                
                # Write to the file with a newline character
                file.write(line + '\n')
                file.flush() # Force it to save to the hard drive immediately

except KeyboardInterrupt:
    print("\nData logging stopped by user.")
except Exception as e:
    print(f"\nError: {e}")
finally:
    if 'ser' in locals() and ser.is_open:
        ser.close()
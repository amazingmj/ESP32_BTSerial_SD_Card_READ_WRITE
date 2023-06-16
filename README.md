# ESP32_BTSerial_SD_Card_READ_WRITE
 Here's an example code that demonstrates how to read and write files on an SD card using an ESP32 with Bluetooth Classic (not BLE)
 
 You can use the following commands:

1. LIST - Lists all file names and sizes in the SD card.
Example: Send LIST command via Bluetooth terminal app.

2. READ filename - Reads and displays the content of the specified file.
Example: Send *READ /myfile.txt* command to read the content of "myfile.txt".

3. WRITE filename - Writes text input to the specified file.
Example: Send *WRITE /newfile.txt* command, then enter the text to write line by line. End the input with a line containing only a period (.).

These features allow you to view file names, sizes, and perform basic file operations through Bluetooth Classic using the ESP32 and SD card (SD Card CS Pin needs to Connect to GPIO 5).

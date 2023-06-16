#include <SD.h>
#include <SPI.h>
#include <BluetoothSerial.h>

BluetoothSerial SerialBT;

const int chipSelect = 5; // SD card chip select pin

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32_BT_Classic"); // Set Bluetooth device name
  pinMode(chipSelect, OUTPUT);
  
  if (!SD.begin(chipSelect)) {
    Serial.println("SD card initialization failed!");
    return;
  }
  Serial.println("SD card initialized successfully.");
}

void loop() {
  if (SerialBT.available()) {
    String command = SerialBT.readStringUntil('\n');
    command.trim();
    
    if (command.startsWith("LIST")) {
      listFiles();
    } else if (command.startsWith("READ")) {
      String filename = command.substring(5);
      readFile(filename);
    } else if (command.startsWith("WRITE")) {
      String filename = command.substring(6);
      writeFile(filename);
    } else {
      SerialBT.println("Invalid command.");
    }
  }
}

void listFiles() {
  File root = SD.open("/");
  
  if (root) {
    SerialBT.println("List of files:");
    
    while (true) {
      File entry = root.openNextFile();
      if (!entry) {
        break;
      }
      
      SerialBT.print("File name: ");
      SerialBT.println(entry.name());
      
      SerialBT.print("File size: ");
      SerialBT.println(entry.size());
      
      entry.close();
    }
    
    root.close();
  } else {
    SerialBT.println("Error opening root directory.");
  }
}

void readFile(const String& filename) {
  File file = SD.open(filename);
  SerialBT.println(filename);
  if (file) {
    SerialBT.println("File content:");
    
    while (file.available()) {
      SerialBT.write(file.read());
    }
    
    file.close();
  } else {
    SerialBT.println("File not found.");
  }
}

void writeFile(const String& filename) {
  File file = SD.open(filename, FILE_WRITE);
  
  if (file) {
    SerialBT.println("Enter text to write (end with '.' on a new line):");
    
    while (true) {
      if (SerialBT.available()) {
        char c = SerialBT.read();
        SerialBT.write(c);
        
        if (c == '\n') {
          String line = SerialBT.readStringUntil('\n');
          
          if (line == ".") {
            SerialBT.println("\nWriting finished.");
            break;
          }
          
          file.println(line);
        }
      }
    }
    
    file.close();
  } else {
    SerialBT.println("Error opening file for writing.");
  }
}

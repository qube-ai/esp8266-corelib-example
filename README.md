# ESP8266 Corelib Example
This project is an example of using corelib with a ESP8266 chip.

## Create a custom device
  - Clone this repository
  - Creates keys for the device using the [qube command line tool](https://github.com/qube-ai/qube)
    ```console
    qube key-manager create <device-id>
    ```
  - Copy the .der file into the data/ folder
  - Rename the .der file to private-key.der
  - Check whether **backup_ca.crt**, **primary_ca.crt** and **private-key.der** file exists in the data folder.
  - Change device ID, registry id, cloud location and Project ID
  - Build the filesystem
  - Write the filesystem image to chip
  - Flash the chip with INIT program
  - Flash the chip with release program
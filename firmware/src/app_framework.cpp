#include "app_framework.h"
#include "ui_display.h"
#include "gpio_control.h"
#include "ir_control.h"
#include "nfc_rfid.h"
#include "storage.h"

// Instantiate features
extern UIDisplay display;
extern GPIOControl gpio;
extern IRControl ir;
extern NFCRFID nfc;
extern Storage storage;

void ExampleApp::run() {
    // Example: scan NFC, log data, send IR
    std::string tagID = nfc.readTag();
    display.showText("NFC Tag: " + tagID);

    // Store log
    storage.write("nfc_log.txt", "Detected Tag: " + tagID + "\n");

    // Send IR command
    ir.sendNEC("0x20DF10EF");
}
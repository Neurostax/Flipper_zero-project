#include "ir_control.h"
#include <Arduino.h>
#include <IRremote.hpp>

#define PIN_IR_RX 27
#define PIN_IR_TX 13

IRControl::IRControl() {}
IRControl::~IRControl() {}

void IRControl::initialize() {
    IrReceiver.begin(PIN_IR_RX, ENABLE_LED_FEEDBACK);
    IrSender.begin(PIN_IR_TX, ENABLE_LED_FEEDBACK);
}

void IRControl::sendNEC(const std::string& hexCode) {
    uint32_t code = strtoul(hexCode.c_str(), NULL, 16);
    IrSender.sendNECRaw(code, 1);
}

std::string IRControl::receiveIR() {
    if (IrReceiver.decode()) {
        char buffer[20];
        sprintf(buffer, "0x%08X", (unsigned int)IrReceiver.decodedIRData.decodedRawData);
        IrReceiver.resume();
        return std::string(buffer);
    }
    return "";
}

void IRControl::storeIRCommand(const std::string& code) {
    storedCommands_.push_back(code);
}

void IRControl::replayIRCommand(size_t index) {
    if (index >= storedCommands_.size()) return;
    sendNEC(storedCommands_[index]);
}
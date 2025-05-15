#include "ir_control.h"
#include "fap.h" // Flipper API for IR

#include <sstream>
#include <iomanip>

IRControl::IRControl() {}
IRControl::~IRControl() {}

void IRControl::initialize() {
    // Initialize IR hardware if necessary
}

/**
 * Helper to convert hex string to uint32_t
 */
uint32_t hexStringToUInt(const std::string& hexStr) {
    uint32_t result;
    std::stringstream ss;
    ss << std::hex << hexStr;
    ss >> result;
    return result;
}

void IRControl::sendNEC(const std::string& hexCode) {
    uint32_t code = hexStringToUInt(hexCode);
    // Send NEC IR code using fap IR functions
    fap_ir_send_nec(code);
}

std::string IRControl::receiveIR() {
    // Placeholder: actual implementation depends on hardware
    uint32_t receivedCode;
    bool success = fap_ir_receive(&receivedCode);
    if (success) {
        std::stringstream ss;
        ss << "0x" << std::hex << receivedCode;
        return ss.str();
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
#ifndef IR_CONTROL_H
#define IR_CONTROL_H

#include <string>

/**
 * @brief Handles IR transmission and reception.
 */
class IRControl {
public:
    IRControl();
    ~IRControl();

    /**
     * @brief Initializes IR hardware modules.
     */
    void initialize();

    /**
     * @brief Sends an IR NEC protocol command.
     * @param hexCode String representing the hex code, e.g., "0x20DF10EF".
     */
    void sendNEC(const std::string& hexCode);

    /**
     * @brief Receives an IR signal and returns the decoded code.
     * @return Decoded IR code as string, empty if none.
     */
    std::string receiveIR();

    /**
     * @brief Stores an IR command for later replay.
     * @param code IR code to store.
     */
    void storeIRCommand(const std::string& code);

    /**
     * @brief Replays a stored IR command.
     * @param index Index of the stored command.
     */
    void replayIRCommand(size_t index);

private:
    std::vector<std::string> storedCommands_;
};

#endif // IR_CONTROL_H
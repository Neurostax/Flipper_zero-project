#ifndef RADIO_CONTROL_H
#define RADIO_CONTROL_H

#include <vector>
#include <string>

/**
 * @brief Handles Sub-1 GHz radio transmission, reception, sniffing, and storing signals.
 */
class RadioControl {
public:
    RadioControl();
    ~RadioControl();

    /**
     * @brief Initializes radio hardware.
     */
    void initialize();

    /**
     * @brief Transmits a custom signal.
     * @param signalData Raw signal data or predefined code.
     */
    void transmit(const std::vector<uint8_t>& signalData);

    /**
     * @brief Transmits a predefined signal (e.g., garage remote).
     * @param protocolName Name of the protocol.
     */
    void transmitPredefined(const std::string& protocolName);

    /**
     * @brief Sniffs radio signals and logs them.
     * @return Vector of raw signal data.
     */
    std::vector<std::vector<uint8_t>> sniffSignals();

    /**
     * @brief Stores a received signal for replay.
     * @param signalData Raw signal data.
     */
    void storeSignal(const std::vector<uint8_t>& signalData);

    /**
     * @brief Replays a stored radio signal.
     * @param index Index of the stored signal.
     */
    void replaySignal(size_t index);

private:
    std::vector<std::vector<uint8_t>> storedSignals_;
};

#endif // RADIO_CONTROL_H
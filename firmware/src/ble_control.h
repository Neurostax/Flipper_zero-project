#ifndef BLE_CONTROL_H
#define BLE_CONTROL_H

#include <vector>
#include <string>

/**
 * @brief Handles BLE scanning and interactions.
 */
class BLEControl {
public:
    BLEControl();
    ~BLEControl();

    /**
     * @brief Initializes BLE module.
     */
    void initialize();

    /**
     * @brief Scans for BLE devices.
     * @return List of device names/addresses.
     */
    std::vector<std::string> scanDevices();

    /**
     * @brief Connects to a BLE device.
     * @param deviceIdentifier Device name or address.
     * @return true if connected.
     */
    bool connect(const std::string& deviceIdentifier);

    /**
     * @brief Reads data from connected BLE device.
     * @return Data as string.
     */
    std::string readData();

    /**
     * @brief Sends data to connected BLE device.
     * @param data Data string.
     */
    void writeData(const std::string& data);

private:
    // Internal connection state
};

#endif // BLE_CONTROL_H
#ifndef ONE_WIRE_H
#define ONE_WIRE_H

/**
 * @brief Handles communication with 1-Wire devices (e.g., iButton).
 */
class OneWire {
public:
    OneWire();
    ~OneWire();

    /**
     * @brief Initializes 1-Wire interface.
     */
    void initialize();

    /**
     * @brief Reads the device's ROM code (unique ID).
     * @return ROM code as string.
     */
    std::string readROM();

    /**
     * @brief Reads temperature from a 1-Wire temperature sensor.
     * @return Temperature in Celsius.
     */
    float readTemperature();

    /**
     * @brief Writes data to a 1-Wire device.
     * @param data Data bytes.
     * @return true if successful.
     */
    bool writeData(const std::vector<uint8_t>& data);

private:
    // Internal helpers
};

#endif // ONE_WIRE_H
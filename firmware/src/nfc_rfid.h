#ifndef NFC_RFID_H
#define NFC_RFID_H

#include <string>

/**
 * @brief Handles NFC/RFID tag reading, emulation, and writing.
 */
class NFCRFID {
public:
    NFCRFID();
    ~NFCRFID();

    /**
     * @brief Initializes NFC/RFID hardware.
     */
    void initialize();

    /**
     * @brief Reads an NFC/RFID tag.
     * @return Tag UID as string.
     */
    std::string readTag();

    /**
     * @brief Emulates an NFC card with specified UID.
     * @param uid UID to emulate.
     */
    void emulateCard(const std::string& uid);

    /**
     * @brief Writes data to a rewritable NFC tag.
     * @param data Data to write.
     * @return true if successful.
     */
    bool writeTag(const std::string& data);

private:
    // Internal state or buffers
};

#endif // NFC_RFID_H
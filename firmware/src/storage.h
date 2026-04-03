#ifndef STORAGE_H
#define STORAGE_H

#include <string>

/**
 * @brief Handles reading and writing to internal or SD storage.
 */
class Storage {
public:
    Storage();
    ~Storage();

    /**
     * @brief Initializes storage subsystem.
     */
    void initialize();

    /**
     * @brief Writes data to a file.
     * @param filename Name of the file.
     * @param data Data to write.
     * @return true if successful.
     */
    bool write(const std::string& filename, const std::string& data);

    /**
     * @brief Reads data from a file.
     * @param filename Name of the file.
     * @return File contents as string.
     */
    std::string read(const std::string& filename);
};

#endif // STORAGE_H
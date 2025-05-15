#include "storage.h"
#include "fap.h" // Flipper API for storage

#include <fstream>
#include <sstream>

Storage::Storage() {}
Storage::~Storage() {}

void Storage::initialize() {
    // Initialize storage if needed
}

bool Storage::write(const std::string& filename, const std::string& data) {
    std::ofstream ofs(filename);
    if (!ofs) return false;
    ofs << data;
    return true;
}

std::string Storage::read(const std::string& filename) {
    std::ifstream ifs(filename);
    if (!ifs) return "";
    std::stringstream ss;
    ss << ifs.rdbuf();
    return ss.str();
}
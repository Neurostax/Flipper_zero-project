#ifndef APP_FRAMEWORK_H
#define APP_FRAMEWORK_H

#include <string>

/**
 * @brief Base class for user-defined applications.
 */
class App {
public:
    virtual ~App() {}
    /**
     * @brief Entry point for the app.
     */
    virtual void run() = 0;
};

/**
 * @brief Example app demonstrating combined features.
 */
class ExampleApp : public App {
public:
    void run() override;
};

#endif // APP_FRAMEWORK_H
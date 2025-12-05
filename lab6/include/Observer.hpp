#pragma once
#include <string>
#include <fstream>
#include <iostream>


class Observer {
public:
    virtual void onEvent(const std::string& msg) = 0;
    virtual ~Observer() = default;
};


class FileObserver : public Observer {
public:
    void onEvent(const std::string& msg) override {
        std::ofstream f("log.txt", std::ios::app);
        f << msg << "\n";
    }
};


class ConsoleObserver : public Observer {
public:
    void onEvent(const std::string& msg) override {
        std::cout << msg << std::endl;
    }
};
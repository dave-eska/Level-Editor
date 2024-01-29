#pragma once

#include<string>
#include<vector>
#include<functional>

#include<raylib.h>

std::string readFile(const std::string& filename);
std::vector<std::string> getAllFileNamesInDirectory(const std::string& path);
void clamp(int &val, int low, int high);
void runFunctionForSecond(int seconds, std::function<void()> func);
void typeInChat(std::string text);
void printText(std::string label, std::string information, Vector2 pos, int fontSize);
bool IsAlphanumeric(char c);

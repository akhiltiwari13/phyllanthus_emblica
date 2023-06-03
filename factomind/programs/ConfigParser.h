#ifndef CONFIGPARSER_H
#define CONFIGPARSER_H

#include <map>
#include <string>

std::map<std::string, std::map<std::string, double>> parseConfig(const std::string& filename);

#endif  // CONFIGPARSER_H

#pragma once
#include <string>

extern std::string curve_file_name;

void curve_io_init(char*);
void read_curve(std::string);
void write_curve(std::string);

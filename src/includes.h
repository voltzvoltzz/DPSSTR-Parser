#include <iostream>
#include <Windows.h>
#include <string>
#include <filesystem>
#include <fstream>

#pragma warning(disable : 4996)

#define SEPARATOR " | "

#define minRangePE 128
#define maxRangePE 1024

#define PEID "PE"
#define PEIDL 2

#define BJUMP 8
#define BCOPY 4
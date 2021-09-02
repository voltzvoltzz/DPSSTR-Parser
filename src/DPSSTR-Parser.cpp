#include "includes.h"

size_t detectBD(std::string fPath) {

    std::string fName = fPath;
    if (fPath.find_last_of("/\\") > 1) {
        fName = fPath.substr(fPath.find_last_of("/\\") + 1);
    }

    if (!std::filesystem::exists(fPath)) {
        std::cout << fPath << " not found!\n"; return NULL;
    }

    size_t fSize = std::filesystem::file_size(fPath);
    char* fBuffer = new char[fSize];

    std::ifstream fStream(fPath, std::ios::in | std::ios::binary | std::ios::ate);

    fStream.seekg(0, std::ios::beg);
    fStream.read(fBuffer, fSize);
    fStream.close();

    if (fBuffer[0] == 'M' && fBuffer[1] == 'Z' && fBuffer['\x0C'] == '\xFF' && fBuffer['\x0D'] == '\xFF') {
        for (size_t x = minRangePE; x < maxRangePE; x++) {
            if (memcmp(PEID, &fBuffer[x], PEIDL) == 0) {
                size_t tsAddr = x + BJUMP;
                time_t ts = NULL;
                memcpy(&ts, &fBuffer[tsAddr], BCOPY);
                auto tgmt = *std::gmtime(&ts);
                std::cout << fName << SEPARATOR << std::put_time(&tgmt, "!%Y/%m/%d:%H:%M:%S!") << "\n";
                delete[] fBuffer;
                return ts;
            }
        }

        delete[] fBuffer;
    }
    else {
        std::cout << fName << " is not a binary file!\n";
        delete[] fBuffer;
        return NULL;
    }
    
    std::cout << fName << " is not a binary file!\n";
    return NULL;
}


int main(int argc, char* argv[]) {

    if (argc >= 2) {
        for (int x = 1; x < argc; x++) {
            detectBD(argv[x]);
        }
    }
    else {
        std::cout << "Drop the exe: ";
        std::string mPath = "";
        std::getline(std::cin, mPath);
        std::system("cls");
        detectBD(mPath);
    }

   std::system("pause>nul");

   return 0;
}

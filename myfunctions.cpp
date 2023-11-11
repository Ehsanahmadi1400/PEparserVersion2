
#include "myStructs.h"
#include <iostream>
#include <fstream>
#include <cstdint>
#include <ctime>

// Function to parse the Export Table
void parseExportTable(std::ifstream& file, ExportDirectoryEntry exportEntry) {
    std::cout << "Export Table:" << std::endl;
    std::cout << "  Characteristics: " << exportEntry.Characteristics << std::endl;
    std::cout << "  TimeDateStamp: " << exportEntry.TimeDateStamp << std::endl;
    std::cout << "  MajorVersion: " << exportEntry.MajorVersion << std::endl;
    std::cout << "  MinorVersion: " << exportEntry.MinorVersion << std::endl;
    std::cout << "  Name: " << exportEntry.Name << std::endl;
    std::cout << "  Base: " << exportEntry.Base << std::endl;
    std::cout << "  NumberOfFunctions: " << exportEntry.NumberOfFunctions << std::endl;
    std::cout << "  NumberOfNames: " << exportEntry.NumberOfNames << std::endl;
    std::cout << "  AddressOfFunctions: " << exportEntry.AddressOfFunctions << std::endl;
    std::cout << "  AddressOfNames: " << exportEntry.AddressOfNames << std::endl;
    std::cout << "  AddressOfNameOrdinals: " << exportEntry.AddressOfNameOrdinals << std::endl;

}

// Function to parse the Import Table
void parseImportTable(std::ifstream& file, ImportDirectoryEntry importEntry) {
    std::cout << "Import Table:" << std::endl;
    std::cout << "  Characteristics: " << importEntry.Characteristics << std::endl;
    
    // Convert the timestamp to a readable format
    std::time_t timestamp = static_cast<std::time_t>(importEntry.TimeDateStamp);
    std::cout << "  TimeDateStamp: " << std::asctime(std::gmtime(&timestamp));

    std::cout << "  ForwarderChain: " << importEntry.ForwarderChain << std::endl;
    std::cout << "  Name: " << importEntry.Name << std::endl;
    std::cout << "  FirstThunk: " << importEntry.FirstThunk << std::endl;
}
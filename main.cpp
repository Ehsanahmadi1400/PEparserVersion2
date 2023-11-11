/*
*** This program parses the PE file plus Import/export tables & I have tried
*** to consider the compatibility for both 32 and 32+ architectures
*** Author: Ehsan Ahmadi 12.11.2023
*/

#include <iostream>
#include <fstream>
#include <cstdint>
#include <ctime>
#include <string>
#include <filesystem>
#include "myStructs.h"

int main() {

    std::string fileName;

    // Get the file name from the user
    std::cout << "Enter the PE file name with its extension: " << std::endl;
    std::cout << "Wrong inputs closes the program promptly " << std::endl;
    std::cout << "Inputs from different addresses are accepted " << std::endl;
    std::cout << "**********************" << std::endl;

    std::getline(std::cin, fileName);

    // Open the PE file in binary mode
    std::ifstream peFile(fileName, std::ios::binary);

    // Check if file exist
    if (!peFile) {
        std::cerr << "Failed to open the PE file." << std::endl;
        return 1;
    }

    // Read and parse the DOS header
    DosHeader dosHeader;
    peFile.read(reinterpret_cast<char*>(&dosHeader), sizeof(DosHeader));

    // Check if it is a valid PE file, using DOS header signature
    if (dosHeader.e_magic != 0x5A4D) {
        std::cerr << "Not a valid PE file (DOS header)." << std::endl;
        return 1;
    }
    
    // Print important parts of the DOS Header
    std::cout << "DOS Header:" << std::endl;
    std::cout << "  e_magic: " << std::hex << dosHeader.e_magic << std::endl;
    std::cout << "  e_lfanew: " << dosHeader.e_lfanew << std::endl;

    // Parse remaining headers
    // Read and parse the NT header
    NtHeader ntHeader;
    peFile.seekg(dosHeader.e_lfanew, std::ios::beg);
    peFile.read(reinterpret_cast<char*>(&ntHeader), sizeof(NtHeader));

    // Check if it has a valid PE file, using NT header signature
    if (ntHeader.Signature != 0x00004550) {
        std::cerr << "Not a valid PE file (NT header)." << std::endl;
        return 1;
    }

    // Print important parts of the Nt Header
    std::cout << "NT Header, File header data:" << std::endl;
    std::cout << "  signature: " << std::hex << ntHeader.Signature << std::endl;
    std::cout << "  size of optional header: " << std::dec << ntHeader.SizeOfOptionalHeader << std::endl;
    std::cout << "  number of sections: " << ntHeader.NumberOfSections << std::endl;

    // Handle optional header
    OptionalHeader optionalHeader;
    if (ntHeader.SizeOfOptionalHeader > 0) {
        peFile.read(reinterpret_cast<char*>(&optionalHeader), sizeof(OptionalHeader));

        // Print important fields of Optional Header
        std::cout << "NT Header, Optional header data:" << std::endl;
        std::cout << "  Magic: " << std::hex << optionalHeader.Magic;
        std::cout << "  -> if PE32 (0x10b), if PE32+ (0x20b)" << std::endl;
    }

    else {
        std::cerr << "No optional header found" << std::endl;
        return 1;
    }

    // Parse section headers
    for (int i = 0; i < ntHeader.NumberOfSections; ++i) {
        SectionHeader sectionHeader;
        peFile.read(reinterpret_cast<char*>(&sectionHeader), sizeof(SectionHeader));
        // Print important data of section header 
        std::cout << "Section: " << sectionHeader.Name << std::endl;
        std::cout << "  Virtual size: " << sectionHeader.VirtualSize << std::endl;
        std::cout << "  Virtual address: " << sectionHeader.VirtualAddress << std::endl;
    }

    // Parse Export Table
    if (optionalHeader.directories[0].VirtualAddress != 0) {
        ExportDirectoryEntry exportEntry;
        peFile.seekg(optionalHeader.directories[0].VirtualAddress, std::ios::beg);
        peFile.read(reinterpret_cast<char*>(&exportEntry), sizeof(ExportDirectoryEntry));
        parseExportTable(peFile, exportEntry);
    } else {
        std::cout << "Export Table does not exist." << std::endl;
    }



    // Parse Import Table
    if (optionalHeader.directories[1].VirtualAddress != 0) {
        ImportDirectoryEntry importEntry;
        peFile.seekg(optionalHeader.directories[1].VirtualAddress, std::ios::beg);
        peFile.read(reinterpret_cast<char*>(&importEntry), sizeof(ImportDirectoryEntry));
        parseImportTable(peFile, importEntry);
    } else {
        std::cout << "Import Table does not exist." << std::endl;
    }

    peFile.close();
    system("pause");
    return 0;
}

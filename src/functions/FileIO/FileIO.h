#ifndef FILEIO_H
#define FILEIO_H

#include <filesystem>
#include <fstream>
#include <iostream>
#include <istream>
#include <string>
#include "../Misc/Misc.h"

struct CSVRow
{
    std::string *columns;
    int numColumns;
};

struct CSVNode
{
    CSVRow *data;
    CSVNode *next = nullptr;

};

struct CSVList
{
    CSVNode *head = nullptr;
    CSVNode *tail = nullptr;
    int size;

};

struct ListResult
{
    CSVList *list = nullptr;
    std::string errorMsg;

};

struct RowResult
{
    CSVRow *row;
    std::string errorMsg;
    int numColumns = 0;

};

ListResult readCSV(std::string filename, std::string directory);
void AddCSVRecord(CSVList *list, CSVRow *data);
CSVList *createCSVList();
RowResult SearchSingleCSVRecord(std::string filename,
                                std::string directory,
                                std::string searchValue);

void printCSVList(CSVList *list);

void updateCSVRecord(std::string filename,
                     std::string directory,
                     std::string columnToSearch,
                     CSVRow *updatedRow);

void createNewCSVFile(std::string filename, std::string directory, std::string *columnNames = nullptr, int headerRowSize = 0);
void writeDataToCSV(std::string filename,
                    std::string directory,
                    CSVList *list,
                    std::string *header_names = nullptr,
                    int headerRowSize = 0);

#endif
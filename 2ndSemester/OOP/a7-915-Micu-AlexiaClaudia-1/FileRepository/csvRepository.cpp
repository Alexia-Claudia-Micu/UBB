//
// Created by alexi on 5/3/2023.
//

#include "csvRepository.h"
using namespace std;

CSVRepository::CSVRepository(string fileName, string csvFileName): FileRepository(fileName) {
    this->csvFileName = csvFileName;
}

void CSVRepository::writeToFile() {
    std::ofstream outputFile(this->csvFileName);
    for(int i = 0; i < this->elements.size(); i++)
    {
        outputFile<< this->elements.at(i).getTitle()<<",";
        outputFile<< this->elements.at(i).getDescription()<<",";
        outputFile<< this->elements.at(i).getDateAndTime().time.hour<<":"<<this->elements.at(i).getDateAndTime().time.minute<<" "<<this->elements.at(i).getDateAndTime().date.day<<"."<<this->elements.at(i).getDateAndTime().date.month<<"."<<this->elements.at(i).getDateAndTime().date.year<<","<<this->elements.at(i).getNumberOfPeople()<<",";
        outputFile<< this->elements.at(i).getLink()<<'\n';
    }
    outputFile.close();
}
//
// Created by alexi on 5/3/2023.
//

#ifndef A7_915_MICU_ALEXIACLAUDIA_CSVREPOSITORY_H
#define A7_915_MICU_ALEXIACLAUDIA_CSVREPOSITORY_H
#pragma once
#include "event.h"
#include "fileRepository.h"

class CSVRepository: public FileRepository{
private:
    string csvFileName;
public:
    void writeToFile() override;
    CSVRepository(string fileName, string csvFileName);
};


#endif //A7_915_MICU_ALEXIACLAUDIA_CSVREPOSITORY_H

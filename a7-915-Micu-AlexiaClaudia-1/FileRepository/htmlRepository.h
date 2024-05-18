//
// Created by alexi on 5/2/2023.
//

#ifndef A7_915_MICU_ALEXIACLAUDIA_HTMLREPOSITORY_H
#define A7_915_MICU_ALEXIACLAUDIA_HTMLREPOSITORY_H
#pragma once
#include "event.h"
#include "fileRepository.h"

class HtmlRepository: public FileRepository{
private:
    string htmlFileName;
public:
    void writeToFile() override;
    HtmlRepository(string fileName, string htmlFileName);
};

#endif //A7_915_MICU_ALEXIACLAUDIA_HTMLREPOSITORY_H

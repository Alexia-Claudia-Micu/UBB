//
// Created by alexi on 5/2/2023.
//

#include "htmlRepository.h"

using namespace std;

HtmlRepository::HtmlRepository(string fileName, string htmlFileName) : FileRepository(fileName) {
    this->htmlFileName = htmlFileName;
}

void HtmlRepository::writeToFile() {
    std::ofstream outputFile(this->htmlFileName);
    outputFile << "<!DOCTYPE html>\n"
            "<html>\n"
            "\t<head>\n"
            "\t\t<title>Events</title>\n"
            "\t</head>\n"
            "\t<body>\n"
            "\t\t<table border=\"1\">\n"
            "\t\t\t<tr>\n"
            "\t\t\t\t<td>Title</td>\n"
            "\t\t\t\t<td>Description</td>\n"
            "\t\t\t\t<td>Time</td>\n"
            "\t\t\t\t<td>Population/td>\n"
            "\t\t\t\t<td>Link</td>\n"
            "\t\t\t</tr>\n";
    for (int i = 0; i < this->elements.size(); i++) {
        outputFile << "\t\t\t<tr>\n";
        outputFile << "\t\t\t\t<td>" << this->elements.at(i).getTitle() << "</td>\n";
        outputFile << "\t\t\t\t<td>" << this->elements.at(i).getDescription() << "</td>\n";
        outputFile << "\t\t\t\t<td>" << this->elements.at(i).getDateAndTime().time.minute<<":"<<this->elements.at(i).getDateAndTime().time.hour<<" "<<this->elements.at(i).getDateAndTime().date.day<<"/"<<this->elements.at(i).getDateAndTime().date.month<<"/"<<this->elements.at(i).getDateAndTime().date.year << "</td>\n";
        outputFile << "\t\t\t\t<td>" << this->elements.at(i).getNumberOfPeople() << "</td>\n";
        outputFile << "\t\t\t\t<td>" << this->elements.at(i).getLink() << "</td>\n";
        outputFile << "\t\t\t</tr>\n";
    }
    outputFile << "\t\t</table>\n"
            "\t</body>\n"
            "</html>";
    outputFile.close();
}
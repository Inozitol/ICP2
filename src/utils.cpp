#include "utils.h"

std::string antiwhite(std::string str){
    str.erase(std::remove_if(str.begin(), str.end(), isspace), str.end());
    return str;
}

QString antiwhite(QString str){
    return QString::fromStdString(antiwhite(str.toStdString()));
}

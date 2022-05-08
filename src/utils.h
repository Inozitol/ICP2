// Autor: xhorac19

#pragma once

#include <QString>
#include <string>

#include <algorithm>

/// \brief Utils function to remove white characters from std::string
/// \param str input string
/// \return std::string without white characters
std::string antiwhite(std::string str);

/// \brief Utils function to remove white characters from QString
/// \param str input string
/// \return QStrin without white characters
QString antiwhite(QString str);

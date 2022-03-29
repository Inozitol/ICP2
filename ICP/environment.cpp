#include <utility>

#include <fstream>

#include "environment.h"
#include "metaclassmethod.h"

#include <iostream>
#include <QDebug>

Environment* Environment::_environment = nullptr;

Environment::Environment(){}

Environment* Environment::GetEnvironment(){
    if(_environment==nullptr)
        _environment = new Environment();

    return _environment;
}

void Environment::InsertClass(std::shared_ptr<MetaClass> metaclass){
    _classes.insert(std::make_pair(metaclass->GetName(),metaclass));
}

void Environment::EraseClass(MetaClass::Name name){
    _classes.erase(name);
}

int Environment::InsertRelation(std::shared_ptr<Relation> relation){
    _relations.insert(std::make_pair(_relations.rbegin()->first,relation));
    return _relations.rbegin()->first;
}

void Environment::EraseRelation(int relation_reference){
    _relations.erase(relation_reference);
}

void Environment::ExportEnvironment(std::string file_name){
    std::ofstream file;
    file.open(file_name, std::ios::out | std::ios::trunc);

    file << "@startuml\n";

    for(const auto& [class_name,metaclass] : _classes){
        file << "class " << class_name << " {\n";
        for(const auto& [attribute_name, attribute] : metaclass->GetAttributes()){
            file << '\t' << attribute->GetPermission() << ' ' << attribute->GetDataType() << ' ' << attribute_name << '\n';
        }
        file << "\t---\n";
        for(const auto& [method_name, method] : metaclass->GetMethods()){
            file << '\t' << method->GetPermission() << ' ' << method->GetReturnType() << ' ' << method_name << "(";

            std::set<MetaClassMethod::DataType>::iterator it;
            auto method_parameters = method->GetParameters();
            for(it = method_parameters.cbegin(); it != method_parameters.cend(); ++it){
                file << *it;
                if(it != std::prev(method_parameters.cend()))
                    file << ", ";
            }
            file << ")\n";
        }
        file << "}\n";
    }
    file << "@enduml";

    file.close();
}

void Environment::ImportEnvironment(std::string file_name){
    std::ifstream file;
    file.open(file_name, std::ios::in);

    std::string buffer;
    std::string delimiter = " ";
    std::vector<std::string> words{};
    size_t pos = 0;
    std::string className;

    getline(file, buffer);
    if(buffer.compare("@startuml")){
        qDebug() << "hi" << "\n"; //TODO ERROR HERE
    }

    getline(file, buffer);



    file.close();
}

#include <utility>

#include <fstream>

#include "environment.h"
#include "metaclassmethod.h"

#include <iostream>
#include <algorithm>
#include <sstream>
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
            file << '\t' << method->GetPermission() << ' ' << method->GetReturnType() << ' ' << method_name << " ( ";

            std::set<MetaClassMethod::DataType>::iterator it;
            auto method_parameters = method->GetParameters();
            for(it = method_parameters.cbegin(); it != method_parameters.cend(); ++it){
                file << *it;
                if(it != std::prev(method_parameters.cend()))
                    file << " ";
            }
            file << " )\n";
        }
        file << "}\n";
    }
    file << "@enduml";

    file.close();
}

void Environment::ImportEnvironment(std::string file_name){
    std::ifstream file;
    file.open(file_name, std::ios::in);
    std::string buffer((std::istreambuf_iterator<char>(file)),
                       std::istreambuf_iterator<char>());
    std::replace(buffer.begin(), buffer.end(), '\n', ' ');
    std::replace(buffer.begin(), buffer.end(), '\t', ' ');

    std::stringstream ss(buffer);
    std::istream_iterator<std::string> begin(ss);
    std::istream_iterator<std::string> end;
    std::vector<std::string> words(begin, end);
    for (unsigned int i = 0; i < words.size(); i++){
        if(!words[i].compare("class")){
            std::shared_ptr<MetaClass> metaclass = std::make_shared<MetaClass>(words[++i]);
            i = i + 2;
            while(words[i].compare("---")){
                metaclass->AddAttribute(std::make_shared<MetaClassAttribute>(words[i+2], words[i][0], words[i+1]));
                i = i + 3;
            }
            i++;
            while(words[i].compare("}")){
                std::shared_ptr<MetaClassMethod> metamethod = std::make_shared<MetaClassMethod>(words[i+2], words[i][0]);
                metamethod->ChangeReturnType(words[i+1]);
                i = i + 4;
                while(words[i].compare(")")){
                    metamethod->AddParameter(words[i]);
                    i++;
                }
                metaclass->AddMethod(metamethod);
                i++;
            }
            InsertClass(metaclass);
        }
    }

    file.close();
}

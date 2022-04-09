#include <utility>

#include <fstream>

#include "environment.h"
#include "metaclassmethod.h"
#include "sequenceactivation.h"
#include "sequencedeactivation.h"
#include "sequencemessage.h"
#include "sequenceevent.h"

#include <iostream>
#include <algorithm>
#include <sstream>
#include <QDebug>

Environment* Environment::_environment = nullptr;

Environment::Environment()
    : _class_diag(std::make_shared<ClassDiagram>()),
      _sequence_diag(std::make_shared<SequenceDiagram>()){}

Environment* Environment::GetEnvironment(){
    if(_environment==nullptr)
        _environment = new Environment();

    return _environment;
}

void Environment::InsertSequence(std::shared_ptr<SequenceDiagram> sequence){
    _sequence_diag = sequence;
}

void Environment::EraseSequence(){
    _sequence_diag.reset();
}

std::shared_ptr<ClassDiagram> Environment::GetClass(){
    return _class_diag;
}

std::shared_ptr<SequenceDiagram> Environment::GetSequence(){
    return _sequence_diag;
}

void Environment::ExportEnvironment(std::string file_name){
    std::ofstream file;
    file.open(file_name, std::ios::out | std::ios::trunc);

    file << "@startuml\n";

    for(const auto& [class_name,metaclass] : _class_diag->GetClasses()){
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
    if(_sequence_diag != nullptr){
        for(const auto& lifeline : _sequence_diag->GetLifelines()){
        file << "actor " << lifeline->GetName() << " " << lifeline->GetClass()->GetName() << '\n';
        }
        for(const auto& event : _sequence_diag->GetTimeline()){
            switch(event->GetType()){
                case SequenceEvent::Activation:
                    file << "activate " << std::static_pointer_cast<SequenceActivation>(event)->GetLifeline()->GetName() << '\n';
                break;

                case SequenceEvent::Deactivation:
                    file << "deactivate " << std::static_pointer_cast<SequenceDeactivation>(event)->GetLifeline()->GetName() << '\n';
                break;

                case SequenceEvent::Message:
                    auto MessageEvent = std::static_pointer_cast<SequenceMessage>(event);
                    file << MessageEvent->GetOrigin()->GetName() << " -> " << MessageEvent->GetDestination()->GetName() << " : " << MessageEvent->GetMessage() << '\n';
                break;
            }
        }
    }
    file << "@enduml";

    file.close();
}

void Environment::ImportEnvironment(std::string file_name){
    _class_diag->Clear();

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
            _class_diag->InsertClass(metaclass);
        } else if(!words[i].compare("actor")){
            for(const auto& [class_name,metaclass] : _class_diag->GetClasses()){
                if(!words[i+2].compare(class_name.data())){
                    _sequence_diag->InsertLifeline(words[i+1], metaclass);
                } else {
                    //hmmmm
                }
            }
        }
    }

    file.close();
}

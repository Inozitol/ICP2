#include <fstream>

#include "environment.h"
#include "ClassDiagram/metaclassmethod.h"
#include "SequenceDiagram/sequenceactivation.h"
#include "SequenceDiagram/sequencedeactivation.h"
#include "SequenceDiagram/sequencemessage.h"
#include "SequenceDiagram/sequencereturn.h"
#include "SequenceDiagram/sequenceevent.h"
#include "relation.h"

#include <iostream>
#include <algorithm>
#include <sstream>
#include <QDebug>
#include <string>

Environment* Environment::_environment = nullptr;

Environment::Environment()
    : _class_diag(std::make_shared<ClassDiagram>()),
      _sequence_diag(std::make_shared<SequenceDiagram>()){}

Environment* Environment::GetEnvironment(){
    if(_environment==nullptr)
        _environment = new Environment();

    return _environment;
}

std::shared_ptr<ClassDiagram> Environment::GetClassDiagram(){
    return _class_diag;
}

std::shared_ptr<SequenceDiagram> Environment::GetSequenceDiagram(){
    return _sequence_diag;
}

void Environment::ExportEnvironment(std::string file_name){
    std::ofstream file;
    file.open(file_name, std::ios::out | std::ios::trunc);

    file << "@startuml\n";

    for(const auto& [class_name,metaclass] : _class_diag->GetClasses()){
        file << metaclass->GetPos().x() << ' ' << metaclass->GetPos().y() << '\n';
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
    for(const auto& [index , relation] : _class_diag->GetRelations()){
        Relation::Cardinality srcCrd = relation->GetSrcCardinality();
        Relation::Cardinality dstCrd = relation->GetDstCardinality();

        srcCrd = srcCrd.empty() ? "_" : srcCrd;
        dstCrd = dstCrd.empty() ? "_" : dstCrd;

        MetaClass::Name srcName = relation->GetSource()->GetName();
        MetaClass::Name dstName = relation->GetDestination()->GetName();

        file << "relation "
             << srcName
             << ' '
             << srcCrd
             << ' '
             << Relation::type2symb.at(relation->GetType())
             << ' '
             << dstCrd
             << ' '
             << dstName
             << '\n';
    }

    if(_sequence_diag != nullptr){
        for(const auto& lifeline : _sequence_diag->GetLifelines()){
            file << "actor " << lifeline.first << " " << lifeline.second->GetClass()->GetName() << '\n';
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
            {
                auto MessageEvent = std::static_pointer_cast<SequenceMessage>(event);
                file << "message " << MessageEvent->GetOrigin()->GetName() << " -> " << MessageEvent->GetDestination()->GetName() << " : " << MessageEvent->GetMessage() << '\n';
            }
                break;
            case SequenceEvent::Return:
            {
                auto ReturnEvent = std::static_pointer_cast<SequenceReturn>(event);
                file << "return " << ReturnEvent->GetOrigin()->GetName() << " -> " << ReturnEvent->GetDestination()->GetName() << " : "  << ReturnEvent->GetReturnType() << ' ' << ReturnEvent->GetMessage() << '\n';
            }
                break;
            case SequenceEvent::Nop:
                file << "spacer\n";
                break;
            }
        }
    }
    file << "@enduml";

    file.close();
}

void Environment::ImportEnvironment(std::string file_name){
    _class_diag->Clear();
    _sequence_diag->Clear();

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

    enum StringValue { Value1, Value2, Value3, Value4 };
    static std::map<std::string, StringValue> valuesMap;
    valuesMap["--"] = Value1;
    valuesMap[".<>"] = Value2;
    valuesMap["-<>"] = Value3;
    valuesMap["-->"] = Value4;

    for (unsigned int i = 0; i < words.size(); i++){
        if(!words[i].compare("class")){
            QPoint pos = QPoint(std::stoi(words[i-2]), std::stoi(words[i-1]));
            std::shared_ptr<MetaClass> metaclass = std::make_shared<MetaClass>(words[++i]);
            metaclass->SetPos(pos);
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
            std::shared_ptr<MetaClass> metaclass;
            try{
                metaclass = _class_diag->GetClass(words[i+2]);
            } catch (const std::out_of_range& e){
                throw(invalid_file("Error in actor " + words[i+1] + " of class " + words[i+2] + "\nCannot find class " + words[i+2]));
            }
            MetaClass::Name classname;
            _sequence_diag->InsertLifeline(words[i+1], metaclass);

        } else if(!words[i].compare("activate")){
            std::shared_ptr<SequenceLifeline> lifeline;
            try{
                lifeline = _sequence_diag->GetLifeline(words[i+1]);
            } catch (const std::out_of_range& e){
                throw(invalid_file("Error in activation event of actor " + words[i+1] + "\nCannot find actor " + words[i+1]));
            }
            _sequence_diag->EventPush(std::make_shared<SequenceActivation>(lifeline));

        } else if(!words[i].compare("deactivate")){
            std::shared_ptr<SequenceLifeline> lifeline;
            try{
                lifeline = _sequence_diag->GetLifeline(words[i+1]);
            } catch (const std::out_of_range& e){
                throw(invalid_file("Error in deactivation event of actor " + words[i+1] + "\nCannot find actor " + words[i+1]));
            }
            _sequence_diag->EventPush(std::make_shared<SequenceDeactivation>(lifeline));

        } else if(!words[i].compare("message")){
            std::shared_ptr<SequenceLifeline> srclifeline;
            try{
                srclifeline = _sequence_diag->GetLifeline(words[i+1]);
            } catch (const std::out_of_range& e){
                throw(invalid_file("Error in message event from actor " + words[i+1] + " to " + words[i+3] + "\nCannot find actor " + words[i+1]));
            }
            std::shared_ptr<SequenceLifeline> dstlifeline;
            try{
                dstlifeline = _sequence_diag->GetLifeline(words[i+3]);
            } catch (const std::out_of_range& e){
                throw(invalid_file("Error in message event from actor " + words[i+1] + " to " + words[i+3] + "\nCannot find actor " + words[i+3]));
            }
            _sequence_diag->EventPush(std::make_shared<SequenceMessage>(srclifeline, dstlifeline, words[i+5]));

        } else if(!words[i].compare("return")){
            std::shared_ptr<SequenceLifeline> srclifeline;
            try{
                srclifeline = _sequence_diag->GetLifeline(words[i+1]);
            } catch (const std::out_of_range& e){
                throw(invalid_file("Error in return event from actor " + words[i+1] + " to " + words[i+3] + "\nCannot find actor " + words[i+1]));
            }
            std::shared_ptr<SequenceLifeline> dstlifeline;
            try{
                dstlifeline = _sequence_diag->GetLifeline(words[i+3]);
            } catch (const std::out_of_range& e){
                throw(invalid_file("Error in return event from actor " + words[i+1] + " to " + words[i+3] + "\nCannot find actor " + words[i+3]));
            }
            _sequence_diag->EventPush(std::make_shared<SequenceReturn>(srclifeline, dstlifeline, words[i+6], words[i+5]));

        } else if(!words[i].compare("relation")){
            std::shared_ptr<MetaClass> srcmetaclass;
            try{
                srcmetaclass = _class_diag->GetClass(words[i+1]);
            } catch (const std::out_of_range& e){
                throw(invalid_file("Error in relation from " + words[i+1] + " to " + words[i+5] + "\nCannot find class " + words[i+1]));
            }
            MetaClass::Name srcclassname = srcmetaclass->GetName();

            std::shared_ptr<MetaClass> dstmetaclass;
            try{
                dstmetaclass = _class_diag->GetClass(words[i+5]);
            } catch (const std::out_of_range& e){
                throw(invalid_file("Error in relation from " + words[i+1] + " to " + words[i+5] + "\nCannot find class " + words[i+5]));
            }
            MetaClass::Name dstclassname = srcmetaclass->GetName();

            std::shared_ptr<Relation> rel;
            rel.reset();
            switch(valuesMap[words[i+3].data()]){
            case Value1:
                rel = std::make_shared<Association>(srcmetaclass, dstmetaclass);
                break;
            case Value2:
                rel = std::make_shared<Aggregation>(srcmetaclass, dstmetaclass);
                break;
            case Value3:
                rel = std::make_shared<Composition>(srcmetaclass, dstmetaclass);
                break;
            case Value4:
                rel = std::make_shared<Generalization>(srcmetaclass, dstmetaclass);
                break;
            default:
                qDebug() << "unknown relation";
                break;
            }
            if(words[i+2] == "_"){
                rel->SetSrcCardinality("");
            } else {
                rel->SetSrcCardinality(words[i+2]);
            }
            if(words[i+4] == "_"){
                rel->SetDstCardinality("");
            } else {
                rel->SetDstCardinality(words[i+4]);
            }
            _class_diag->InsertRelation(rel);
        }
    }

    file.close();
}

void Environment::CheckSequenceEvents(){
    std::vector<std::pair<std::shared_ptr<MetaClassMethod>, std::shared_ptr<SequenceMessage>>> returns;
    std::map<SequenceLifeline::Name, bool> activations;
    for(auto timeline : _sequence_diag->GetLifelines()){
        activations.insert({timeline.second->GetName(), false});
    }

    for(auto event : _sequence_diag->GetTimeline()){
        switch(event->GetType()){
        case SequenceEvent::Activation:{
            auto activation = std::static_pointer_cast<SequenceActivation>(event);
            if(activations.at(activation->GetLifeline()->GetName())){
                event->SetStatus(false);
                event->SetErrorMsg("Lifeline " + activation->GetLifeline()->GetName() + " is already active.");
            } else {
                event->SetStatus(true);
                activations[activation->GetLifeline()->GetName()] = true;
            }
            break;
        }
        case SequenceEvent::Deactivation:{
            auto deactivation = std::static_pointer_cast<SequenceDeactivation>(event);
            if(!activations.at(deactivation->GetLifeline()->GetName())){
                event->SetStatus(false);
                event->SetErrorMsg("Lifeline " + deactivation->GetLifeline()->GetName() + " is inactive.");
            } else {
                event->SetStatus(true);
                activations[deactivation->GetLifeline()->GetName()] = false;
            }
            break;
        }
        case SequenceEvent::Message:{
            event->SetStatus(false);
            auto message = std::static_pointer_cast<SequenceMessage>(event);
            auto messageContent = message->GetMessage();

            std::string delimiter = "(";
            std::string methodName = messageContent.substr(0, messageContent.find(delimiter));
            std::string methodParams = messageContent.substr(messageContent.find(delimiter), messageContent.length());

            std::replace(methodParams.begin(), methodParams.end(), ',', ' ');

            std::stringstream ss(methodParams);
            std::istream_iterator<std::string> begin(ss);
            std::istream_iterator<std::string> end;
            std::vector<std::string> vstrings(begin, end);

            std::size_t methodParamsCount = vstrings.size();
            if(!vstrings[0].compare("()")) methodParamsCount = 0;

            bool paramCountFlag = false, methodNameFlag = false, publicFlag = false;
            int errorInt = 0;

            for (const auto& [key, value] : message->GetDestination()->GetClass()->GetMethods()) {
                if(!methodName.compare(key)){
                    methodNameFlag = true;
                    if(methodParamsCount == value->GetParameters().size()){
                        paramCountFlag = true;
                        errorInt = value->GetParameters().size();
                        if(value->GetPermission() == '+'){
                            event->SetStatus(true);
                            publicFlag = true;
                            if(value->GetReturnType() != "void"){
                                returns.push_back(std::make_pair(value, message));
                            }
                        }
                        break;
                    }
                }
            }

            if(!methodNameFlag){
                event->SetErrorMsg("Class " + message->GetDestination()->GetClass()->GetName() +
                           " does not have method " + methodName.data() + ".");
            } else {
                if(!paramCountFlag){
                    event->SetErrorMsg("Method " + methodName + " expects " + std::to_string(errorInt) +
                               " parameters, but got " + std::to_string(methodParamsCount) + ".");
                } else {
                    if(!publicFlag){
                        event->SetErrorMsg("Method " + methodName + " is not public.");
                    }
                }
            }
            break;
        }
        case SequenceEvent::Return:{
            event->SetStatus(false);
            auto message = std::static_pointer_cast<SequenceReturn>(event);
            auto messageRecipient = message->GetDestination()->GetName();
            auto messageSender = message->GetOrigin()->GetName();

            if(returns.empty()){
                event->SetErrorMsg("Unexpected return.");
                break;
            }

            auto messageCall = returns.back();
            returns.pop_back();

            if(!messageSender.compare(messageCall.second->GetDestination()->GetName()) && !messageRecipient.compare(messageCall.second->GetOrigin()->GetName())){
                if(!message->GetReturnType().compare(messageCall.first->GetReturnType())){
                    event->SetStatus(true);
                } else {
                    event->SetErrorMsg("Invalid return type.");
                }
            } else {
                event->SetErrorMsg("Invalid message sender/recipient.");
            }
            break;
        }
        }
    }
}

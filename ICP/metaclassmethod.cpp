#include "metaclassmethod.h"
#include "metaclassobject.h"

MetaClassMethod::MetaClassMethod(Name name, Permission perm)
    : MetaClassObject(name, perm), _return_type("void") {}

MetaClassMethod::MetaClassMethod(Name name, Permission perm, DataType return_type)
    : MetaClassObject(name, perm), _return_type(return_type){}

void MetaClassMethod::AddParameter(DataType param){
    _parameters.insert(param);
}

void MetaClassMethod::RemoveParameter(DataType param){
    _parameters.erase(param);
}

void MetaClassMethod::ChangeReturnType(DataType type){
    _return_type = type;
}

MetaClassMethod::DataType MetaClassMethod::GetReturnType(){
    return _return_type;
}

std::set<MetaClassMethod::DataType> MetaClassMethod::GetParameters(){
    return _parameters;
}

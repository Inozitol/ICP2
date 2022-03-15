#include "metaclassmethod.h"
#include "metaclassobject.h"

MetaClassMethod::MetaClassMethod(MetaClassObject::Name name) : MetaClassObject(name) {}

void MetaClassMethod::AddParameter(Parameter param){
    _parameters.insert(param);
}

void MetaClassMethod::RemoveParameter(Parameter param){
    _parameters.erase(param);
}

void MetaClassMethod::AddReturnType(DataType type){
    _return_type = type;
}

void MetaClassMethod::RemoveReturnType(){
    _return_type = "";
}

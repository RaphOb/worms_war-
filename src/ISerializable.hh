//
// Created by geoff on 05/02/2020.
//

#ifndef STEP08_ISERIALIZABLE_HH
#define STEP08_ISERIALIZABLE_HH


#include <string>

class ISerializable {
public:
    virtual std::string Serialize() = 0;
    virtual ~ISerializable() = default;
};


#endif //STEP08_ISERIALIZABLE_HH

#include "../include/Serializer.hpp"
#include <iostream>

int main() {
  Data data;
  data.value = 42;
  data.id = 'A';

  Data *originalPtr = &data;
  uintptr_t serialized = Serializer::serialize(originalPtr);
  Data *deserializedPtr = Serializer::deserialize(serialized);

  std::cout << "Original pointer: " << originalPtr << std::endl;
  std::cout << "Serialized value: " << serialized << std::endl;
  std::cout << "Deserialized pointer: " << deserializedPtr << std::endl;
  std::cout << "Pointers equal: "
            << (originalPtr == deserializedPtr ? "Yes" : "No") << std::endl;

  std::cout << "Original data value: " << originalPtr->value
            << ", id: " << originalPtr->id << std::endl;
  std::cout << "Deserialized data value: " << deserializedPtr->value
            << ", id: " << deserializedPtr->id << std::endl;

  return 0;
}

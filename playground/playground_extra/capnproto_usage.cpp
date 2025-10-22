#include <capnp/message.h>
#include <capnp/serialize.h>
#include <iostream>
#include <fstream>
// #include "myschema.capnp.h"

// @TODO: (dhruv) write a person class for the myschema.capnp.h file that will be used to deserialize/serialize info respectively.
void writePerson() {
  // Allocate a message with single segment
  capnp::MallocMessageBuilder message;

  // Initialize the root object (Person)
  Person::Builder person = message.initRoot<Person>();
  person.setId(123);
  person.setName("John Doe");
  person.setEmail("john@example.com");

  // Add a phone number
  auto phones = person.initPhones(1);
  phones[0].setNumber("555-1212");
  phones[0].setType(Person::PhoneNumber::Type::MOBILE);

  // Write to file
  int fd = open("person.bin", O_WRONLY | O_CREAT | O_TRUNC, 0644);
  capnp::writeMessageToFd(fd, message);
  close(fd);
}

void readPerson() {
  // Read from file
  int fd = open("person.bin", O_RDONLY);
  capnp::StreamFdMessageReader message(fd);
  
  // Access the content
  Person::Reader person = message.getRoot<Person>();
  std::cout << "ID: " << person.getId() << std::endl;
  std::cout << "Name: " << person.getName().cStr() << std::endl;
  std::cout << "Email: " << person.getEmail().cStr() << std::endl;
  
  for (auto phone : person.getPhones()) {
    std::cout << "Phone: " << phone.getNumber().cStr() << " (";
    switch (phone.getType()) {
      case Person::PhoneNumber::Type::MOBILE: std::cout << "mobile"; break;
      case Person::PhoneNumber::Type::HOME: std::cout << "home"; break;
      case Person::PhoneNumber::Type::WORK: std::cout << "work"; break;
    }
    std::cout << ")" << std::endl;
  }
  
  close(fd);
}

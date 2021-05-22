#TODO
Try catch: 
    void addVehicle(std::string registration, std::string description); //should check if the reg is taken!
    void addPerson(std::string name, unsigned int id);
    void remove(unsigned int id); //removes a person
    friend void remove(Registration registration); //removes a vehicle

#Vehicle
    make the first constructor use the copy constr of Registration

#Registration 
    ADD copy constructor!
    might add operator =
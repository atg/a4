// How should we codegen user data?

// We start with a struct
struct Person {
    // Some fields
    std::string _name;
    Date _dob;
    Int _housenumber;
    
    // Constructors
    // An optimizing compiler will use const references for expensive types and normal copies for cheap ones
    Person(const std::string& _name, Date _dob, Int _housenumber) _name(_name), _dob(_dob), _housenumber(_housenumber)) { }

    // Copy constructor
    Person(const Person& person) _name(other._name), _dob(other._dob), _housenumber(other._housenumber)) { }
    
    // Move constructor
    Person(const Person&& person) _name(std::move(other._name)), _dob(std::move(other._dob)), _housenumber(std::move(other._housenumber))) { }
    
    // All primitive datatypes are hashable, therefore all datatypes are hashable
    int32_t hash() const {
        return furrow::hash(std::make_tuple(
            furrow::hash(_name),
            _dob.hash(),
            furrow::hash(_housenumber)
        ));
    }
    
    // Equality
    bool operator == (const Person& other) const {
        return _name == other._name && _dob == other._dob && _housenumber == other._housenumber;
    }
    
    // Existence
    operator bool () const {
        return bool(_name) || bool(_dob) || bool(_housenumber); // An optimizing compiler could order these from cheapest to most expensive
    }
    
    // All datatypes have an implicit order, though it may not make any sense :)
    // ^^ Not quite *all* datatypes, what about functions, etc? Do we just ignore them?
    // This lets them be stored in maps, sets, etc
    bool operator < (Person& other) const {
        return _name < other._name || _dob < other._dob || _housenumber < other._housenumber;
    }
    bool operator > (Person& other) const {
        return _name > other._name || _dob > other._dob || _housenumber > other._housenumber;
    }
    bool operator <= (Person& other) const {
        return !(*this > other);
    }
    bool operator >= (Person& other) const {
        return !(*this < other);
    }
}

// Need an overload of furrow::hash() to make it properly generic
// Begs the question, is there any reason to have a hash() method actually in the class?
int32_t furrow::hash(const Person& p) {
    return p.hash();
}


// How functions are implemented
// Could use std::function, but it's better if we have full access to the captured variables so we can do function equality, etc
struct Function14 {
    // Function pointer
    A (*_ptr)(B);
    
    // Captured variables. Some are by reference, some are copied.
    ...
    
    // Other stuff
    operator bool () const { return true; }
    bool operator == (const Function14& fun) const { return _ptr == fun._ptr; } // Question: is this a good idea?
}
int32_t furrow::hash(const Function14& fun) {
    // Hash both _ptr and the captured variables
    ...
}






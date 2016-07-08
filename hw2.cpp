/** Name: Kendrick Chu
 Date: 4/4/16
 @File: hw1.cpp
 @Brief: The program uses polymorphism to create ThingA and ThingB objects derived from a Thing base class, and these objects are stored using a Board class object.  Operator overloading is used to print out the objects within the Board class, to check if there is an object within the Board object at a certain position, and to compare the objects in the Board object to see if there are duplicates.
 */

#include <iostream>
#include <string>
#include <vector>

class Board; //forward declaration

/** @class Thing
 @Brief Stores the Thing class
 
 This is the Thing base class consisting of a position.
 */
class Thing{
public:
    //Constructor the makes a specified position into the object's position
    Thing(int pos);
    
    //Gives position of Thing object
    virtual int get_position() const;
    
    //Virtual print function used to print out all Thing objects and objects derived from this class
    virtual void print(std::ostream& out) const;
    
    //Virtual destructor
    virtual ~Thing();
    
    //Creates a clone on heap memory
    virtual Thing* clone();
    
protected:
    int position;
    static int ID_generator;
    int thing_ID;
};

/** @class ThingA
 @Brief Stores the ThingA class
 
 This is the ThingA class derived from the Thing base class, which consists of a position, string property, and board.
 
 */
class ThingA : public Thing {
public:
    //Constructor that initializes the position, property, and board to specified values
    ThingA(int pos, std::string prop, const Board& b);
    
    //Prints out the position and property of the object
    void print(std::ostream& out) const;
    
    //Creates a clone on heap memory
    virtual Thing* clone();
    
    //Virtual ThingA destructor
    virtual ~ThingA();
    
private:
    std::string property;
    const Board& board;
    int thingA_ID;
};

/** @class ThingB
 @Brief Stores the ThingB class
 
 This is the ThingB class derived from the Thing base class, which consists of a position, double property, and board.
 */
class ThingB : public Thing {
public:
    //Constructor that initializes the position, property, and board to specified values
    ThingB(int pos, double prop, const Board& b);
    
    //Makes the object have a new position
    bool propose_new_position(int a);
    
    //Prints out the position and property of the object
    void print(std::ostream& out) const;
    
    //Creates a clone on heap memory
    virtual Thing* clone();
    
    //Virtual ThingB destructor
    virtual ~ThingB();
    
private:
    double property;
    const Board& board;
    int thingB_ID;
};

/** @class Board
 @Brief Stores the Board class
 
 This is the Board class which stores Thing objects and all derived objects of the thing class into a vector.
 */
class Board{
public:
    
    Board();
    
    virtual ~Board();
    
    //Checks whether or not there is a  thing in the Thing* vector at a certain position
    bool ParticleInPosition(int pos) const;
    
    //Adds a ThingA element to the Thing* vector
    void AddAParticle(int pos, std::string prop);
    
    //Adds a ThingB element ot the Thing* vector
    bool AddBParticle(int pos, double prop);
    
    //Prints out the elements in the things vector
    void print(std::ostream& out) const;
    
    //Checks whether or not there is an element in the specified position using the ParticleInPosition function
    bool operator[](int pos);
    
    //Checks whether or not the particles of the board object are different
    bool operator()();
    
    //Deep copy constructor
    Board(const Board& b);
    
    //Operator= function for Board
    Board& operator=(Board b);
    
    //Swap function
    void swap(Board& b);
    
private:
    std::vector<Thing*> things;
};

//Uses the print function to print out the objects in the vector contained in the Board object using the << operator
std::ostream& operator <<(std::ostream& out, const Board& b);

//Initialize ID_generator to 0
int Thing::ID_generator = 0;




int main() {
    //Create a Board object
    Board test;
    //Output contents of Board object, should be nothing
    std::cout << test << std::endl;
    //Checks if there is particle at position 0 on the board, should return false or 0
    std::cout << test[0] << std::endl;
    
    //Add particles to board
    test.AddAParticle(0, "red");
    test.AddBParticle(3, 2.163);
    test.AddAParticle(2, "white");
    
    //Output contents of Board object
    std::cout << test;
    //Checks if there is a particle at position 0 on the board, should return true or 1
    std::cout << test[0] << std::endl;
    
    //Make another Board object equal to the previous board object, deep copy contents over
    Board testing = test;
    //Output contents of new Board object
    std::cout << testing;
    
    //If new board object has the same contents of previous board object in different area of heap memory, then should run.  If they refer to same memory, should crash.
    
    return 0;
    
}











//Thing functions definitions

/** Constructor the makes a specified position into the object's position
 @param int pos is the position of the Thing object
 */
Thing::Thing(int pos) : position(pos) {
    thing_ID = ++ID_generator;
    std::cout << "Thing " << thing_ID << " Thing constructor" << std::endl;
}

/** Returns the position of the object
 @returns the position of the object
 */
int Thing::get_position() const { return position; }

/** Virtual print function used to print out all Thing objects and objects derived from this class
 @param std::outstream& out is the outstream variable used to print
 */
void Thing::print(std::ostream &out) const { }

/** Virtual destructor for the base class Thing that will act on the base class and derived classes and delete appropriately, printing out the ID of the object it's destroying
 */
Thing::~Thing() {
    std::cout << "destructing Thing object " << thing_ID << std::endl;
}

/** Creates another copy of the Thing object on heap memory
 @returns the pointer to the Thing object on heap memory
 */
Thing* Thing::clone() {
    Thing* thing = new Thing(*this);
    return thing;
}



//ThingA functions definitions

/** Constructor that initializes the position, property, and board to specified values
 @param int pos is the position of the ThingA object
 @param std::string prop is the string property of the ThingA object
 @param const Board& b is the constant reference to the board object of ThingA
 */
ThingA::ThingA(int pos, std::string prop, const Board& b) : Thing(pos), property(prop), board(b) {
    thingA_ID = ++ID_generator;
    std::cout << "ThingA " << thingA_ID << " ThingA constructor" << std::endl;
    
}

/** Prints out the position and property of the object
 @param std::ostream& out is the outstream variable used to print
 */
void ThingA::print(std::ostream& out) const { out << "A:" << get_position() << ":" << property; }

/** Creats another copy of the ThingA object on heap memory with a Thing pointer pointing to it
 @returns the Thing pointer object
 */
Thing* ThingA::clone() {
    Thing* thing = new ThingA(*this);
    return thing;
}

/** Virtual destructor for the ThingA class, prints out a message to confirm object destruction
 */
ThingA::~ThingA() {
    std::cout << "destructing ThingA object " << thingA_ID << std::endl;
}






//ThingB functions definitions

/** Constructor that initializes the position, property, and board to specified values
 @param int pos is the position of the ThingB object
 @param double prop is the double property of the ThingB object
 @param const Board& b is the constant reference to the board object of ThingB
 */
ThingB::ThingB(int pos, double prop, const Board& b) : Thing(pos), property(prop), board(b) {
    thingB_ID = ++ID_generator;
    std::cout << "ThingB " << thingB_ID << " ThingB constructor" << std::endl;
}

/**Makes the object have a new position
 @param int a is the new position for the object
 */
bool propose_new_position(int a);

/** Prints out the position and property of the object
 @param std::ostream& out is the outstream variable used to print
 */
void ThingB::print(std::ostream& out) const { out << "B:" << get_position() << ":" << property; }

/** Creates a copy of the ThingB object on heap memory and points to it using a Thing*
 @returns the Thing pointer to the ThingB object on heap memory
 */
Thing* ThingB::clone() {
    Thing* thing = new ThingB(*this);
    return thing;
}

/** Virtual destructor for the ThingB class, prints out a message to confirm object destruction
 */
ThingB::~ThingB() {
    std::cout << "destructing ThingB object " << thingB_ID << std::endl;
}







//Board functions definitons

/** Default constructor for Board object
 */
Board::Board() : things() {
    
}

/** Destructor for Board class, uses a range based for loop to delete all elements in the things vector
 */
Board::~Board() {
    //For every element in the things vector, call delete
    for (auto& x : things) delete x;
}

/** Checks whether or not there is a  thing in the Thing* vector at a certain position
 @param int pos is the specified position
 @returns true if there is an element at the specified position or flase if there is not an element at the specified position
 */
bool Board::ParticleInPosition(int pos) const {
    //Checks each element in the vector if there is an element at at certain specified position
    for (size_t i = 0, n = things.size(); i < n; ++i)
        //If there is an element at the specified position, return true or 1
        if (things[i]->get_position() == pos)
            return true;
    //Else return false or 0
    return false;
}

/** Adds a ThingA element to the Thing* vector
 @param int pos is the position used for the new ThingA
 @param std::string prop is the string property used for the new ThingA
 */
void Board::AddAParticle(int pos, std::string prop) {
    Thing* thing = nullptr;
    //Try to allocate heap memory safely, print out error message if it can't and set pointer to nullptr
    try {
        thing = new ThingA(pos, prop, *this);
    }
    catch (std::exception& e) {
        std::cerr << "Failure to Board::AddAParticle(" << pos << ", " << prop << ", *this)" << std::endl;
        thing = nullptr;
    }
    
    //if thing != nullptr, then add thing pointer to things vector
    if (thing)
        things.push_back(thing);
}




/** Adds a ThingB element ot the Thing* vector
 @param int pos is the position used for the new ThingA
 @param double prop is the double property used for the new ThingB
 */
bool Board::AddBParticle(int pos, double prop) {
    
    //if no particle is at position pos, then add, otherwise don't add.
    if (!ParticleInPosition(pos)) {
        ThingB* thing = nullptr;
        //Try to allocate heap memory, if fail then print out error message and set pointer to nullptr
        try {
            thing = new ThingB(pos, prop, *this);
        }
        catch (std::exception& e) {
            std::cerr << "Failure to Board::AddBParticle(" << pos << ", " << prop << ". *this)" << std::endl;
            thing = nullptr;
        }
        
        //if thing != nullptr, then add thing pointer to things vector
        if (thing) {
            things.push_back(thing);
            return true;
        }
    }
    return false;
}


/** Prints out the elements in the things vector
 @param std::ostream& out is the outstream variable being used to output the elements in the things vector
 */
void Board::print(std::ostream& out) const {
    //Print out each element in the things vector, separated by an endl
    for (size_t i = 0, n = things.size(); i < n; ++i){
        things[i]->print(out);
        std::cout << std::endl;
    }
}

/** Checks whether or not there is an element in the specified position using the ParticleInPosition function
 @returns the result of the ParticleInPosition function
 */
bool Board::operator[](int pos){
    return ParticleInPosition(pos);
}

/** Checks whether or not the particles of the board object are different
 @returns true or 1 if there are the same particles on the board
 @returns false or 0 if all the particles on the board are different
 */
bool Board::operator()() {
    //For every element in the things variable, check each element with all elements after it
    for (size_t i = 0, n = things.size(); i < n; ++i)
        //Used to compare the element in the first for loop
        for (size_t k = 1, n = things.size(); k < n; ++k) {
            //If there are multiple of the same particles on the board, return true
            if (things[i] == things[k])
                return true;
        }
    //Else return false
    return false;
}

/** Copy constructor, copies the contents of the vector variable in the parameter Board object onto another vector in another Board object
 @param const Board& b is the Board object from which the vector values are being copied
 */
Board::Board(const Board& b) {
    for (size_t i = 0, n = b.things.size(); i < n; ++i) {
        things.push_back(b.things[i]->clone());
    }
}
/** Uses the operator= to assign the values of the right argument to the left argument
 @param Board b is a copy of the object whose values are being swapped
 @returns the object with new values from b, the parameter
 */
Board& Board::operator=(Board b) {
    b.swap(*this);
    return *this;
}

/** Swaps the private member variables of b and the object this function is acting on
 @Board& b is the reference to the Board object whose values are being swapped, which is destroyed at the end of the function
 */
void Board::swap(Board& b) {
    std::swap(things, b.things);
}

/** Uses the print function to print out the objects in the vector contained in the Board object using the << operator
 @param std::ostream& out is the outstream variable to that is used in the print function
 @param const Board& b is a constant reference to the Board variable, which is the object that the operator << is acting on
 @returns the outstream variable
 */
std::ostream& operator <<(std::ostream& out, const Board& b) {
    b.print(out);
    return out;
}




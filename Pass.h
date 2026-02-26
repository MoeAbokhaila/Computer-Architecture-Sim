//
//  Pass.h




#include <iostream>
#include <map>
#include <vector>
#include <memory>
#include <string>



class Positions
{
public:
    virtual ~Positions() = default;  // Virtual destructor for base class
    virtual int getValueInt() const { return 0; } // Default implementation
    virtual double getValueDouble() const { return 0.0; } // Default implementation
    virtual float getValueFloat() const { return 0.0; }
    virtual std::string getValueString() const { return ""; } // Default implementation
    virtual char getValueChar() const { return ' '; }

};


class Memory {
 private:
     std::map<int, std::shared_ptr<Positions>> positions;
     int counter;
 public:
     Memory():counter(0){}
     void storePosition(std::shared_ptr<Positions> position) {
         positions[counter++] = position;
     }
     
     std::shared_ptr<Positions> loadPosition(int key)
    {
         auto it = positions.find(key);//auto key is used to detect datatype from its initialization
         if (it != positions.end())
         {
             return it->second;
         }
         return std::shared_ptr<Positions>(); // Return empty
     }
    
     int getCounter() const { return counter; }
     
    /*void printStoredPositionsCount() const {
            std::cout << "Total objects in memory: " << positions.size() << '\n';
        }*/
};

Memory memory;

class Pass
{
public:
    template<typename T>
    Pass& operator||(const T& output)
                    {
                    std::cout<<output;
                    return *this;//*this returns "this object"
                    }
                    };

class Kick
{
    public:
    template <typename T>
    Kick& operator/(T& input)
    {
        std::cin>>input;
        return *this;
    }
    
    Kick& operator/(std::string& input)
    {
        std::cin>>input;
        return *this;
    }
    
    
};




class Striker: public Positions
{
    friend Pass& operator||(Pass& o, const Striker& s);//friends for the operators to access priv data
    friend Kick& operator/(Kick& i, Striker& s);
    private:
        int x;
    public:
        Striker()
        {
            this->x=0;
            memory.storePosition(std::make_shared<Striker>(*this));
        }
        
        int getStriker(){return x;}
        
        void operator=(int x)
        {
            this->x=x;
        }
    
        
        void operator+(int x)
        {
            this->x+=x;
        }
        void operator+=(int x)
        {
            this->x+=x;
        }
        
        void operator-(int x)
        {
            this->x-=x;
        }
    
        void operator+(double x)
        {
            this->x+=x;
        }
        
    int getValueInt() const override {
            return x; // Return x as int
        }
        
        
        
};

class Defender:public Positions
{
    friend Kick& operator/(Kick& i, Defender& s);
    friend Pass& operator||(Pass& o, const Defender& cm);
private:
    char x;
public:

    Defender()
    {
        this->x=' ';
        memory.storePosition(std::make_shared<Defender>(*this));
    }
    
    void operator=(char x)
    {
        this->x=x;
    }
    
    char getValueChar() const override {
            return x; // Return x as char
        }
    
};

class LeftWing: public Positions
{
    friend Pass& operator||(Pass& o, const LeftWing& lw);
   // friend Pass& operator||(Pass& o, LeftWing& s);
    friend Kick& operator/(Kick& i, LeftWing& s);
    private:
        double x;
    public:
    LeftWing()
        {
            this->x=0;
            memory.storePosition(std::make_shared<LeftWing>(*this));
        }
        
        int getLeftWing(){return x;}
        
        void operator=(double x)
        {
            this->x=x;
        }
        
        void operator+(double x)
        {
            this->x+=x;
        }
        
        void operator-(double x)
        {
            this->x-=x;
        }
        
        void operator+(int x)
        {
            this->x+=x;
        }
    
        void operator-(int x)
        {
            this->x-=x;
        }
        
    double getValueDouble() const override {
            return x; // Return x as double
        }
};

class CentreMid: public Positions
{
    friend Pass& operator||(Pass& o, CentreMid& s);
    friend Kick& operator/(Kick& i, CentreMid& s);
    private:
        float x;
    public:
    CentreMid()
        {
            this->x=0;
        memory.storePosition( std::make_shared<CentreMid>(*this));
        }
        
        int getCentreMid(){return x;}
        
        void operator=(float x)
        {
            this->x=x;
        }
    
        void operator=(double x)
        {
            this->x=x;
        }
        
        void operator+(float x)
        {
            this->x+=x;
        }
    
        void operator+(double x)
        {
            this->x+=x;
        }
            
        
        void operator-(float x)
        {
            this->x-=x;
        }
    
        void operator-(int x)
        {
            this->x-=x;
        }
        
        void operator+(int x)
        {
            this->x-=x;
        }
        void operator=(int x)
        {
            this->x-=x;
        }
        
    float getValueFloat() const override {
            return x;
        }
        
        
        
};

class RightWing: public Positions
{
    friend Pass& operator||(Pass& o, RightWing& s);
    friend Kick& operator/(Kick& i, RightWing& s);
    private:
        std::string x;
    public:
    RightWing()
        {
            this->x=" ";
        memory.storePosition(std::make_shared<RightWing>(*this));
        }
        
    std::string getRightWing(){return x;}
        
        void operator=(std::string x)
        {
            this->x=x;
        }
        
        void operator+=(std::string x)
        {
            this->x+=x;
        }
        
    bool operator==(std::string x)
    {
        return this->x==x;
    }
        
        
    std::string getValueString() const override {
            return x; // Return the stored string
        }
        
        
        
};

Kick& operator/(Kick& i, Striker& s)
{
    int input;
    i/input;
    s.x=input;
    return i;
}

Kick& operator/(Kick& i, LeftWing& s)
{
    double input;
    i/input;
    s.x=input;
    return i;
}

Kick& operator/(Kick& i, CentreMid& s)
{
    float input;
    i/input;
    s.x=input;
    return i;
}

Kick& operator/(Kick& i, RightWing& s)
{
    std::string input;
    i/input;
    s.x=input;
    return i;
}

Kick& operator/(Kick& i, Defender& s)
{
    char input;
    i/input;
    s.x=input;
    return i;
}




Pass& operator||(Pass& o, const Striker& s)
{
    o||s.x;
    
    return o;
}



/*Pass& operator||(Pass& o, LeftWing& s)
{
    o||s.x;
    
    return o;
}*/

Pass& operator||(Pass& o, RightWing& s)
{
    o||s.x;
    
    return o;
}

Pass& operator||(Pass& o, CentreMid& s)
{
    o||s.x;
    
    return o;
}



class CPU {
    
private:
    std::vector<std::shared_ptr<Positions>>registers;
    std::shared_ptr<Positions>accumulator;
    Memory& memory;

public:
    CPU(Memory& memory) : memory(memory) {
        registers.resize(2);
    }

    // Load a position into a register
    void load(int reg, int key) {
        registers[reg] = memory.loadPosition(key);
    }


    void add() {

        if (auto striker1 = dynamic_cast<Striker*>(registers[0].get()))
        {
                    if (auto striker2 = dynamic_cast<Striker*>(registers[1].get())) {
                        
                        auto newStriker = std::make_shared<Striker>();//creates a new object
                        *newStriker = striker1->getValueInt() + striker2->getValueInt();//uses the accessors to add these into the new object
                        accumulator = newStriker;//assigns that to the accumulator
                    }
                    
                    else if (auto leftWing = dynamic_cast<LeftWing*>(registers[1].get())) {
                        auto newLeftWing = std::make_shared<LeftWing>();
                        *newLeftWing = striker1->getValueInt() + leftWing->getValueDouble();
                        accumulator = newLeftWing;
                    }
            
                    else if (auto centremid = dynamic_cast<CentreMid*>(registers[1].get())) {
                        auto newCentreMid = std::make_shared<CentreMid>();
                        *newCentreMid = striker1->getValueInt() + centremid->getValueFloat();
                        accumulator = newCentreMid;
                    }
                }
        
        if (auto centremid1 = dynamic_cast<CentreMid*>(registers[0].get()))
        {
                    if (auto centremid2 = dynamic_cast<CentreMid*>(registers[1].get()))
                    {
                        
                        auto newCentreMid = std::make_shared<CentreMid>();
                        *newCentreMid = centremid1->getValueFloat() + centremid2->getValueFloat();
                        accumulator = newCentreMid;
                    }
                    
                    else if (auto leftWing = dynamic_cast<LeftWing*>(registers[1].get()))
                    {
                        auto newCentreMid = std::make_shared<CentreMid>();
                        *newCentreMid = centremid1->getValueFloat() + leftWing->getValueDouble();
                        accumulator = newCentreMid;
                    }
            
                    else if (auto striker = dynamic_cast<Striker*>(registers[1].get()))
                    {
                        auto newCentreMid= std::make_shared<CentreMid>();
                        *newCentreMid = centremid1->getValueFloat() + striker->getValueInt();
                        accumulator = newCentreMid;
                    }
                }
        
        if (auto leftwing1 = dynamic_cast<LeftWing*>(registers[0].get()))
        {
                    if (auto leftwing2 = dynamic_cast<LeftWing*>(registers[1].get()))
                    {
                        
                        auto newLeftWing = std::make_shared<LeftWing>();
                        *newLeftWing = leftwing1->getValueDouble() + leftwing2->getValueDouble();
                        accumulator = newLeftWing;
                    }
            
                    else if (auto centremid = dynamic_cast<CentreMid*>(registers[1].get()))
                    {
                        auto newLeftWing = std::make_shared<LeftWing>();
                        *newLeftWing = centremid->getValueFloat() + leftwing1->getValueDouble();
                        accumulator = newLeftWing;
                    }
            
                    else if (auto striker = dynamic_cast<Striker*>(registers[1].get()))
                    {
                        auto newLeftWing= std::make_shared<LeftWing>();
                        *newLeftWing = leftwing1->getValueDouble() + striker->getValueInt();
                        accumulator = newLeftWing;
                    }
                }
        }
    
    void subtract()
    {
        if (auto striker1 = dynamic_cast<Striker*>(registers[0].get())) {
                    if (auto striker2 = dynamic_cast<Striker*>(registers[1].get()))
                    {
                        
                        auto newStriker = std::make_shared<Striker>();
                        *newStriker = striker1->getValueInt() - striker2->getValueInt();
                        accumulator = newStriker;
                    }
                    
                    else if (auto leftWing = dynamic_cast<LeftWing*>(registers[1].get()))
                    {
                        auto newLeftWing = std::make_shared<LeftWing>();
                        *newLeftWing = striker1->getValueInt() - leftWing->getValueDouble();
                        accumulator = newLeftWing;
                    }
            
                    else if (auto centremid = dynamic_cast<CentreMid*>(registers[1].get()))
                    {
                        auto newCentreMid = std::make_shared<CentreMid>();
                        *newCentreMid = striker1->getValueInt() - centremid->getValueFloat();
                        accumulator = newCentreMid;
                    }
                }
        
        if (auto leftwing1 = dynamic_cast<LeftWing*>(registers[0].get())) {
                    if (auto leftwing2 = dynamic_cast<LeftWing*>(registers[1].get()))
                    {
                        
                        auto newLeftWing = std::make_shared<LeftWing>();
                        *newLeftWing = leftwing1->getValueDouble() - leftwing2->getValueDouble();
                        accumulator = newLeftWing;
                    }
            
                    else if (auto centremid = dynamic_cast<CentreMid*>(registers[1].get()))
                    {
                        auto newLeftWing = std::make_shared<LeftWing>();
                        *newLeftWing =  leftwing1->getValueDouble()-centremid->getValueFloat();
                        accumulator = newLeftWing;
                    }
            
                    else if (auto striker = dynamic_cast<Striker*>(registers[1].get()))
                    {
                        auto newLeftWing= std::make_shared<LeftWing>();
                        *newLeftWing = leftwing1->getValueDouble() - striker->getValueInt();
                        accumulator = newLeftWing;
                    }
                }
        if (auto centremid1 = dynamic_cast<CentreMid*>(registers[0].get())) {
                    if (auto centremid2 = dynamic_cast<CentreMid*>(registers[1].get()))
                    {
                        
                        auto newCentreMid = std::make_shared<CentreMid>();
                        *newCentreMid = centremid1->getValueFloat() - centremid2->getValueFloat();
                        accumulator = newCentreMid;
                    }
                    
                    else if (auto leftWing = dynamic_cast<LeftWing*>(registers[1].get()))
                    {
                        auto newCentreMid = std::make_shared<CentreMid>();
                        *newCentreMid = centremid1->getValueFloat() - leftWing->getValueDouble();
                        accumulator = newCentreMid;
                    }
            
                    else if (auto striker = dynamic_cast<Striker*>(registers[1].get()))
                    {
                        auto newCentreMid= std::make_shared<CentreMid>();
                        *newCentreMid = centremid1->getValueFloat() - striker->getValueInt();
                        accumulator = newCentreMid;
                    }
                }
        
    }
    
    void multiply()
    {
        if (auto striker1 = dynamic_cast<Striker*>(registers[0].get())) {
                    if (auto striker2 = dynamic_cast<Striker*>(registers[1].get()))
                    {
                        
                        auto newStriker = std::make_shared<Striker>();
                        *newStriker = striker1->getValueInt() * striker2->getValueInt();
                        accumulator = newStriker;
                    }
                    
                    else if (auto leftWing = dynamic_cast<LeftWing*>(registers[1].get()))
                    {
                        auto newLeftWing = std::make_shared<LeftWing>();
                        *newLeftWing = striker1->getValueInt() * leftWing->getValueDouble();
                        accumulator = newLeftWing;
                    }
            
                    else if (auto centremid = dynamic_cast<CentreMid*>(registers[1].get()))
                    {
                        auto newCentreMid = std::make_shared<CentreMid>();
                        *newCentreMid = striker1->getValueInt() * centremid->getValueFloat();
                        accumulator = newCentreMid;
                    }
                }
        
        if (auto leftwing1 = dynamic_cast<LeftWing*>(registers[0].get())) {
                    if (auto leftwing2 = dynamic_cast<LeftWing*>(registers[1].get()))
                    {
                        
                        auto newLeftWing = std::make_shared<LeftWing>();
                        *newLeftWing = leftwing1->getValueDouble() * leftwing2->getValueDouble();
                        accumulator = newLeftWing;
                    }
            
                    else if (auto centremid = dynamic_cast<CentreMid*>(registers[1].get()))
                    {
                        auto newLeftWing = std::make_shared<LeftWing>();
                        *newLeftWing = centremid->getValueFloat() * leftwing1->getValueDouble();
                        accumulator = newLeftWing;
                    }
            
                    else if (auto striker = dynamic_cast<Striker*>(registers[1].get()))
                    {
                        auto newLeftWing= std::make_shared<LeftWing>();
                        *newLeftWing = leftwing1->getValueDouble() * striker->getValueInt();
                        accumulator = newLeftWing;
                    }
                }
        if (auto centremid1 = dynamic_cast<CentreMid*>(registers[0].get())) {
                    if (auto centremid2 = dynamic_cast<CentreMid*>(registers[1].get()))
                    {
                        
                        auto newCentreMid = std::make_shared<CentreMid>();
                        *newCentreMid = centremid1->getValueFloat() * centremid2->getValueFloat();
                        accumulator = newCentreMid;
                    }
                    
                    else if (auto leftWing = dynamic_cast<LeftWing*>(registers[1].get()))
                    {
                        auto newCentreMid = std::make_shared<CentreMid>();
                        *newCentreMid = centremid1->getValueFloat() * leftWing->getValueDouble();
                        accumulator = newCentreMid;
                    }
            
                    else if (auto striker = dynamic_cast<Striker*>(registers[1].get()))
                    {
                        auto newCentreMid= std::make_shared<CentreMid>();
                        *newCentreMid = centremid1->getValueFloat() * striker->getValueInt();
                        accumulator = newCentreMid;
                    }
                }
        
    }
    
    void divide()
    {
        if (auto striker1 = dynamic_cast<Striker*>(registers[0].get())) {
                    if (auto striker2 = dynamic_cast<Striker*>(registers[1].get()))
                    {
                        
                        auto newStriker = std::make_shared<Striker>();
                        *newStriker = striker1->getValueInt() / striker2->getValueInt();
                        accumulator = newStriker;
                    }
                    
                    else if (auto leftWing = dynamic_cast<LeftWing*>(registers[1].get()))
                    {
                        auto newLeftWing = std::make_shared<LeftWing>();
                        *newLeftWing = striker1->getValueInt() / leftWing->getValueDouble();
                        accumulator = newLeftWing;
                    }
            
                    else if (auto centremid = dynamic_cast<CentreMid*>(registers[1].get()))
                    {
                        auto newCentreMid = std::make_shared<CentreMid>();
                        *newCentreMid = striker1->getValueInt() / centremid->getValueFloat();
                        accumulator = newCentreMid;
                    }
                }
        
        if (auto leftwing1 = dynamic_cast<LeftWing*>(registers[0].get())) {
                    if (auto leftwing2 = dynamic_cast<LeftWing*>(registers[1].get()))
                    {
                        
                        auto newLeftWing = std::make_shared<LeftWing>();
                        *newLeftWing = leftwing1->getValueDouble() / leftwing2->getValueDouble();
                        accumulator = newLeftWing;
                    }
            
                    else if (auto centremid = dynamic_cast<CentreMid*>(registers[1].get()))
                    {
                        auto newLeftWing = std::make_shared<LeftWing>();
                        *newLeftWing = centremid->getValueFloat() / leftwing1->getValueDouble();
                        accumulator = newLeftWing;
                    }
            
                    else if (auto striker = dynamic_cast<Striker*>(registers[1].get()))
                    {
                        auto newLeftWing= std::make_shared<LeftWing>();
                        *newLeftWing = leftwing1->getValueDouble() / striker->getValueInt();
                        accumulator = newLeftWing;
                    }
                }
        if (auto centremid1 = dynamic_cast<CentreMid*>(registers[0].get())) {
                    if (auto centremid2 = dynamic_cast<CentreMid*>(registers[1].get()))
                    {
                        
                        auto newCentreMid = std::make_shared<CentreMid>();
                        *newCentreMid = centremid1->getValueFloat() / centremid2->getValueFloat();
                        accumulator = newCentreMid;
                    }
                    
                    else if (auto leftWing = dynamic_cast<LeftWing*>(registers[1].get()))
                    {
                        auto newCentreMid = std::make_shared<CentreMid>();
                        *newCentreMid = centremid1->getValueFloat() / leftWing->getValueDouble();
                        accumulator = newCentreMid;
                    }
            
                    else if (auto striker = dynamic_cast<Striker*>(registers[1].get()))
                    {
                        auto newCentreMid= std::make_shared<CentreMid>();
                        *newCentreMid = centremid1->getValueFloat() / striker->getValueInt();
                        accumulator = newCentreMid;
                    }
                }
        
    }
    
    bool compare() {
        if (registers[0] && registers[1])
        {
            if (auto striker1 = dynamic_cast<Striker*>(registers[0].get())) {
                if (auto striker2 = dynamic_cast<Striker*>(registers[1].get())) {
                    return striker1->getValueInt()==striker2->getValueInt();
                }
            }
            
            
            
            if (auto leftwing1 = dynamic_cast<LeftWing*>(registers[0].get())) {
                if (auto leftwing2 = dynamic_cast<LeftWing*>(registers[1].get())) {
                    return leftwing1->getValueDouble()==leftwing2->getValueDouble();
                }
            }
            
            if (auto centremid1 = dynamic_cast<CentreMid*>(registers[0].get())) {
                if (auto centremid2 = dynamic_cast<CentreMid*>(registers[1].get())) {
                    return centremid1->getValueFloat()==centremid2->getValueFloat();
                }
            }
            
            if (auto rightwing1 = dynamic_cast<RightWing*>(registers[0].get())) {
                if (auto rightwing2 = dynamic_cast<RightWing*>(registers[1].get())) {
                    return rightwing1->getValueString()==rightwing2->getValueString();
                }
            }
            
            if (auto defender1 = dynamic_cast<Defender*>(registers[0].get())) {
                if (auto defender2 = dynamic_cast<Defender*>(registers[1].get())) {
                    return defender1->getValueChar()==defender2->getValueChar();
                }
            }
            
        }
        
        return false;
    }
        
    
    
       

    void storeAccumulator(int key) {
        if (accumulator) {
            memory.storePosition(accumulator);
        }
    }

    std::shared_ptr<Positions> getAccumulator() const {
        
        return accumulator; // Return the accumulator
    }
    
    /*void printRegisters() const {
            std::cout << "Registers Loaded in CPU:\n";
            for (size_t i = 0; i < registers.size(); ++i) {
                std::cout << "Register " << i << ": ";
                if (registers[i]) {
                    if (auto striker = dynamic_cast<Striker*>(registers[i].get())) {
                        std::cout << "Type: Striker, Value: " << striker->getValueInt();
                    } else if (auto leftWing = dynamic_cast<LeftWing*>(registers[i].get())) {
                        std::cout << "Type: LeftWing, Value: " << leftWing->getValueDouble();
                    } else if (auto centreMid = dynamic_cast<CentreMid*>(registers[i].get())) {
                        std::cout << "Type: CentreMid, Value: " << centreMid->getValueDouble();
                    } else if (auto rightWing = dynamic_cast<RightWing*>(registers[i].get())) {
                        std::cout << "Type: RightWing, Value: " << rightWing->getValueString();
                    } else {
                        std::cout << "Unknown Position Type";
                    }
                } else {
                    std::cout << "Empty"; // No position loaded
                }
                std::cout << '\n'; // Move to next line
            }
        }
    
    void printAccumulator() const {
            std::cout << "Accumulator Contents: ";
            if (accumulator) {
                if (auto striker = dynamic_cast<Striker*>(accumulator.get())) {
                    std::cout << "Type: Striker, Value: " << striker->getValueInt();
                } else if (auto leftWing = dynamic_cast<LeftWing*>(accumulator.get())) {
                    std::cout << "Type: LeftWing, Value: " << leftWing->getValueDouble();
                } else if (auto centreMid = dynamic_cast<CentreMid*>(accumulator.get())) {
                    std::cout << "Type: CentreMid, Value: " << centreMid->getValueFloat();
                } else if (auto rightWing = dynamic_cast<RightWing*>(accumulator.get())) {
                    std::cout << "Type: RightWing, Value: " << rightWing->getValueString();
                } else {
                    std::cout << "Unknown Position Type";
                }
            } else {
                std::cout << "Empty"; // Accumulator is empty
            }
            std::cout << '\n'; // Move to next line
        }*/
    
};


CPU cpu(memory);

LeftWing operator+(Striker& s, LeftWing& x) {
  
    memory.storePosition( std::make_shared<Striker>(s));
    memory.storePosition( std::make_shared<LeftWing>(x));
    cpu.load(0, memory.getCounter()-1);
    cpu.load(1, memory.getCounter());
    cpu.add();
    cpu.storeAccumulator(memory.getCounter()+1);
    
    //cpu.printAccumulator();
    
    auto result = std::dynamic_pointer_cast<LeftWing>(cpu.getAccumulator());
    if (result) {
        return *result;
    }
    return LeftWing();
}

Striker operator+(Striker& s, Striker& x) {
   
    memory.storePosition( std::make_shared<Striker>(s));
    memory.storePosition(std::make_shared<Striker>(x));
    cpu.load(0, memory.getCounter() - 1);
    cpu.load(1, memory.getCounter() - 2);
    cpu.add();
    cpu.storeAccumulator(memory.getCounter()+1);
    
   // cpu.printAccumulator();
    
    auto result = std::dynamic_pointer_cast<Striker>(cpu.getAccumulator());
    if (result) {
        return *result;
    }
    return Striker();
}

CentreMid operator+(Striker& s, CentreMid& x) {
    memory.storePosition( std::make_shared<Striker>(s));
    memory.storePosition( std::make_shared<CentreMid>(x));
    cpu.load(0, memory.getCounter()-1);
    cpu.load(1, memory.getCounter() -2);
    cpu.add();
    cpu.storeAccumulator(memory.getCounter()+1);
    
    
    auto result = std::dynamic_pointer_cast<CentreMid>(cpu.getAccumulator());
    if (result) {
        return *result;
    }
    return CentreMid();
}

CentreMid operator+(CentreMid& cm, Striker& st) {
    
    memory.storePosition( std::make_shared<CentreMid>(cm));
    memory.storePosition( std::make_shared<Striker>(st));
    cpu.load(0, memory.getCounter() -2);
    cpu.load(1, memory.getCounter() -1);
    cpu.add();
    cpu.storeAccumulator(memory.getCounter()+1);
    
    //cpu.printAccumulator();
    
    auto result = std::dynamic_pointer_cast<CentreMid>(cpu.getAccumulator());
    if (result) {
        return *result;
    }
    return CentreMid();
}

CentreMid operator+(CentreMid& cm, LeftWing& lw) {
  
    memory.storePosition( std::make_shared<CentreMid>(cm));
    memory.storePosition(std::make_shared<LeftWing>(lw));
    cpu.load(0, memory.getCounter() -2);
    cpu.load(1, memory.getCounter() -1);
    cpu.add();
    cpu.storeAccumulator(memory.getCounter()+1);
    
    //cpu.printAccumulator();
    
    auto result = std::dynamic_pointer_cast<CentreMid>(cpu.getAccumulator());
    if (result) {
        return *result;
    }
    return CentreMid();
}

CentreMid operator+(CentreMid& cm, CentreMid& lw) {
  
    memory.storePosition( std::make_shared<CentreMid>(cm));
    memory.storePosition(std::make_shared<CentreMid>(lw));
    cpu.load(0, memory.getCounter() -2);
    cpu.load(1, memory.getCounter() -1);
    cpu.add();
    cpu.storeAccumulator(memory.getCounter()+1);
    
    //cpu.printAccumulator();
    
    auto result = std::dynamic_pointer_cast<CentreMid>(cpu.getAccumulator());
    if (result) {
        return *result;
    }
    return CentreMid();
}

LeftWing operator+(LeftWing& cm, LeftWing& lw) {
   
    memory.storePosition( std::make_shared<LeftWing>(cm));
    memory.storePosition( std::make_shared<LeftWing>(lw));
    cpu.load(0, memory.getCounter() -2);
    cpu.load(1, memory.getCounter() -1);
    cpu.add();
    cpu.storeAccumulator(memory.getCounter()+1);
    
    //cpu.printAccumulator();
    
    auto result = std::dynamic_pointer_cast<LeftWing>(cpu.getAccumulator());
    if (result) {
        return *result;
    }
    return LeftWing();
}

LeftWing operator+(LeftWing& lw, CentreMid& cm) {
    
    memory.storePosition(std::make_shared<LeftWing>(lw));
    memory.storePosition(std::make_shared<CentreMid>(cm));
    cpu.load(0, memory.getCounter() -2);
    cpu.load(1, memory.getCounter() -1);
    cpu.add();
    cpu.storeAccumulator(memory.getCounter()+1);
    
    //cpu.printAccumulator();
    
    auto result = std::dynamic_pointer_cast<LeftWing>(cpu.getAccumulator());
    if (result) {
        return *result;
    }
    return LeftWing();
}

LeftWing operator+(LeftWing& lw, Striker& st) {
   
    memory.storePosition( std::make_shared<LeftWing>(lw));
    memory.storePosition( std::make_shared<Striker>(st));
    cpu.load(0, memory.getCounter() -2);
    cpu.load(1, memory.getCounter() -1);
    cpu.add();
    cpu.storeAccumulator(memory.getCounter()+1);
    
    //cpu.printAccumulator();
    
    auto result = std::dynamic_pointer_cast<LeftWing>(cpu.getAccumulator());
    if (result) {
        return *result;
    }
    return LeftWing();
}


//subtract striker or int
LeftWing operator-(Striker& s, LeftWing& x) {

    memory.storePosition( std::make_shared<Striker>(s));
    memory.storePosition( std::make_shared<LeftWing>(x));
    cpu.load(0, memory.getCounter()-1);
    cpu.load(1, memory.getCounter());
    cpu.subtract();
    cpu.storeAccumulator(memory.getCounter()+1);
    
    //cpu.printAccumulator();
    
    auto result = std::dynamic_pointer_cast<LeftWing>(cpu.getAccumulator());
    if (result) {
        return *result;
    }
    return LeftWing();
}

Striker operator-(Striker& s, Striker& x) {
    
    memory.storePosition( std::make_shared<Striker>(s));
    memory.storePosition( std::make_shared<Striker>(x));
    cpu.load(0, memory.getCounter() - 1);
    cpu.load(1, memory.getCounter() - 2);
    cpu.subtract();
    cpu.storeAccumulator(memory.getCounter()+1);
    
    //cpu.printAccumulator();
    
    auto result = std::dynamic_pointer_cast<Striker>(cpu.getAccumulator());
    if (result) {
        return *result;
    }
    return Striker();
}

CentreMid operator-(Striker& s, CentreMid& x) {
    
    memory.storePosition( std::make_shared<Striker>(s));
    memory.storePosition( std::make_shared<CentreMid>(x));
    cpu.load(0, memory.getCounter() -2);
    cpu.load(1, memory.getCounter() -1);
    cpu.subtract();
    cpu.storeAccumulator(memory.getCounter()+1);
    
    
    auto result = std::dynamic_pointer_cast<CentreMid>(cpu.getAccumulator());
    if (result) {
        return *result;
    }
    return CentreMid();
}

//subtract leftwing

LeftWing operator-(LeftWing& cm, LeftWing& lw) {
   
    memory.storePosition( std::make_shared<LeftWing>(cm));
    memory.storePosition( std::make_shared<LeftWing>(lw));
    cpu.load(0, memory.getCounter() -2);
    cpu.load(1, memory.getCounter() -1);
    cpu.subtract();
    cpu.storeAccumulator(memory.getCounter()+1);
    
    //cpu.printAccumulator();
    
    auto result = std::dynamic_pointer_cast<LeftWing>(cpu.getAccumulator());
    if (result) {
        return *result;
    }
    return LeftWing();
}

LeftWing operator-(LeftWing& lw, CentreMid& cm) {
    
    memory.storePosition(std::make_shared<LeftWing>(lw));
    memory.storePosition(std::make_shared<CentreMid>(cm));
    cpu.load(0, memory.getCounter() -2);
    cpu.load(1, memory.getCounter() -1);
    cpu.subtract();
    cpu.storeAccumulator(memory.getCounter()+1);
    
    //cpu.printAccumulator();
    
    auto result = std::dynamic_pointer_cast<LeftWing>(cpu.getAccumulator());
    if (result) {
        return *result;
    }
    return LeftWing();
}

LeftWing operator-(LeftWing& lw, Striker& st) {
   
    memory.storePosition( std::make_shared<LeftWing>(lw));
    memory.storePosition( std::make_shared<Striker>(st));
    cpu.load(0, memory.getCounter() -2);
    cpu.load(1, memory.getCounter() -1);
    cpu.subtract();
    cpu.storeAccumulator(memory.getCounter()+1);
    
    //cpu.printAccumulator();
    
    auto result = std::dynamic_pointer_cast<LeftWing>(cpu.getAccumulator());
    if (result) {
        return *result;
    }
    return LeftWing();
}

//subtract centremid
CentreMid operator-(CentreMid& cm, Striker& st) {
    
    memory.storePosition( std::make_shared<CentreMid>(cm));
    memory.storePosition( std::make_shared<Striker>(st));
    cpu.load(0, memory.getCounter() -2);
    cpu.load(1, memory.getCounter() -1);
    cpu.subtract();
    cpu.storeAccumulator(memory.getCounter()+1);
    
    //cpu.printAccumulator();
    
    auto result = std::dynamic_pointer_cast<CentreMid>(cpu.getAccumulator());
    if (result) {
        return *result;
    }
    return CentreMid();
}

CentreMid operator-(CentreMid& cm, LeftWing& lw) {
  
    memory.storePosition( std::make_shared<CentreMid>(cm));
    memory.storePosition(std::make_shared<LeftWing>(lw));
    cpu.load(0, memory.getCounter() -2);
    cpu.load(1, memory.getCounter() -1);
    cpu.subtract();
    cpu.storeAccumulator(memory.getCounter()+1);
    
   // cpu.printAccumulator();
    
    auto result = std::dynamic_pointer_cast<CentreMid>(cpu.getAccumulator());
    if (result) {
        return *result;
    }
    return CentreMid();
}

CentreMid operator-(CentreMid& cm, CentreMid& lw) {
  
    memory.storePosition( std::make_shared<CentreMid>(cm));
    memory.storePosition(std::make_shared<CentreMid>(lw));
    cpu.load(0, memory.getCounter() -2);
    cpu.load(1, memory.getCounter() -1);
    cpu.subtract();
    cpu.storeAccumulator(memory.getCounter()+1);
    
    //cpu.printAccumulator();
    
    auto result = std::dynamic_pointer_cast<CentreMid>(cpu.getAccumulator());
    if (result) {
        return *result;
    }
    return CentreMid();
}

//multiply striker
LeftWing operator*(Striker& s, LeftWing& x) {
  
    memory.storePosition( std::make_shared<Striker>(s));
    memory.storePosition( std::make_shared<LeftWing>(x));
    cpu.load(0, memory.getCounter()-1);
    cpu.load(1, memory.getCounter());
    cpu.multiply();
    cpu.storeAccumulator(memory.getCounter()+1);
    
    //cpu.printAccumulator();
    
    auto result = std::dynamic_pointer_cast<LeftWing>(cpu.getAccumulator());
    if (result) {
        return *result;
    }
    return LeftWing();
}

Striker operator*(Striker& s, Striker& x) {
   
    memory.storePosition( std::make_shared<Striker>(s));
    memory.storePosition(std::make_shared<Striker>(x));
    cpu.load(0, memory.getCounter() - 1);
    cpu.load(1, memory.getCounter() - 2);
    cpu.multiply();
    cpu.storeAccumulator(memory.getCounter()+1);
    
    //cpu.printAccumulator();
    
    auto result = std::dynamic_pointer_cast<Striker>(cpu.getAccumulator());
    if (result) {
        return *result;
    }
    return Striker();
}

CentreMid operator*(Striker& s, CentreMid& x) {
    memory.storePosition( std::make_shared<Striker>(s));
    memory.storePosition( std::make_shared<CentreMid>(x));
    cpu.load(0, memory.getCounter());
    cpu.load(1, memory.getCounter() -1);
    cpu.multiply();
    cpu.storeAccumulator(memory.getCounter()+1);
    
    
    auto result = std::dynamic_pointer_cast<CentreMid>(cpu.getAccumulator());
    if (result) {
        return *result;
    }
    return CentreMid();
}

//multiply leftwing

LeftWing operator*(LeftWing& cm, LeftWing& lw) {
   
    memory.storePosition( std::make_shared<LeftWing>(cm));
    memory.storePosition( std::make_shared<LeftWing>(lw));
    cpu.load(0, memory.getCounter() -2);
    cpu.load(1, memory.getCounter() -1);
    cpu.multiply();
    cpu.storeAccumulator(memory.getCounter()+1);
    
    //cpu.printAccumulator();
    
    auto result = std::dynamic_pointer_cast<LeftWing>(cpu.getAccumulator());
    if (result) {
        return *result;
    }
    return LeftWing();
}

LeftWing operator*(LeftWing& lw, CentreMid& cm) {
    
    memory.storePosition(std::make_shared<LeftWing>(lw));
    memory.storePosition(std::make_shared<CentreMid>(cm));
    cpu.load(0, memory.getCounter() -2);
    cpu.load(1, memory.getCounter() -1);
    cpu.multiply();
    cpu.storeAccumulator(memory.getCounter()+1);
    
    //cpu.printAccumulator();
    
    auto result = std::dynamic_pointer_cast<LeftWing>(cpu.getAccumulator());
    if (result) {
        return *result;
    }
    return LeftWing();
}

LeftWing operator*(LeftWing& lw, Striker& st) {
   
    memory.storePosition( std::make_shared<LeftWing>(lw));
    memory.storePosition( std::make_shared<Striker>(st));
    cpu.load(0, memory.getCounter() -2);
    cpu.load(1, memory.getCounter() -1);
    cpu.multiply();
    cpu.storeAccumulator(memory.getCounter()+1);
    
    //cpu.printAccumulator();
    
    auto result = std::dynamic_pointer_cast<LeftWing>(cpu.getAccumulator());
    if (result) {
        return *result;
    }
    return LeftWing();
}

//multiply centremid
CentreMid operator*(CentreMid& cm, Striker& st) {
    
    memory.storePosition( std::make_shared<CentreMid>(cm));
    memory.storePosition( std::make_shared<Striker>(st));
    cpu.load(0, memory.getCounter() -2);
    cpu.load(1, memory.getCounter() -1);
    cpu.multiply();
    cpu.storeAccumulator(memory.getCounter()+1);
    
    //cpu.printAccumulator();
    
    auto result = std::dynamic_pointer_cast<CentreMid>(cpu.getAccumulator());
    if (result) {
        return *result;
    }
    return CentreMid();
}

CentreMid operator*(CentreMid& cm, LeftWing& lw) {
  
    memory.storePosition( std::make_shared<CentreMid>(cm));
    memory.storePosition(std::make_shared<LeftWing>(lw));
    cpu.load(0, memory.getCounter() -2);
    cpu.load(1, memory.getCounter() -1);
    cpu.multiply();
    cpu.storeAccumulator(memory.getCounter()+1);
    
    //cpu.printAccumulator();
    
    auto result = std::dynamic_pointer_cast<CentreMid>(cpu.getAccumulator());
    if (result) {
        return *result;
    }
    return CentreMid();
}

CentreMid operator*(CentreMid& cm, CentreMid& lw) {
  
    memory.storePosition( std::make_shared<CentreMid>(cm));
    memory.storePosition(std::make_shared<CentreMid>(lw));
    cpu.load(0, memory.getCounter() -2);
    cpu.load(1, memory.getCounter() -1);
    cpu.multiply();
    cpu.storeAccumulator(memory.getCounter()+1);
    
    //cpu.printAccumulator();
    
    auto result = std::dynamic_pointer_cast<CentreMid>(cpu.getAccumulator());
    if (result) {
        return *result;
    }
    return CentreMid();
}

//divide striker
LeftWing operator/(Striker& s, LeftWing& x) {
  
    memory.storePosition( std::make_shared<Striker>(s));
    memory.storePosition( std::make_shared<LeftWing>(x));
    cpu.load(0, memory.getCounter()-1);
    cpu.load(1, memory.getCounter());
    cpu.divide();
    cpu.storeAccumulator(memory.getCounter()+1);
    
    //cpu.printAccumulator();
    
    auto result = std::dynamic_pointer_cast<LeftWing>(cpu.getAccumulator());
    if (result) {
        return *result;
    }
    return LeftWing();
}

Striker operator/(Striker& s, Striker& x) {
   
    memory.storePosition( std::make_shared<Striker>(s));
    memory.storePosition(std::make_shared<Striker>(x));
    cpu.load(0, memory.getCounter() - 1);
    cpu.load(1, memory.getCounter() - 2);
    cpu.divide();
    cpu.storeAccumulator(memory.getCounter()+1);
    
    //cpu.printAccumulator();
    
    auto result = std::dynamic_pointer_cast<Striker>(cpu.getAccumulator());
    if (result) {
        return *result;
    }
    return Striker();
}

CentreMid operator/(Striker& s, CentreMid& x) {
    memory.storePosition( std::make_shared<Striker>(s));
    memory.storePosition( std::make_shared<CentreMid>(x));
    cpu.load(0, memory.getCounter());
    cpu.load(1, memory.getCounter() -1);
    cpu.divide();
    cpu.storeAccumulator(memory.getCounter()+1);
    
    
    auto result = std::dynamic_pointer_cast<CentreMid>(cpu.getAccumulator());
    if (result) {
        return *result;
    }
    return CentreMid();
}

//divide leftwing
LeftWing operator/(LeftWing& cm, LeftWing& lw) {
   
    memory.storePosition( std::make_shared<LeftWing>(cm));
    memory.storePosition( std::make_shared<LeftWing>(lw));
    cpu.load(0, memory.getCounter() -2);
    cpu.load(1, memory.getCounter() -1);
    cpu.divide();
    cpu.storeAccumulator(memory.getCounter()+1);
    
    //cpu.printAccumulator();
    
    auto result = std::dynamic_pointer_cast<LeftWing>(cpu.getAccumulator());
    if (result) {
        return *result;
    }
    return LeftWing();
}

LeftWing operator/(LeftWing& lw, CentreMid& cm) {
    
    memory.storePosition(std::make_shared<LeftWing>(lw));
    memory.storePosition(std::make_shared<CentreMid>(cm));
    cpu.load(0, memory.getCounter() -2);
    cpu.load(1, memory.getCounter() -1);
    cpu.divide();
    cpu.storeAccumulator(memory.getCounter()+1);
    
    //cpu.printAccumulator();
    
    auto result = std::dynamic_pointer_cast<LeftWing>(cpu.getAccumulator());
    if (result) {
        return *result;
    }
    return LeftWing();
}

LeftWing operator/(LeftWing& lw, Striker& st) {
   
    memory.storePosition( std::make_shared<LeftWing>(lw));
    memory.storePosition( std::make_shared<Striker>(st));
    cpu.load(0, memory.getCounter() -2);
    cpu.load(1, memory.getCounter() -1);
    cpu.divide();
    cpu.storeAccumulator(memory.getCounter()+1);
    
    //cpu.printAccumulator();
    
    auto result = std::dynamic_pointer_cast<LeftWing>(cpu.getAccumulator());
    if (result) {
        return *result;
    }
    return LeftWing();
}

//divide centremid
CentreMid operator/(CentreMid& cm, Striker& st) {
    
    memory.storePosition( std::make_shared<CentreMid>(cm));
    memory.storePosition( std::make_shared<Striker>(st));
    cpu.load(0, memory.getCounter() -2);
    cpu.load(1, memory.getCounter() -1);
    cpu.divide();
    cpu.storeAccumulator(memory.getCounter()+1);
    
    //cpu.printAccumulator();
    
    auto result = std::dynamic_pointer_cast<CentreMid>(cpu.getAccumulator());
    if (result) {
        return *result;
    }
    return CentreMid();
}

CentreMid operator/(CentreMid& cm, LeftWing& lw) {
  
    memory.storePosition( std::make_shared<CentreMid>(cm));
    memory.storePosition(std::make_shared<LeftWing>(lw));
    cpu.load(0, memory.getCounter() -2);
    cpu.load(1, memory.getCounter() -1);
    cpu.divide();
    cpu.storeAccumulator(memory.getCounter()+1);
    
    //cpu.printAccumulator();
    
    auto result = std::dynamic_pointer_cast<CentreMid>(cpu.getAccumulator());
    if (result) {
        return *result;
    }
    return CentreMid();
}

CentreMid operator/(CentreMid& cm, CentreMid& lw) {
  
    memory.storePosition( std::make_shared<CentreMid>(cm));
    memory.storePosition(std::make_shared<CentreMid>(lw));
    cpu.load(0, memory.getCounter() -2);
    cpu.load(1, memory.getCounter() -1);
    cpu.divide();
    cpu.storeAccumulator(memory.getCounter()+1);
    
    //cpu.printAccumulator();
    
    auto result = std::dynamic_pointer_cast<CentreMid>(cpu.getAccumulator());
    if (result) {
        return *result;
    }
    return CentreMid();
}

//compare strikers
bool operator==(Striker& s, Striker& x) {
   
    memory.storePosition( std::make_shared<Striker>(s));
    memory.storePosition(std::make_shared<Striker>(x));
    cpu.load(0, memory.getCounter() - 1);
    cpu.load(1, memory.getCounter() - 2);
    
    
    
    if (cpu.compare()==false)
    {
        return false;
    }
    
    else if(cpu.compare()==true)
            {
                return true;
            }
    else{
        return false;
    }
}

bool operator==(CentreMid& s, CentreMid& x) {
    memory.storePosition( std::make_shared<CentreMid>(s));
    memory.storePosition( std::make_shared<CentreMid>(x));
    cpu.load(0, memory.getCounter());
    cpu.load(1, memory.getCounter() -1);;
    
    
    if (cpu.compare()==false)
    {
        return false;
    }
    
    else if(cpu.compare()==true)
            {
                return true;
            }
    else{
        return false;
    }
}

bool operator==(LeftWing& cm, LeftWing& st) {
    
    memory.storePosition( std::make_shared<LeftWing>(cm));
    memory.storePosition( std::make_shared<LeftWing>(st));
    cpu.load(0, memory.getCounter() -2);
    cpu.load(1, memory.getCounter() -1);
    
    if (cpu.compare()==false)
    {
        return false;
    }
    
    else if(cpu.compare()==true)
            {
                return true;
            }
    else{
        return false;
    }
}

bool operator==(RightWing& cm, RightWing& st) {
    
    memory.storePosition( std::make_shared<RightWing>(cm));
    memory.storePosition( std::make_shared<RightWing>(st));
    cpu.load(0, memory.getCounter() -2);
    cpu.load(1, memory.getCounter() -1);
    
    if (cpu.compare()==false)
    {
        return false;
    }
    
    else if(cpu.compare()==true)
            {
                return true;
            }
    else{
        return false;
    }
}

bool operator==(Defender& cm, Defender& st) {
    
    memory.storePosition( std::make_shared<Defender>(cm));
    memory.storePosition( std::make_shared<Defender>(st));
    cpu.load(0, memory.getCounter() -2);
    cpu.load(1, memory.getCounter() -1);
    
    if (cpu.compare()==false)
    {
        return false;
    }
    
    else if(cpu.compare()==true)
            {
                return true;
            }
    else{
        return false;
    }
}


Pass& operator||(Pass& o, const LeftWing& lw)
{
    o ||lw.getValueDouble();
    return o;
}
Pass& operator||(Pass& o, const CentreMid& cm)
{
    o ||cm.getValueFloat();
    return o;
}

Pass& operator||(Pass& o, const Defender& cm)
{
    o ||cm.getValueChar();
    return o;
}



    Kick kick;
    Pass pass;

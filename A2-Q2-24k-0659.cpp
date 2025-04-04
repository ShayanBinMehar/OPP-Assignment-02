#include <iostream>
#include <string>

class Ghost {
protected:
    std::string name;
    int scareLevel;

public:
    Ghost(std::string n, int level) : name(n), scareLevel(level) {}
    virtual void haunt() = 0;
    int getScareLevel() const { return scareLevel; }
    friend std::ostream& operator<<(std::ostream& os, const Ghost& ghost) {
        os << "Ghost Name: " << ghost.name << ", Scare Level: " << ghost.scareLevel;
        return os;
    }
    virtual ~Ghost() {}
};

class Poltergeist : public Ghost {
public:
    Poltergeist(std::string n, int level) : Ghost(n, level) {}
    void haunt() override {
        std::cout << name << " moves objects around!" << std::endl;
    }
};

class Banshee : public Ghost {
public:
    Banshee(std::string n, int level) : Ghost(n, level) {}
    void haunt() override {
        std::cout << name << " screams loudly!" << std::endl;
    }
};

class ShadowGhost : public Ghost {
public:
    ShadowGhost(std::string n, int level) : Ghost(n, level) {}
    void haunt() override {
        std::cout << name << " whispers creepily!" << std::endl;
    }
};

class ShadowPoltergeist : public Ghost {
public:
    ShadowPoltergeist(std::string n, int level) : Ghost(n, level) {}
    void haunt() override {
        std::cout << name << " moves objects and whispers creepily!" << std::endl;
    }
};

class Visitor {
private:
    std::string name;
    int bravery;

public:
    Visitor(std::string n, int b) : name(n), bravery(b) {}
    int getBravery() const { return bravery; }
    std::string getName() const { return name; }
};

class HauntedHouse {
private:
    std::string name;
    Ghost* ghosts[10];
    int ghostCount;

public:
    HauntedHouse(std::string n) : name(n), ghostCount(0) {}

    void addGhost(Ghost* ghost) {
        if (ghostCount < 10) {
            ghosts[ghostCount++] = ghost;
        } else {
            std::cout << "Haunted House is full!" << std::endl;
        }
    }

    void simulateVisit(Visitor visitors[], int visitorCount) {
        std::cout << "\nVisitors enter " << name << "...\n";

        for (int i = 0; i < visitorCount; ++i) {
            for (int j = 0; j < ghostCount; ++j) {
                ghosts[j]->haunt();
                if (ghosts[j]->getScareLevel() < visitors[i].getBravery()) {
                    std::cout << visitors[i].getName() << " laughs at the ghost!" << std::endl;
                } else if (ghosts[j]->getScareLevel() > visitors[i].getBravery() + 2) {
                    std::cout << visitors[i].getName() << " runs away!" << std::endl;
                } else {
                    std::cout << visitors[i].getName() << " has a shaky voice!" << std::endl;
                }
            }
        }
    }

    void cleanup() {
        for (int i = 0; i < ghostCount; ++i) {
            delete ghosts[i];
        }
    }
};

void visit(Visitor visitors[], int visitorCount, HauntedHouse& house) {
    house.simulateVisit(visitors, visitorCount);
}

int main() {

    HauntedHouse house1("Spooky Manor");
    HauntedHouse house2("Creepy Castle");

    house1.addGhost(new Poltergeist("Polly", 5));
    house1.addGhost(new Banshee("Banshee Betty", 8));
    house1.addGhost(new ShadowGhost("Shadow Sam", 6));

    house2.addGhost(new ShadowPoltergeist("Shadow Polly", 7));

    Visitor visitors[] = {
        Visitor("Alice", 3),
        Visitor("Bob", 6),
        Visitor("Charlie", 9)
    };

    visit(visitors, 3, house1);
    visit(visitors, 3, house2);

    house1.cleanup();
    house2.cleanup();

    return 0;
}

#include <iostream>
#include <random>

std::mt19937 mt{std::random_device{}()};

class Creature{
  protected:
        std::string name{"???"};
        char symbol{' '};
        int health{};
        int damage_per_attack{};
        int gold{};
    public:
        Creature(std::string name, char symbol, int health, int damage_per_attack, int gold): 
        name{name}, 
        symbol{symbol}, 
        health{health},
        damage_per_attack{damage_per_attack},
        gold{gold}
        {}

        std::string getName() const {return name;}
        char getSymbol() const {return symbol;}
        int getHealth() const {return health;}
        int getDamage() const {return damage_per_attack;}
        int getGold() const {return gold;}

        void reduceHealth(int amount){health-=amount;}
        bool isDead(){return ((health <= 0) ? true : false);}
        void addGold(int amount){gold+=amount;}
};

class Player: public Creature{
    private:
        int lvl;
    public:
        Player(std::string name): 
        Creature{name, '@', 10, 1, 0},
        lvl{1}
        {}
        
        int getLvl() const {return lvl;}
        void levelUp(){damage_per_attack++; lvl++;}
        bool hasWon(){return lvl >= 20 ? true : false;}
        void increaseStrength(int amount){damage_per_attack+=amount;}
};

class Monster: public Creature{
    public:
        enum Type{dragon, orc, slime, max_type};
    private:
        //static because it is shared among all instances
        //inline to define it inside the class
        static inline Creature monsterData[]{
            Creature{"dragon", 'D', 20, 4, 100},
            Creature{"orc", 'o', 4, 2, 25},
            Creature{"slime", 's', 1, 1, 10}
        };
    public:
        Monster(Type monster): Creature{monsterData[monster]}{}
        //static member function to allow use of static variable without instantiating an object of the class
        static Monster getRandomMonster(){
            std::uniform_int_distribution<> rand_monster(0, max_type-1);

            return Monster{static_cast<Type>(rand_monster(mt))};
        }
};

void generateNewMonster(Monster& m){
    m = Monster::getRandomMonster();
	std::cout << "A " << m.getName() << " (" << m.getSymbol() << ") was created.\n";
}

void generatePotion(Player& p){
    enum PotionType{smallHealth, mediumHealth, largeHealth,
                    smallStrength, mediumStrength, largeStrength,
                    smallPoison, mediumPoison, largePoison, maxPotion};

    int potion_table[]{-2, -2, -5,
                        1,  1,  1,
                        1,  1,  1};

    //30% chance -> need ten numbers of equal distribution to make that happen
    std::uniform_int_distribution<> chance30(0, 9);
    std::uniform_int_distribution<> die9(0, maxPotion-1);

    int position = die9(mt);
    char decision = 'N';

    if(chance30(mt) < 3){
        std::cout << "Drink me!\n (Y)es or (N)o: ";
        std::cin >> decision;

        if(decision == 'Y'){
            if (position/3 == 1){
                p.increaseStrength(potion_table[position]);
                std::cout << "You've ingested " << static_cast<PotionType>(position) << " and now your strength is " << p.getDamage() << "\n";
            }else{
                p.reduceHealth(potion_table[position]);
                std::cout << "You've ingested " << static_cast<PotionType>(position) << " and now your health is " << p.getHealth() << "\n";
            }
        }
    }
}

void run(Player& p, Monster& m){
    std::uniform_int_distribution<> escape(0, 1);

    if(escape(mt)){
        std::cout << "Run, Forest! Run!\n";
        generateNewMonster(m);

    }else{
        std::cout << "Why are you runnin'?\n";
        std::cout << "The " << m.getName() << " dealt " << m.getDamage() << " stab(s).\n";
        
        p.reduceHealth(m.getDamage());
    }
}

void fight(Player& p, Monster& m){
    std::cout<< "You've dealt " << p.getDamage() << " stab(s) to " << m.getName() << ".\n";
    m.reduceHealth(p.getDamage());

    if(m.getHealth() <= 0){
        p.addGold(m.getGold());
        p.levelUp();
        
        std::cout << "You've killed the " << m.getName() << ". It's children will weep tonight.\n";
        std::cout << "But! Killing it has won you: " << m.getGold() << " virtual gold coins.\n";
        std::cout << "And allowed you to level up: " << p.getLvl() << ". Congrats :D.\n";

        generatePotion(p);
        generateNewMonster(m);

        }else{
        std::cout << "And it was kind enough deal some back, " << m.getDamage() << " stab(s) to be exact!\n";
        p.reduceHealth(m.getDamage());
    }
}

int main()
{
    std::string name;
    std::cout << "Enter your name: ";
    std::cin >> name;

    Player p1{name};
    std::cout << "Welcome, " << p1.getName() << ".\n";

    char decision = 'F';

    Monster m{Monster::Type::dragon};
    generateNewMonster(m);
   
    while(!p1.hasWon() && !p1.isDead()){

        std::cout << "(R)un or (F)ight: ";
        std::cin >> decision;

        if(decision == 'R'){
            run(p1, m);
        }else{
            fight(p1, m);
        }

        std::cout << "HEALTH: " << p1.getHealth() << "\n";
        std::cout << "STRENGTH: " << p1.getDamage() << "\n";
    }

    if(p1.hasWon())
        std::cout << "Player " << p1.getName() << " congratulations! You've won with a grand total of " << p1.getGold() << " virtual gold coins. Go touch grass!\n";
    else
        std::cout << "Player " << p1.getName() << " congratulations! You've lost at a pitiful " << p1.getLvl() << ". level having only aquired " << p1.getGold() << " virtual gold coins.\n";

	return 0;
}
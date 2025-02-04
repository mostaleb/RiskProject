#include "Orders.h"
#include "LogObserver.h"
#include <sstream>

using std::cout;
using std::endl;
using std::ostream;

Order::Order() {}
Deploy::Deploy() : Order() {};
Order::Order(Order *next, int orderType) : next(next), orderType(orderType) {}
Deploy::Deploy(Order *next, int orderType) : Order(next, orderType) { cout << "Deploy order created" << endl; }
Advance::Advance(Order *next, int orderType) : Order(next, orderType) { cout << "Advance order created" << endl; }
Bomb::Bomb(Order *next, int orderType) : Order(next, orderType) { cout << "Bomb order created" << endl; }
Blockade::Blockade(Order *next, int orderType) : Order(next, orderType) { cout << "Blockade order created" << endl; }
Airlift::Airlift(Order *next, int orderType) : Order(next, orderType) { cout << "Airlift order created" << endl; }
Negotiate::Negotiate(Order *next, int orderType) : Order(next, orderType) { cout << "Negotiate order created" << endl; }
OrderList::OrderList() : head(nullptr), tail(nullptr) { cout << "Empty OrderList Successfully Created" << endl; }

void OrderList::Notify(ILoggable *ol){
    LogObserver lo;
    lo.Update(ol);
}

std::string OrderList::stringToLog(){
    std::cout << "Order added to the order list: " << getTail()->orderType << std::endl;
    std::string str;
    std::stringstream ss;
    ss << getTail()->orderType;
    ss >> str;
    return "Order added to the order list: " + str + ".\n";
}
void OrderList::add(Order *o)
{
    if (head == nullptr && tail == nullptr)
    { // initial case - empty Order List

        std::cout << "Initial case - empty List" << std::endl;

        this->head = o;
        this->tail = o;
    }
    else
    {
        // Non-empty case
        this->tail->next = o;
        this->tail = o;
    }

    std::cout << "List has " << OrderList::length() << " Order objects" << std::endl;
    Notify(this);
}

// The functions prints every members of the list
void OrderList::print()
{

    if (this->head != nullptr)
    {
        // When the list is not empty
        Order *curr = this->head;

        while (curr != nullptr)
        {

            std::cout << "Order ID: " << curr->orderType << std::endl;
            curr = curr->next;
        }
    }
    else
    {
        // When the list is empty
        std::cout << "Empty list" << std::endl;
    }
}

// Accessor for head
const Order *OrderList::getHead()
{
    return head;
}

// Accessor for tail
const Order *OrderList::getTail()
{
    return tail;
}

// The function moves an order from one position in the list to another
void OrderList::move(int position, int newPosition) // position is the index of the order to move
{                                                   // newPosition is the index the order has to be moved to

    if (position < 0 || position > OrderList::length() || newPosition < 0 || newPosition > OrderList::length())
    {
        cout << "The position(s) is(are) not valid" << endl;
    }
    else if (position == newPosition)
    {
        cout << "The new position is the same as the actual position" << endl;
    }
    else
    {
        if (head == nullptr)
        {
            // The list is empty
            cout << "The list is empty" << endl;
        }
        else if (head->next == nullptr)
        {
            // The list only has one order
            cout << "There's only one order in the list, it cannot move anywhere" << endl;
        }
        else
        {
            Order *beforeP = this->head; // Temporary pointer to that is used to traverse the list
            if (position == 1)
            {
                this->head = beforeP->next;

                Order *holder = beforeP;
                beforeP->next = beforeP->next->next;
                holder->next = nullptr;

                Order *beforeNP = this->head;

                // Traverse the list to the new position
                if (newPosition < position)
                {
                    while (newPosition > 1)
                    {
                        beforeNP = beforeNP->next;
                        newPosition--;
                    }
                }
                else
                {
                    while (newPosition > 2)
                    {
                        beforeNP = beforeNP->next;
                        newPosition--;
                    }
                }
                holder->next = beforeNP->next;
                beforeNP->next = holder;
            }
            else if (newPosition == 1)
            {
                while (position > 2)
                {
                    beforeP = beforeP->next;
                    position--;
                }
                Order *holder = beforeP->next;
                beforeP->next = beforeP->next->next;
                holder->next = nullptr;
                holder->next = head;
                head = holder;
            }
            else
            {
                // When the position is other that one, it needs to traverse the list
                while (position > 2)
                {
                    beforeP = beforeP->next;
                    position--;
                }
                Order *holder = beforeP->next;
                beforeP->next = beforeP->next->next;
                holder->next = nullptr;

                Order *beforeNP = this->head;

                // Traverse the list to the new position
                if (newPosition < position)
                {
                    while (newPosition > 1)
                    {
                        beforeNP = beforeNP->next;
                        newPosition--;
                    }
                }
                else
                {
                    while (newPosition > 2)
                    {
                        beforeNP = beforeNP->next;
                        newPosition--;
                    }
                }
                holder->next = beforeNP->next;
                beforeNP->next = holder;
            }
        }
    }
}

// The function removes an order at a given position
void OrderList::remove(int position)
{
    int positionTemp = position; // To keep track of the original position
    if (head == nullptr)
    {
        // The list is empty
        cout << "Nothing to be removed" << endl;
    }
    else if (position < 0 || position > OrderList::length())
    {
        // The input is invalid
        cout << "Entered position is not valid" << endl;
    }
    else
    {
        Order *beforeP = this->head; // Temporary pointer to that is used to traverse the list
        if (position == 1)
        {
            // When the position is 1 no need to traverse the list
            head = beforeP->next;
            delete beforeP;
        }
        else
        {
            // When the position is other that one, it needs to traverse the list
            while (position > 2)
            {
                beforeP = beforeP->next;
                position--;
            }
            beforeP->next = beforeP->next->next;
            if (positionTemp == OrderList::length()) // When the last position is removed,
            {                                        // the tail has to be set again
                this->tail = beforeP->next;
            }
            delete beforeP;
        }
    }
}

// The function return the length of the list
int OrderList::length()
{
    if (head == nullptr)
    {
        // The list is empty
        return 0;
    }
    else
    {
        // The list is not empty
        Order *curr = this->head;
        int length = 0;
        while (curr != nullptr)
        {
            length++;
            curr = curr->next;
        }
        return length;
    }
}

// Validation function
void Order::validation()
{
    cout << orderType << " is being validated..." << endl;
}

// Execution function
void Order::execution()
{
    Order::validation();
    cout << orderType << " is being executed..." << endl;
}

// Copy constructor (deep copy) of Order
Order::Order(const Order &o)
{
    orderType = o.orderType;
    next = nullptr;
}

// Copy constructor (deep copy) of OrderList
OrderList::OrderList(const OrderList &ol)
{

    if (head == nullptr)
    {
        // Empty list case
        cout << "The list is empty." << endl;
    }
    // else
    // {
    //     // First, we set the tail and head on the first order manually (wihtout the loop)
    //     Order *temp = ol.head;
    //     head = new Order(*(temp));
    //     tail = head;
    //     Order *curr = head;
    //     // Second, all the orders are copied and linked to each other
    //     while (temp->next != nullptr)
    //     {
    //         temp = temp->next;
    //         curr->next = new Order(*(temp));
    //         curr = curr->next;
    //         tail = curr;
    //     }
    // }
}

// Stream insertion operator implementation
ostream &operator<<(ostream &out, Order &o)
{
    switch (o.orderType)
    {
    case 1:
        out << "Deploy order: place some armies on one of the current player’s territories." << endl;
        break;
    case 2:
        out << "Advance order: move some armies from one of the current player’s territories (source) to an adjacent territory\n"
            << "(target). If the target territory belongs to the current player, the armies are moved to the target\n"
            << "territory. If the target territory belongs to another player, an attack happens between the two\n"
            << "territories." << endl;
        break;
    case 3:
        out << "Bomb order: destroy half of the armies located on an opponent’s territory that is adjacent to one of the current\n"
            << "player’s territories." << endl;
        break;
    case 4:
        out << "Blockade order: triple the number of armies on one of the current player’s territories and make it a neutral territory." << endl;
        break;
    case 5:
        out << "Airlift order: advance some armies from one of the current player’s territories to any another territory." << endl;
        break;
    case 6:
        out << "Negotiate order: prevent attacks between the current player and another player until the end of the turn." << endl;
        break;
    default:
        out << "There is a mistake, this order doesn't exist." << endl;
    }
    out << "Execution satus: " << endl;
    o.execution();

    return out;
}

void Deploy::Notify(ILoggable *d){
    LogObserver lo;
    lo.Update(d);
}
void Advance::Notify(ILoggable *a){
    LogObserver lo;
    lo.Update(a);
}
void Blockade::Notify(ILoggable *b){
    LogObserver lo;
    lo.Update(b);
}
void Bomb::Notify(ILoggable *bo){
    LogObserver lo;
    lo.Update(bo);
}
void Airlift::Notify(ILoggable *al){
    LogObserver lo;
    lo.Update(al);
}
void Negotiate::Notify(ILoggable *n){
    LogObserver lo;
    lo.Update(n);
}

std::string Deploy::stringToLog(){
    std::cout << "Deploy order executed." << std::endl;
    return "Deploy order executed.\n";
}
std::string Advance::stringToLog(){
    std::cout << "Advance order executed." << std::endl;
    return "Advance order executed.\n";
}
std::string Blockade::stringToLog(){
    std::cout << "Blockade order executed." << std::endl;
    return "Blockafe order executed.\n";
}
std::string Bomb::stringToLog(){
    std::cout << "Bomb order executed." << std::endl;
    return "Bomb order executed.\n";
}
std::string Airlift::stringToLog(){
    std::cout << "Airlift order executed." << std::endl;
    return "Airlift order executed.\n";
}
std::string Negotiate::stringToLog(){
    std::cout << "Negotiate order executed." << std::endl;
    return "Negotiate order executed.\n";
}

void Deploy::execute() {
    Notify(this);
    return;//Temporary
    std::cout << "entered in deploy execute" << std::endl << std::endl;
    bool isValid = false;
    Territory* t = nullptr;
    if(player != nullptr) {
        for(const auto& _t : player->territories) {
            if(_t->getCountry() == territory) {
                isValid = true;
                t = _t;
                break;
            } 
        }

        if(!isValid){
            std::cout << "You do not own this territory, please try a different one" << std::endl;
            return;
        }

        t->setArmyCount(armyCount);
        std::cout << armyCount << " troops deployed to " << t->getCountry() << std::endl;
        
    }
    else {
        std::cout << "Deploy ordered not properly configured" << std::endl;
    }   
}

void Advance::execute() {
    Notify(this);
    Territory *terr1 = nullptr, *terr2 = nullptr;
    return;//Temporary
    for(const auto& _t : src->territories) {
        if(_t->getCountry() == t1) {
            terr1 = _t;
            break;
        }
    }

    if(terr1 == nullptr) {
        std::cout << "Order is invalid, you do not own source territory" << std::endl;
        return;
    }

    for(const auto& t : src->territories) {
        for(const auto& edge : edges) {
            if(edge->AdjacencyEdges.first == t || edge->AdjacencyEdges.second == t) {
                if(edge->AdjacencyEdges.first->getCountry() == t2) {
                    terr2 = edge->AdjacencyEdges.first;
                    break;
                }
                else if(edge->AdjacencyEdges.second->getCountry() == t2) {
                    terr2 = edge->AdjacencyEdges.second;
                    break;
                }
            }
        }

        if(terr2 != nullptr) break;
    }

    if(terr2 != nullptr) {
        bool playerOwner = false;
        for(const auto& t : src->territories) {
            if(terr2 == t) {
                playerOwner = true;
                break;
            }
        }

        if(playerOwner) {
            terr1->setArmyCount(terr1->getArmyCount() - armyCount);
            terr2->setArmyCount(terr2->getArmyCount() + armyCount);
        }
        else {

            int tempValue = armyCount;

            while(terr1->getArmyCount() != 0 || terr2->getArmyCount() != 0) {
                std::random_device                  rand_dev;
                std::mt19937                        generator(rand_dev());
                std::uniform_int_distribution<int>  distr(0,1);

                int number1 = distr(generator);

                if(number1 < 0.6) {
                    terr2->setArmyCount(terr2->getArmyCount() - 1);
                }

                int number2 = distr(generator);

                if(number2 < 0.7) {
                    armyCount -= 1;
                }
            }

            if(terr2->getArmyCount() == 0) {
                terr1->setArmyCount(terr1->getArmyCount() - armyCount);
                src->territories.push_back(terr2);
                
                int index = 0;
                for(const auto t : target->territories) {
                    if(t == terr2) break;
                    index++;
                }

                target->territories.erase(target->territories.begin() + index);
            
            }
            else {
                terr1->setArmyCount(terr1->getArmyCount() - tempValue);
            }
        }
    }
    else {
        std::cout << "Territories are not adjacent, order is invalid" << std::endl;
        return;
    }



}

void Blockade::execute() {
    Notify(this);
    return;//Temporary
    Territory* t = nullptr;
    int index = 0;

    for(const auto& _t : player->territories) {
        if(_t->getCountry() == t1) {
            t = _t;
            break;
        }
        index++;
    }

    if(t == nullptr) {
        std::cout << "Order is invalid, you do not own this territory" << std::endl;
        return;
    }

    t->setArmyCount(t->getArmyCount() * 2);
    neutralPlayer = new Player("neutral player");
    neutralPlayer->territories.push_back(t);
    player->territories.erase(player->territories.begin() + index);

    std::cout << "Army count at territory " << t->getCountry() << " has increased from " << t->getArmyCount() / 2 << " to " << t->getArmyCount() << " and is now owned by the neutral player" << std::endl;
    return;
}

void Bomb::execute() {
    Notify(this);
    return;//Temporary
    Territory* t = nullptr;

    for(const auto& _t : owner->territories) {
        if(_t->getCountry() == t1) {
            t = _t; 
            break;
        }
    }

    if(t != nullptr) {
        std::cout << "Order is invalid, you own this territory" << std::endl;
        return;
    }

    Territory* target = nullptr;

    for(const auto& t : owner->territories) {
        for(const auto& edge : edges) {
            if(edge->AdjacencyEdges.first == t || edge->AdjacencyEdges.second == t) {
                if(edge->AdjacencyEdges.first->getCountry() == t1) {
                    target = edge->AdjacencyEdges.first;
                    break;
                }
                else if(edge->AdjacencyEdges.second->getCountry() == t1) {
                    target = edge->AdjacencyEdges.second;
                    break;
                }
            }
        }

        if(target != nullptr) break;
    }

    if(target != nullptr) {
        target->setArmyCount(target->getArmyCount() / 2);
    }
    else {
        std::cout << "Territories are not adjacent, cannot issue bomb order" << std::endl;
        return;
    }



}

void Airlift::execute() {
    Notify(this);
    return;//Temporary
    Territory *source = nullptr, *target = nullptr;

    for(const auto& t : player->territories) {
        if(t->getCountry() == t1) {
            source = t;
        }
        else if(t->getCountry() == t2) {
            target = t;
        }
    }

    if(source == nullptr || target == nullptr ) {
        std::cout << "Order is invalid, you do not own both territories" << std::endl;
        return;
    }

    source->setArmyCount(source->getArmyCount() - armyCount);
    target->setArmyCount(target->getArmyCount() + armyCount);
    std::cout << armyCount << " troops successfully deployed from " << source->getCountry() << " to " << target->getArmyCount() << std::endl;
}

void Negotiate::execute() {
    Notify(this);
    return;//Temporary
    if(target == src) {
        std::cout << "Invalid order, target selected is the same as source" << std::endl;
        return;
    }

    src->unAttackableName = target->name;
    target->unAttackableName = src->name;
    return;

}
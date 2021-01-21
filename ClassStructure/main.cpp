#include <iostream>
#include "Bed.h"
#include "Chair.h"
#include "Column.h"
#include "Door.h"
#include "TableLamp.h"
#include "Wall.h"
#include "Fridge.h"

int main() {
    auto* bed = new Bed();
    auto* chair = new Chair();
    auto* column = new Column();
    auto* door = new Door();
    auto* tableLamp = new TableLamp();
    auto* wall = new Wall();
    auto* fridge = new Fridge();

//    bed->setId(1);
//    bed->setName("prachtig mooi tweepersoonsbed van Hank");
//    bed->setDescription("super zacht bed slaap lekker!");
//    bed->setStatus(1);
//    bed->setLedStatus(0);
//    bed->setDescription("super zacht bed slaap lekker!");
//    bed->setDescription("super zacht bed slaap lekker!");
//    bed->setDescription("super zacht bed slaap lekker!");
//    bed->setDescription("super zacht bed slaap lekker!");
//
//    cout << bed->getId() << endl;
//    cout << bed->getName() << endl;
//    cout << bed->getDescription() << endl;
//    cout << bed->getLedStatus() << endl;
//    cout << bed->getStatus() << endl;
}

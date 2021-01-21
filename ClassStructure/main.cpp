#include <iostream>
#include "Bed.h"
#include "Chair.h"
#include "Column.h"
#include "Door.h"
#include "TableLamp.h"
#include "Wall.h"
#include "Fridge.h"

int main() {
    auto* bed = new Bed(1, "Hanks Bed", "Super nice bed");
    auto* chair = new Chair();
    auto* column = new Column();
    auto* door = new Door();
    auto* tableLamp = new TableLamp();
    auto* wall = new Wall();
    auto* fridge = new Fridge();


    bed->getLedStatus();
    cout << bed->getLedStatus() << endl;
    bed->toggleLedStatus();
    cout << bed->getLedStatus() << endl;
}

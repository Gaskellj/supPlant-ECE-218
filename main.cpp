#include "smart_plant_system.h"

// main() runs in its own thread in the OS
int main()
{
    smartPlantSystemInit();
    while (true) {
        smartPlantSystemUpdate();
    }
}


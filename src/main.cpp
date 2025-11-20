#include "system_controller.h"
#include "temperature_sensor.h"
#include "humidity_sensor.h"
#include "pressure_sensor.h"
#include <iostream>
#include <memory>

int main() {
    SystemController ctrl;

    ctrl.addSensor(std::make_unique<TemperatureSensor>("room1", -5.0, 35.0));
    ctrl.addSensor(std::make_unique<TemperatureSensor>("room2", -5.0, 35.0));
    ctrl.addSensor(std::make_unique<HumiditySensor>("room1", 10.0, 90.0));
    ctrl.addSensor(std::make_unique<PressureSensor>("outdoor", 980.0, 1050.0));

    bool running = true;
    while (running) {
        std::cout << "\n=== MENY ===\n";
        std::cout << "1) Läs nya mätvärden från alla sensorer\n";
        std::cout << "2) Visa statistik för sensor\n";
        std::cout << "3) Visa alla mätvärden\n";
        std::cout << "4) Konfigurera tröskelregel\n";
        std::cout << "5) Visa larm\n";
        std::cout << "6) Spara mätdata till fil\n";
        std::cout << "7) Läs mätdata från fil\n";
        std::cout << "0) Avsluta\n";
        std::cout << "Välj: ";
        int choice;
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }
        std::cin.ignore(10000, '\n');
        switch (choice) {
            case 1:
                ctrl.sampleAllOnce();
                break;
            case 2: {
                std::cout << "Sensor (exakt namn): ";
                std::string name;
                std::getline(std::cin, name);
                if (name.empty()) std::getline(std::cin, name);
                ctrl.showStatsFor(name);
                break;
            }
            case 3:
                ctrl.showAllMeasurements();
                break;
            case 4:
                ctrl.configureThresholdInteractive();
                break;
            case 5:
                ctrl.showAlerts();
                break;
            case 6: {
                std::cout << "Filnamn att spara till: ";
                std::string path;
                std::getline(std::cin, path);
                if (path.empty()) std::getline(std::cin, path);
                ctrl.saveMeasurements(path);
                break;
            }
            case 7: {
                std::cout << "Filnamn att läsa från: ";
                std::string path;
                std::getline(std::cin, path);
                if (path.empty()) std::getline(std::cin, path);
                ctrl.loadMeasurements(path);
                break;
            }
            case 0:
                running = false;
                break;
            default:
                std::cout << "Ogiltigt val\n";
        }
    }

    std::cout << "Avslutar.\n";
    return 0;
}

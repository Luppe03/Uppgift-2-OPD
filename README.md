OPD - Uppgift 2: Sensorövervakningssystem

Översikt: Denna uppgift bygger på Uppgift 1 och simulerar ett system som samlar in, lagrar och analyserar data från olika sensorer, tröskelbaserade larm har lagts till.

Programmet är skrivet i C++17 och använder arv, polymorfism och smarta pekare. 

Syftet med uppgiften är att träna på objektorienterad programmering i C++, inklusive arv, polymorfism, inkapsling samt användning av smarta pekare. Filhantering och grundläggande systemdesign tränas genom UML-diagram.

Filstruktur:
Uppgift 2/
├── .vscode/
│ ├── c_cpp_properties.json
│ └── settings.json
│
├── include/
│ ├── humidity_sensor.h
│ ├── measurement.h
│ ├── pressure_sensor.h
│ ├── sensor.h
│ ├── storage.h
│ ├── system_controller.h
│ ├── temperature_sensor.h
│ └── thresholds.h
│
├── src/
│ ├── humidity_sensor.cpp
│ ├── main.cpp
│ ├── pressure_sensor.cpp
│ ├── storage.cpp
│ ├── system_controller.cpp
│ └── temperature_sensor.cpp
│
├── uml/
│ └── diagram.puml
│
└── README.md

Bekskrivning:
".vscode/" - Inställningar för VS code.
"include/" - Klassdeklarationer. (.h)
"src/" - implementation av klasser och main programmet. (.cpp)
"uml/" - UML-diagram som visar klassrelationer.

Kompilering och körning:

1. Skriv g++ -std=c++17 src/*.cpp -Iinclude -o program.exe i terminalen.

2. Kör programmet genom att aningen skriva .\program.exe (windows) eller ./program.exe (macOS/linux)

Exempel på körning:

=== MENY ===
1) Läs nya mätvärden från alla sensorer
2) Visa statistik för sensor
3) Visa alla mätvärden
4) Konfigurera tröskelregel
5) Visa larm
6) Spara mätdata till fil
7) Läs mätdata från fil
0) Avsluta
Välj: 


Lukas Persson
Objektorienterad programmering i C++
STI
Inlämning 2

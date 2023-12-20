#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    double kloc;       // Size of the software in KLOC
    double a, b, c, d; // Constants
    double eaf;
    double model;
    // Input value
    cout << "Enter the size of the software in KLOC: ";
    cin >> kloc;
    cout << "Enter effort adjustment factor: ";
    cin >> eaf;
    cout << "Select model:\n1.Application Composition model\n2.Early Design model\n3.Post Architecture model\n";
    int m;
    cin >> m;

    if (m == 1)
    {
        cout<<"Application Composition model\n";
        a = 2.4;
        b = 1.05;
        c = 2.5;
        d = 0.38;
    }
    else if (m == 2)
    {
        cout<<"Early design model\n";
        a = 3.6;
        b = 1.20;
        c = 2.5;
        d = 0.32;
    }
    else
    {
        cout<<"Post architecture model\n";
        a = 3.0;
        b = 1.12;
        c = 2.5;
        d = 0.35;
    }

    // Calculate effort using COCOMO I
    double effort = a * pow(kloc, b) * eaf;

    // Calculate development time and persons required
    double development_time = c * pow(effort, d);
    int persons_required = ceil(effort / development_time);

    // Output the results

    cout << "COCOMO 2\n\nEffort Estimate : " << effort << " person-months\n";
    cout << "Development Time: " << development_time << " months\n";
    cout << "Persons Required: " << persons_required << " persons\n";

    return 0;
}

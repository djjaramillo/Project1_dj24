
#include <iostream>
using namespace std;

// Capacitor structure
struct _capacitor
{
    double *time;
    double *voltage;
    double *current;
    double C;
};

typedef struct _capacitor Capacitor;

//Main
int main()
{
    // Given values
    const double dt = 1e-10;
    const double finalTime = 5e-6;
    const int steps = 50000;

    const double R = 1000.0;
    const double C = 100e-12;
    const double I = 1e-2;
    const double V0 = 10.0;

    // Create capacitor structures
    Capacitor constantCurrent;
    Capacitor constantVoltage;

    constantCurrent.C = C;
    constantVoltage.C = C;

    // Allocate memory
    constantCurrent.time = new double[steps + 1];
    constantCurrent.voltage = new double[steps + 1];
    constantCurrent.current = new double[steps + 1];

    constantVoltage.time = new double[steps + 1];
    constantVoltage.voltage = new double[steps + 1];
    constantVoltage.current = new double[steps + 1];

    // Initial conditions for constant current
    constantCurrent.time[0] = 0;
    constantCurrent.voltage[0] = 0;
    constantCurrent.current[0] = I;

    // Initial conditions for constant voltage
    constantVoltage.time[0] = 0;
    constantVoltage.voltage[0] = 0;
    constantVoltage.current[0] = V0 / R;

    // Calculate values for each timestep
    for (int i = 1; i <= steps; i++)
    {
        // Constant current circuit
        constantCurrent.time[i] = i * dt;

        constantCurrent.current[i] = I;

	//Calculate voltage using the previous voltage and current
        constantCurrent.voltage[i] =
            constantCurrent.voltage[i - 1] +
            constantCurrent.current[i - 1] * dt /
            constantCurrent.C;

        // Constant voltage circuit
        constantVoltage.time[i] = i * dt;

	//Calculate current using the previous time step
        constantVoltage.current[i] =
            constantVoltage.current[i - 1] -
            (constantVoltage.current[i - 1] /
            (R * constantVoltage.C)) * dt;

        constantVoltage.voltage[i] =
            V0 - constantVoltage.current[i] * R;
    }

    // Print constant current results
    cout << "Constant Current Circuit" << endl;
    cout << "Time(s) Voltage(V) Current(A)" << endl;

    for (int i = 0; i <= steps; i += 200)
    {
        cout << constantCurrent.time[i] << " "
             << constantCurrent.voltage[i] << " "
             << constantCurrent.current[i] << endl;
    }

    // Print constant voltage results
    cout << endl;
    cout << "Constant Voltage Circuit" << endl;
    cout << "Time(s) Voltage(V) Current(A)" << endl;

    for (int i = 0; i <= steps; i += 200)
    {
        cout << constantVoltage.time[i] << " "
             << constantVoltage.voltage[i] << " "
             << constantVoltage.current[i] << endl;
    }

    // Free allocated memory
    delete[] constantCurrent.time;
    delete[] constantCurrent.voltage;
    delete[] constantCurrent.current;

    delete[] constantVoltage.time;
    delete[] constantVoltage.voltage;
    delete[] constantVoltage.current;

    return 0;
}

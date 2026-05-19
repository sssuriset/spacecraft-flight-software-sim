#ifndef THERMAL_H
#define THERMAL_H

class Thermal {
private:
    double temperatureC;
    bool heaterOn;

public:
    Thermal();

    void update(bool inSunlight);
    void setHeater(bool state);

    double getTemperatureC() const;
    bool isHeaterOn() const;
};

#endif
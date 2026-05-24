#ifndef POWER_H
#define POWER_H

class Power {
private:
    double batteryPercent;
    double batteryVoltage;
    bool solarCharging;

public:
    Power();

    void update(double loadWatts);
    void setSolarCharging(bool state);

    double getBatteryPercent() const;
    double getBatteryVoltage() const;
    bool isSolarCharging() const;
};

#endif

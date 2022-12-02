#pragma once

#include <map>
#include <vector>
#include <iostream>
#include <numeric>
#include <cassert>


using namespace std;

class Tables {
private:
    map<double, double> machToDrag;
    map<double, double> altitudeToDensity;
    map<double, double> altitudeToSpeedOfSound;
    map<double, double> altitudeToGravity;

    double getGreaterValue(double value, vector<double> values) {
        if (value > values.back()) {
            return values.back();
        }
        double greaterValue = -100.0;
        auto it = values.begin();
        while (value > *it && value != *it)
            it++;
        return greaterValue = *it;
    }

    double getLesserValue(double value, vector<double> values) {
        if (value < values.front()) {
            return values.front();
        }
        double greaterValue = -100.0;
        auto it = --values.end();
        while (value < *it && value != *it)
            it--;
        return greaterValue = *it;

    }

public:
    map<string, double> getDrag(double mach) {
        if (mach <= 0) {
            map<string, double> values;
            values["x0"] = 0;
            values["y0"] = 0.0;
            values["x1"] = 0.300;
            values["y1"] = 0.1629;
            return values;
        }
        else if (mach > 5.0) {
            map<string, double> values;
            values["x0"] = 2.890;
            values["y0"] = 0.2306;
            values["x1"] = 5.000;
            values["y1"] = 0.2656;
            return values;
        }

        vector<double> keys;
        for (auto it = machToDrag.begin(); it != machToDrag.end(); it++) {
            keys.push_back(it->first);
        }

        double x0 = getLesserValue(mach, keys);
        double y0 = machToDrag[x0];

        double x1 = getGreaterValue(mach, keys);
        double y1 = machToDrag[x1];

        map<string, double> values;
        values["x0"] = x0;
        values["y0"] = y0;
        values["x1"] = x1;
        values["y1"] = y1;

        return values;
    }

    map<string, double> getDensity(double altitude) {
        if (altitude <= 0) {
            map<string, double> values;
            values["x0"] = 0;
            values["y0"] = 1.2250000;
            values["x1"] = 1000.0;
            values["y1"] = 1.1120000;
            return values;
        }
        if (altitude > 80000.0) {
            map<string, double> values;
            values["x0"] = 70000.0;
            values["y0"] = 0.0000828;
            values["x1"] = 80000.0;
            values["y1"] = 0.0000185;
            return values;
        }

        vector<double> keys;
        for (auto it = altitudeToDensity.begin(); it != altitudeToDensity.end(); it++) {
            keys.push_back(it->first);
        }

        double x0 = getLesserValue(altitude, keys);
        double y0 = altitudeToDensity[x0];

        double x1 = getGreaterValue(altitude, keys);
        double y1 = altitudeToDensity[x1];

        map<string, double> values;
        values["x0"] = x0;
        values["y0"] = y0;
        values["x1"] = x1;
        values["y1"] = y1;

        return values;
    }

    map<string, double> getSpeedOfSound(double altitude) {
        if (altitude <= 0) {
            map<string, double> values;
            values["x0"] = 0;
            values["y0"] = 340.0;
            values["x1"] = 1000.0;
            values["y1"] = 336.0;
            return values;
        }
        if (altitude > 40000.0) {
            map<string, double> values;
            values["x0"] = 30000.0;
            values["y0"] = 305.0;
            values["x1"] = 40000.0;
            values["y1"] = 324.0;
            return values;
        }
        vector<double> keys;
        for (auto it = altitudeToSpeedOfSound.begin(); it != altitudeToSpeedOfSound.end(); it++) {
            keys.push_back(it->first);
        }

        double x0 = getLesserValue(altitude, keys);
        double y0 = altitudeToSpeedOfSound[x0];

        double x1 = getGreaterValue(altitude, keys);
        double y1 = altitudeToSpeedOfSound[x1];

        map<string, double> values;
        values["x0"] = x0;
        values["y0"] = y0;
        values["x1"] = x1;
        values["y1"] = y1;

        return values;
    }

    map<string, double> getGravity(double altitude) {
        if (altitude <= 0) {
            map<string, double> values;
            values["x0"] = 0;
            values["y0"] = 9.807;
            values["x1"] = 1000.0;
            values["y1"] = 9.804;
            return values;
        }
        if (altitude > 25000.0) {
            map<string, double> values;
            values["x0"] = 20000.0;
            values["y0"] = 9.745;
            values["x1"] = 25000.0;
            values["y1"] = 9.730;
            return values;
        }
        vector<double> keys;
        for (auto it = altitudeToGravity.begin(); it != altitudeToGravity.end(); it++) {
            keys.push_back(it->first);
        }

        double x0 = getLesserValue(altitude, keys);
        double y0 = altitudeToGravity[x0];

        double x1 = getGreaterValue(altitude, keys);
        double y1 = altitudeToGravity[x1];

        map<string, double> values;
        values["x0"] = x0;
        values["y0"] = y0;
        values["x1"] = x1;
        values["y1"] = y1;

        return values;
    }

    Tables() {
        machToDrag[0.0] = 0;
        machToDrag[0.300] = 0.1629;
        machToDrag[0.500] = 0.1659;
        machToDrag[0.700] = 0.2031;
        machToDrag[0.890] = 0.2597;
        machToDrag[0.920] = 0.3010;
        machToDrag[0.960] = 0.3287;
        machToDrag[0.980] = 0.4002;
        machToDrag[1.000] = 0.4258;
        machToDrag[1.020] = 0.4335;
        machToDrag[1.060] = 0.4483;
        machToDrag[1.240] = 0.4064;
        machToDrag[1.530] = 0.3663;
        machToDrag[1.990] = 0.2897;
        machToDrag[2.870] = 0.2297;
        machToDrag[2.890] = 0.2306;
        machToDrag[5.000] = 0.2656;

        altitudeToDensity[0.0] = 1.2250000;
        altitudeToDensity[1000.0] = 1.1120000;
        altitudeToDensity[2000.0] = 1.0070000;
        altitudeToDensity[3000.0] = 0.9093000;
        altitudeToDensity[4000.0] = 0.8194000;
        altitudeToDensity[5000.0] = 0.7364000;
        altitudeToDensity[6000.0] = 0.6601000;
        altitudeToDensity[7000.0] = 0.5900000;
        altitudeToDensity[8000.0] = 0.5258000;
        altitudeToDensity[9000.0] = 0.4671000;
        altitudeToDensity[10000.0] = 0.4135000;
        altitudeToDensity[15000.0] = 0.1948000;
        altitudeToDensity[20000.0] = 0.0889100;
        altitudeToDensity[25000.0] = 0.0400800;
        altitudeToDensity[30000.0] = 0.0184100;
        altitudeToDensity[40000.0] = 0.0039960;
        altitudeToDensity[50000.0] = 0.0010270;
        altitudeToDensity[60000.0] = 0.0003097;
        altitudeToDensity[70000.0] = 0.0000828;
        altitudeToDensity[80000.0] = 0.0000185;

        altitudeToSpeedOfSound[0.0] = 340.0;
        altitudeToSpeedOfSound[1000.0] = 336.0;
        altitudeToSpeedOfSound[2000.0] = 332.0;
        altitudeToSpeedOfSound[3000.0] = 328.0;
        altitudeToSpeedOfSound[4000.0] = 324.0;
        altitudeToSpeedOfSound[5000.0] = 320.0;
        altitudeToSpeedOfSound[6000.0] = 316.0;
        altitudeToSpeedOfSound[7000.0] = 312.0;
        altitudeToSpeedOfSound[8000.0] = 308.0;
        altitudeToSpeedOfSound[9000.0] = 303.0;
        altitudeToSpeedOfSound[10000.0] = 299.0;
        altitudeToSpeedOfSound[15000.0] = 295.0;
        altitudeToSpeedOfSound[20000.0] = 295.0;
        altitudeToSpeedOfSound[25000.0] = 295.0;
        altitudeToSpeedOfSound[30000.0] = 305.0;
        altitudeToSpeedOfSound[40000.0] = 324.0;

        altitudeToGravity[0.0] = 9.807;
        altitudeToGravity[1000.0] = 9.804;
        altitudeToGravity[2000.0] = 9.801;
        altitudeToGravity[3000.0] = 9.797;
        altitudeToGravity[4000.0] = 9.794;
        altitudeToGravity[5000.0] = 9.791;
        altitudeToGravity[6000.0] = 9.788;
        altitudeToGravity[7000.0] = 9.785;
        altitudeToGravity[8000.0] = 9.782;
        altitudeToGravity[9000.0] = 9.779;
        altitudeToGravity[10000.0] = 9.776;
        altitudeToGravity[15000.0] = 9.761;
        altitudeToGravity[20000.0] = 9.745;
        altitudeToGravity[25000.0] = 9.730;

    }
};


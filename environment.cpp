#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

struct Data {
    string city;
    double temp, humidity, pollution;
};

int main() {
    ifstream file("environment_data.csv");
    string line;
    vector<Data> data;

    getline(file, line); // Skip header
    while (getline(file, line)) {
        stringstream ss(line);
        Data d;
        getline(ss, d.city, ',');
        ss >> d.temp; ss.ignore();
        ss >> d.humidity; ss.ignore();
        ss >> d.pollution;
        data.push_back(d);
    }

    auto minT = min_element(data.begin(), data.end(), [](auto& a, auto& b){ return a.temp < b.temp; });
    auto maxT = max_element(data.begin(), data.end(), [](auto& a, auto& b){ return a.temp < b.temp; });

    auto minH = min_element(data.begin(), data.end(), [](auto& a, auto& b){ return a.humidity < b.humidity; });
    auto maxH = max_element(data.begin(), data.end(), [](auto& a, auto& b){ return a.humidity < b.humidity; });

    auto minP = min_element(data.begin(), data.end(), [](auto& a, auto& b){ return a.pollution < b.pollution; });
    auto maxP = max_element(data.begin(), data.end(), [](auto& a, auto& b){ return a.pollution < b.pollution; });

    cout << "Temp Range: " << minT->temp << " (" << minT->city << ") to " << maxT->temp << " (" << maxT->city << ")\n";
    cout << "Humidity Range: " << minH->humidity << " to " << maxH->humidity << "\n";
    cout << "Pollution Range: " << minP->pollution << " to " << maxP->pollution << "\n\n";

    double avgT = accumulate(data.begin(), data.end(), 0.0, [](double sum, Data& d){ return sum + d.temp; }) / data.size();
    double avgH = accumulate(data.begin(), data.end(), 0.0, [](double sum, Data& d){ return sum + d.humidity; }) / data.size();
    double avgP = accumulate(data.begin(), data.end(), 0.0, [](double sum, Data& d){ return sum + d.pollution; }) / data.size();

    cout << "Average Temp: " << avgT << ", Humidity: " << avgH << ", Pollution: " << avgP << "\n\n";

    sort(data.begin(), data.end(), [](auto& a, auto& b){ return a.temp < b.temp; });
    cout << "Cities by Temp:\n";
    for (auto& d : data) cout << d.city << ": " << d.temp << "\n";

    cout << "\nPollution Health Check:\n";
    for (auto& d : data) {
        cout << d.city << ": " << (d.pollution > 100 ? "Unhealthy" : "Safe") << "\n";
    }

    return 0;
}

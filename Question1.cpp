#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>

using namespace std;

const int MAX_YEARS = 30;
const int purchaseYear = 2001;
const double costPrice = 50 * 100000;

void readCSV(const string& filename, double growthRates[], double inflationRates[], int years[], int& numYears) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file." << endl;
        exit(1);
    }
    
    string line;
    getline(file, line); // Skip the header line

    numYears = 0;
    while (getline(file, line)) {
        size_t pos = 0;
        string token;
        
        // Extract year
        pos = line.find(',');
        token = line.substr(0, pos);
        years[numYears] = stoi(token.substr(6, 4));
        line.erase(0, pos + 1);
        
        // Extract growth rate
        pos = line.find(',');
        token = line.substr(0, pos);
        growthRates[numYears] = stod(token);
        line.erase(0, pos + 1);
        
        // Extract inflation rate
        inflationRates[numYears] = stod(line);

        numYears++;
        if (numYears >= MAX_YEARS) {
            cerr << "Too many years in the CSV file." << endl;
            exit(1);
        }
    }

    file.close();
}

double calculateSellingPrice(double costPrice, int endYear, const double growthRates[], const double inflationRates[], const int years[], int numYears, double& ltcg) {
    double adjustedCostPrice = costPrice;
    int startIndex = 0;
    int endIndex = 0;
    
    for (int i = 0; i < numYears; ++i) {
        if (years[i] == purchaseYear) startIndex = i;
        if (years[i] == endYear) {
            endIndex = i;
            break;
        }
    }
    
    for (int i = startIndex; i < endIndex; ++i) {
        double growth = growthRates[i];
        double inflation = inflationRates[i];
        adjustedCostPrice *= (1 + (growth - inflation) / 100);
    }
    
    ltcg = adjustedCostPrice - costPrice;
    return adjustedCostPrice;
}

int main() {
    int sellingYear;
    double growthRates[MAX_YEARS], inflationRates[MAX_YEARS];
    int years[MAX_YEARS];
    int numYears;

    cout << "Enter the year of selling: ";
    cin >> sellingYear;

    readCSV("price-inflation.csv", growthRates, inflationRates, years, numYears);

    if (sellingYear < years[0] || sellingYear > years[numYears - 1]) {
        cerr << "Year out of range" << endl;
        return 1;
    }

    double ltcg;
    double sellingPrice = calculateSellingPrice(costPrice, sellingYear, growthRates, inflationRates, years, numYears, ltcg);
    
    // Calculate tax based on LTCG
    double tax = max(0.0, ltcg * 0.20);  // Ensure tax is non-negative

    cout << fixed << setprecision(2);
    cout << "Estimated Selling Price: Rs " << sellingPrice << endl;
    cout << "Long-term Capital Gains (LTCG): Rs " << ltcg << endl;
    cout << "Long-term Capital Gains Tax (LTCG) to be paid: Rs " << tax << endl;

    return 0;
}
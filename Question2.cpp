#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>

using namespace std;

const int MAX_YEARS = 30;
double COST_PRICE;

void readCSV(const string &filename, double growthRates[], double inflationRates[], int years[], int &numYears)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "Error opening file." << endl;
        exit(1);
    }

    string line;
    getline(file, line); // Skip header

    numYears = 0;
    while (getline(file, line))
    {
        size_t pos = 0;
        string token;

        pos = line.find(',');
        token = line.substr(0, pos);
        years[numYears] = stoi(token.substr(6, 4));
        line.erase(0, pos + 1);

        pos = line.find(',');
        token = line.substr(0, pos);
        growthRates[numYears] = stod(token);
        line.erase(0, pos + 1);

        inflationRates[numYears] = stod(line);

        numYears++;
        if (numYears >= MAX_YEARS)
        {
            cerr << "Too many years in the CSV file." << endl;
            exit(1);
        }
    }

    file.close();
}

double calculateSellingPriceOld(double costPrice, int startYear, int endYear, const double growthRates[], const double inflationRates[], const int years[], int numYears, double &ltcg)
{
    double adjustedCostPrice = costPrice;
    int startIndex = 0;
    int endIndex = 0;

    for (int i = 0; i < numYears; ++i)
    {
        if (years[i] == startYear)
            startIndex = i;
        if (years[i] == endYear)
        {
            endIndex = i;
            break;
        }
    }

    for (int i = startIndex + 1; i < endIndex; ++i)
    {
        double growth = growthRates[i];
        double inflation = inflationRates[i];
        adjustedCostPrice *= (1 + (growth - inflation) / 100);
    }

    ltcg = adjustedCostPrice - costPrice;
    return adjustedCostPrice;
}

double calculateSellingPriceNew(double costPrice, int startYear, int endYear, const double growthRates[], const int years[], int numYears, double &ltcg)
{
    double adjustedCostPrice = costPrice;
    int startIndex = 0;
    int endIndex = 0;

    for (int i = 0; i < numYears; ++i)
    {
        if (years[i] == startYear)
            startIndex = i;
        if (years[i] == endYear)
        {
            endIndex = i;
            break;
        }
    }

    for (int i = startIndex + 1; i < endIndex; ++i)
    {
        double growth = growthRates[i];
        adjustedCostPrice *= (1 + growth / 100);
    }

    ltcg = adjustedCostPrice - costPrice;
    return adjustedCostPrice;
}

int main()
{
    int purchaseYear, sellingYear;
    double growthRates[MAX_YEARS], inflationRates[MAX_YEARS];
    int years[MAX_YEARS];
    int numYears;

    cout << "Enter the cost price: ";
    cin >> COST_PRICE;
    cout << "Enter the purchase year: ";
    cin >> purchaseYear;
    cout << "Enter the selling year: ";
    cin >> sellingYear;

    readCSV("price-inflation.csv", growthRates, inflationRates, years, numYears);

    if (sellingYear < years[0] || sellingYear > years[numYears - 1])
    {
        cerr << "Year out of range" << endl;
        return 1;
    }

    double ltcgOld, ltcgNew;

    // Calculate old scheme (with inflation adjustment and 20% LTCG)
    double sellingPriceOld = calculateSellingPriceOld(COST_PRICE, purchaseYear, sellingYear, growthRates, inflationRates, years, numYears, ltcgOld);
    double taxOld = max(0.0, ltcgOld * 0.20); // 20% tax rate

    // Calculate new scheme (no inflation adjustment and 12.5% LTCG)
    double sellingPriceNew = calculateSellingPriceNew(COST_PRICE, purchaseYear, sellingYear, growthRates, years, numYears, ltcgNew);
    double taxNew = max(0.0, ltcgNew * 0.125); // 12.5% tax rate

    // Output the results
    cout << fixed << setprecision(2);
    cout << "Old Scheme (with inflation adjustment):" << endl;
    cout << "  Estimated Selling Price: Rs " << sellingPriceOld << endl;
    cout << "  Long-term Capital Gains Tax (LTCG) to be paid: Rs " << taxOld << endl;

    cout << "New Scheme (without inflation adjustment):" << endl;
    cout << "  Estimated Selling Price: Rs " << sellingPriceNew << endl;
    cout << "  Long-term Capital Gains Tax (LTCG) to be paid: Rs " << taxNew << endl;

    // Compare the two
    cout << "Difference in tax (Old vs New): Rs " << abs(taxOld - taxNew) << endl;

    return 0;
}

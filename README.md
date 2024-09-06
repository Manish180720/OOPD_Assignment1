# 1. LTCG Calculator

This is a basic program that helps you calculate the selling price of an asset and the Long-term Capital Gains (LTCG) tax based on growth and inflation rates.

## How It Works

1. The program asks for:
    - **Cost price** of the asset.
    - **Purchase year** (when you bought it).
    - **Selling year** (when you plan to sell it).

2. It reads growth and inflation rates from a CSV file named `price-inflation.csv`.

3. It calculates:
    - The estimated selling price.
    - The Long-term Capital Gains tax (20% of the gain).

# Steps to Use

1. Download or clone this project.
2. Create a file called `price-inflation.csv` with data like this:

    ```csv
    Year,Growth Rate,Inflation Rate
    FY2011,7.5,6.0
    FY2012,8.0,5.5
    FY2013,6.5,4.8
    ```

3. Run the program, and enter:
    - **Cost price** (e.g., 5000000)
    - **Purchase year** (e.g., 2010)
    - **Selling year** (e.g., 2020)

4. The program will show:
    - The estimated selling price.
    - The tax you need to pay.

## Example Output

```bash
# Enter the cost price: 5000000
# Enter the purchase year: 2010
# Enter the selling year: 2020
# Estimated Selling Price: Rs 5077006.00
# Long-term Capital Gains Tax (LTCG) to be paid: Rs 15401.00



# LTCG Tax Calculator

This program calculates Long-Term Capital Gains (LTCG) tax based on inflation-adjusted selling price using historical data from a CSV file.

## Features

- **Inflation Adjustment**: Computes selling price adjusted for inflation.
- **LTCG Tax Calculation**: Calculates tax at a rate of 12.5% of the gain.

## Requirements

- A CSV file named `price-inflation.csv` with the following format:


## How to Use

1. **Prepare Data File**: Ensure `price-inflation.csv` is located in the same directory as the executable.

2. **Compile the Code**: 
 ```sh
 g++ -o LTCGCalculator LTCGCalculator.cpp


# Enter the purchase price (Rs): 100000
# Enter the year of purchase: 2010
# Enter the year of selling: 2024
# Final selling price (inflation-adjusted): Rs 250000.00
# LTCG Tax (12.5%): Rs 18750.00

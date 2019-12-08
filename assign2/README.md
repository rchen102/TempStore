# CS435: Assignment 2

## Basic Information
Name: Renze Chen  
B-Number: B00767193  

## File Docs
### Data
1. `raw.mat`: store `[527 x 38]` raw data from the `water-treatment.data`

2. `data.mat`: store `[527 x 38]` data after preprocessing raw data

### Source Code
1. `data_preprocess.m`: for filling up missing and normalization
 

## Question1
### Handle missing value
For each attribute, use the mean value of the attribute to fill up the missing value

### Normalization
For each attribute, do the normalization separately. Rescale(map) the data of each attribute to range `[0,1]`

Assume for attribute `i`(i=1,2,...,38), the value of instance is `Vij`(j=1,2,...,527)  
Normalize(`Vij`) = (`Vij`-`min_i`) / (`max_i`-`min_i`), while
- `min_i` = Min(`Vij`) (j=1,2,...,527)
- `max_i` = Max(`Vij`) (j=1,2,...,527)

## Question2


## Question3

## Question4

## Question5



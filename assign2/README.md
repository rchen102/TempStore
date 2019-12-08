# CS435: Assignment 2
## Basic Information
Name: Renze Chen  
B-Number: B00767193  

## Environment
MATLAB R2016a

## How to run code
To run the code, ensure the version of MATLAB is no less than R2016a.

Please set the workspace of MATLAB to directory `/matlab_code`

No need to compile any code, follow the instruction below to run code

1. __Instruction to fill missing and normalization__
   Open the script `data_preprocess.m`, click `run` in menu or press `F5`

2. __Instruction to apply PCA__
   Open the script `my_pca.m`, click `run` in menu or press `F5`

3. __Instruction to apply kmeans to data and data after PCA__
   Open the script `main.m`, click `run` in menu or press `F5`

## File Explanation
### Data
1. `raw.mat`: `[527 x 38]` raw data reading from the `water-treatment.data`
2. `data.mat`: `[527 x 38]` data after preprocessing raw data(fill missing and normalization)
2. `r_data.mat`: `[527 x 11]` data after applying PCA to dataset

## Output file
1. `result1.txt`: clustering result for `Question3`
2. `result2.txt`: clustering result for `Question4`

## Figure
1. `/figure/Fig1 Before PCA.png`: plot `k` against `SSE`(Before PCA) for elbow method to decide the k value for kmeans
2. `/figure/Fig1 After PCA.png`: plot `k` against `SSE`(After PCA) for elbow method to decide the k value for kmeans

### Source Code
1. `data_preprocess.m`: script code for filling up missing and normalization for dataset
2. `my_pca.m`: script code for applying PCA to dataset
3. `my_kmeans.m`: function code for modified kmeans
4. `main.m`: script code for applying modified kmeans to data and data after PCA, write clustering results to ASCLL file
 





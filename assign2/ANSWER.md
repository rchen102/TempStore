# CS435: Assignment 2
## Basic Information
Name: Renze Chen  
B-Number: B00767193  

## Question1
### Handle missing
For each attribute, use the mean value of the attribute to fill up the missing values of this attribute

### Normalization
For each attribute, do the normalization separately. Rescale(map) the data of each attribute to range `[0,1]`

Assume for attribute `i`(i=1,2,...,38), the value of instance is `Vij`(j=1,2,...,527)  
Normalize(`Vij`) = (`Vij`-`min_i`) / (`max_i`-`min_i`), while
- `min_i` = Min(`Vij`) (j=1,2,...,527)
- `max_i` = Max(`Vij`) (j=1,2,...,527)

## Question2
Utilize the elbow method to decide the k value for kmeans

1. Assume the size of dataset is `N` (i.e., there are `N` data items), choose the range of `K` values to be `from 1 to sqrt(N)` (`[1, sqrt(N)]`)

2. For each value of `K` in the range above, call the kmeans

3. Record the `SSE`(Sum of the Squared Errors) for each value `K`. `SSE` is defined as the sum of distance between member of each cluster and its centroid 

4. Plot the figure that `K` against the `SSE`. Refer to `/figure` folder for specific fig

5. We can find, `SSE` decreases as `K` increases. At first, the `SSE` will decrease fast, but at some point, the decrease will be small, causing an angle in the figure. We consider the point as elbow point. And the number of cluster is chosen at the point.

## Question3
After applying the modified kmeans, from `figure/Fig1 Before PCA.png`, we can find the elbow point is `k=7`, so divide the dataset into `7` clusters:

Value    Count   Percent
  1       21      3.98%
  2        8      1.52%
  3      123     23.34%
  4       36      6.83%
  5      153     29.03%
  6       60     11.39%
  7      126     23.91%

The specific clustering output has been writen into file `result1.txt`

## Question4
After applying `PCA`, the dimensionality of dataset was reduced from `38` to `11`, while the rest components can account for `85%` of the variance

After applying the modified kmeans, from `figure/Fig1 After PCA.png`, we can find the elbow point is `k=4`, so divide the dataset into `4` clusters:

Value    Count   Percent
  1      173     32.83%
  2       77     14.61%
  3      197     37.38%
  4       80     15.18%

The specific clustering output has been writen into file `result2.txt`

## Question5
### Comparison
After applying PCA, the totoal number of clusters that the dataset is divided decreases from `7` to `4`

### Reason
Because PCA can help reduce the dimensionality of dataset. And dimensionality reduction can help eliminate irrelevant features and reduce noise. Since kmeans is sensitive to noisy data and outliers, so after PCA, kmeans can get a better clustering result(i.e., # of cluster will decrease, because some noise data can become a separate cluster)
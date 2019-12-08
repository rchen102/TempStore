clear, clc;
load('data.mat');
load('r_data.mat');

%% apply modified kmeans to data
figure
my_kmeans(data);
title('Before PCA');

figure
my_kmeans(r_data);
title('After PCA');

%% From the figure, use elbow method
%  Decide the k to be 7 before applying PCA
Idx1 = kmeans(data,7);

%  Decide the k to be 4 after applying PCA
Idx2 = kmeans(r_data,4);

res = [1:527]';
res1 = [res, Idx1];
res2 = [res, Idx2];

dlmwrite('result1.txt',res1, ' ');
dlmwrite('result2.txt',res2, ' ');

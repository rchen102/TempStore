clear, clc;
load('data.mat');

%% PCA
[COEFF, SCORE, LATENT] = pca(data);

%% Figure out components account for 85% of the variance
ratio = cumsum(LATENT)./sum(LATENT);
idx = find(ratio > 0.85);
num = idx(1);

%% Reduce the dimensionality
% r_data.mat stores the data after PCA
r_data = SCORE(:, 1:num);
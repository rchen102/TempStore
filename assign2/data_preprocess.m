clear, clc;
load('raw.mat');

%% Fill missing value 
mean_v = nanmean(raw);
for i = 1 : length(mean_v)
    idx = isnan(raw(:,i));
    raw(idx,i) = mean_v(i);
end
    
%% Normalize data
raw = raw';
raw = mapminmax(raw, 0, 1);
raw = raw';

%% data.mat stores the data after preprocessing
data = raw;
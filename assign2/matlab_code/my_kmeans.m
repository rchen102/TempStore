function [] = my_kmeans( data )
% run modified kmeans on data
% plot k against SSE, while k = [1 : sqrt(size of dataset)] 
% then user could use elbow method to find the elbow point

n = size(data, 1);
K = sqrt(n);
res = []; % store SSE for k in range[1,K]

for k = 1 : K
    [Idx,C,sumD] = kmeans(data,k);
    e = sum(sumD);
    res = [res,e];
end
plot(res);
set(gca,'XTick',0:1:K);
end


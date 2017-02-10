%save data.mat data

clc
clear all
close all
load data
image = zeros(10000,10000);
xdiff = 2071;
ydiff = 33271;
data = double(data);
add_x = 80000;
add_y = 30800;
for i = 1 : size(data,1)
    x_pos = data(i,1) - xdiff;
    y_pos = data(i,2) - ydiff;
    if x_pos >= 80000 & x_pos < 90000 & y_pos >= 30800 & y_pos < 40800
        image(y_pos - add_y, x_pos - add_x) = 1;
    end
    disp(i);
end
%image = flipud(image);
imshow(image);
% display('all done');
% imwrite(image,'image.png','png');
% figure;
% 
 
% figure
% BW1 = edge(image,'Canny');
% imshow(BW1)

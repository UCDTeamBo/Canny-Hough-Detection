function Test_Hough()

M = csvread('C:\Users\Lindsey\Documents\GitHub\Canny-Hough-Detection\HoughTransform\HoughTransform\Hough_Line_Points.csv');
T = csvread('C:\Users\Lindsey\Documents\GitHub\Canny-Hough-Detection\HoughTransform\HoughTransform\Copy_Image.csv');
I = imread('C:\Users\Lindsey\Documents\GitHub\Canny-Hough-Detection\HoughTransform\HoughTransform\out_MATLAB.bmp');
length = size(M);
length_2 = size(T);
disp(length_2);
TEST = I;
for i=1:4:length(2)-4;
    %disp(i);
    %I=bitmapplot([M(i+2),M(i+3)],[M(i),M(i+1)],I,struct('LineWidth',5,'Color',[1 0 0 1]));
end
count = 0;
k = 0;
for k=1:1:length_2(1)
    x = T(k,1);
    y = T(k,2);
    T_1 = [x+1,x+1];
    T_2 = [2560-y,2560-y];
    %disp(T_1);
    %disp(T_2);
    TEST=bitmapplot(T_2,T_1,TEST,struct('LineWidth',5,'Color',[1 0 0 1]));
    if (count > 1000)
        break;
    end
    count = count + 1;
    disp(k);
end
%TEST=bitmapplot([6,6],[0,1920],TEST,struct('LineWidth',5,'Color',[1 0 0 1]));
imshow(TEST);
%disp(M);

end
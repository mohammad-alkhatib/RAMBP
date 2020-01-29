% Binary Pattern
% Author: Mohammad Alkhatib 
% email: mohammad.alkhatib@etu.univ-orleans.fr

function [BP] = Binary_pattern(Threshold,Center_Value,i,j,x)

% The module starts by finding the neighborhood patches and compare between
% the central pixel and these patches values

    pixel7 = Threshold(i-x,j-x) > Center_Value;

    pixel6 = Threshold(i-x, j) > Center_Value;

    pixel5 = Threshold(i-x, j+x) > Center_Value;

    pixel4 = Threshold(i, j+x) > Center_Value;

    pixel3 = Threshold(i+x, j+x) > Center_Value;

    pixel2 = Threshold(i+x, j) > Center_Value;

    pixel1 = Threshold(i+x, j-x) > Center_Value;

    pixel0 = Threshold(i, j-x) > Center_Value;

% computing the binary pattern
BP = uint8(...
    pixel7 * 2^7 + pixel6 * 2^6 + ...
    pixel5 * 2^5 + pixel4 * 2^4 + ...
    pixel3 * 2^3 + pixel2 * 2^2 + ...
    pixel1 * 2 + pixel0);
            
end
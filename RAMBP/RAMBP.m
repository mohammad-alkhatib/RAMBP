% Version 0.1 
% Author: Mohammad Alkhatib 
% email: mohammad.alkhatib@etu.univ-orleans.fr
% % REFERENCE: M. Alkhatib, A. Hafiane - arXiv preprint arXiv:1805.05732, 2018 - arxiv.org

function Result = RAMBP(varargin) 
%  Robust Adaptive Median Binary Pattern
%  Result = RAMBP(I,MODE) 
%  MODE : 
%        0  to get RAMBP image
%       'h' or 'hist'  to get a histogram of RAMBP 
%       'nh'           to get a normalized histogram
%  

error(nargchk(1,2,nargin));

Input_image=varargin{1}; 
Input_image_double=double(Input_image);

if nargin==1
    mode='h';
else
    mode=varargin{2};
end

if size(Input_image_double,3)>1
    grayImage=rgb2gray(Input_image_double);
else
    grayImage=Input_image_double;
end


% Replicate padding around the image
I=padarray(grayImage,[15 15],'replicate');

% Noisy pixels detection, returns a classified binary image 
% C = 0 corrupted pixel
% C = 1 uncorrupted pixel

C = Pixel_classification (I);

[m,n] = size(I);

% The max window size for threshold value 
W_m = 2;

% The distance between the centeral pixel and each patch center
R = 7;

% Threshold value, returns a threshold value for each pixel
[Threshold] = Threshold_value_all(I,C,W_m);

% Check if the center value is corrupted or not
Center_Values = I.*C;

for i = 16:m-15
    for j = 16:n-15
        % If the ceter value is uncorrupted the threshold value equal the
        % central pixel
        % Else its equal to the computed threshold value
        if Center_Values (i,j) ~= 0 
           Center_Value = Center_Values (i,j);
        else
           Center_Value = Threshold (i,j); 
        end
        % Binary pattern, returns the binary image
        BinaryPatternImage(i,j) = Binary_pattern(Threshold,Center_Value,i,j,R);

    end
end


% Remove the padding and get the binary pattern image
RAMBP_image = uint8(BinaryPatternImage(16:m-15,16:n-15));

% Finding the histogram
[RAMBP_histogram, GLs] = imhist(uint8(RAMBP_image));

% Normalized histogram
RAMBP_normalized_histogram = RAMBP_histogram/sum(RAMBP_histogram);


% Return the desired result
if mode ==0
    Result = RAMBP_image;
elseif mode =='h'
    Result = RAMBP_histogram;
else
    Result = RAMBP_normalized_histogram;
end


end

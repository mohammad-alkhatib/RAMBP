% Threshold value
% Author: Mohammad Alkhatib 
% email: mohammad.alkhatib@etu.univ-orleans.fr

function [Th] = Threshold_value_all(J,N,Max_w_s)
% Returns the threshlod values of each pixel

% initialize the threshold image
Th = zeros(size(J));
[m,n] = size(J);

for i = 16: m-15
    for j = 16: n-15
        % min window size 3x3
        Min_w_s=1;

        % Get the window values
        Wind_cur = N(i-Min_w_s:i+Min_w_s,j-Min_w_s:j+Min_w_s);
        % Number of the corrupted pixel
        Unoisy_number = sum(Wind_cur(:));
        Wind_size= Min_w_s*2+1;

        % If the number of the uncorrupted pixel is more than the corrupted ones, break. 
        % Otherwise, the window will be enlarged by 1 pixel in all directions until 
        % reaching the pre-define maximum window size 
        while Unoisy_number < (Wind_size/2) 
            if (Min_w_s<Max_w_s)
                Min_w_s=Min_w_s+1;
                Wind_cur = N(i-Min_w_s:i+Min_w_s,j-Min_w_s:j+Min_w_s);
                Unoisy_number = sum(Wind_cur(:));
                Wind_size= Min_w_s*2+1;
            else
               break;
            end
        end

        % the threshold value is equal to the median of the uncorrupted pixels inside 
        % the acceepted window
        J_cur = J(i-Min_w_s:i+Min_w_s,j-Min_w_s:j+Min_w_s);
        J_curr = J_cur(:);
        Wind_cur_val= J_curr(Wind_cur(:)==1);
        Th(i,j) = median(Wind_cur_val(:));
    end
end
end
% Noisy pixels detection
% Author: Mohammad Alkhatib 
% email: mohammad.alkhatib@etu.univ-orleans.fr

function [N] = Pixel_classification (J1)

% Returns the classified binary image of 
% N = 0 corrupted pixel
% N = 1 uncorrupted pixel

% initialize the binary image
[rows,cols]=size(J1);
N=ones(rows,cols);

% start the classification step
for i=11:rows-10
    for j=11:cols-10
        
        % get the central pixel
        center_value=J1(i,j);
        
        % step one : Identify the window 21x21
        imPatch = J1((i-10):(i+10), (j-10):(j+10));
        
        % step two : Convert the matrix to 1-D vector
        imVec = imPatch(:);
        
        % step three : Sort the vector ascending
        V_0 = sort(imVec);
        
        % step five: compute the difference vector and both 
        % intervals [1:med] and (med:end]

        for k=1:(size(V_0,1)-1)
        D_v(k)=abs(V_0(k)-V_0(k+1));
        end
        
        first_interval=D_v(1:ceil(size(V_0,1)/2)-1);
        index1 = find(first_interval == max(first_interval), 1);
        
        second_interval=D_v(ceil(size(V_0,1)/2):end);
        index2 = find(second_interval == max(second_interval), 1);
        
        % step six: find the pixels which correspond to the maximum
        % differences in both intervals
        
        b1=V_0(index1);
        b2=V_0(index2-1+ceil(size(V_0,1)/2));
                
        % step seven: classify the center pixel into three clusters if it
        % belongs to the middle interval, it considers uncorrupted pixel and
        % equal to 1 in the classified binary image
        if center_value <= b2 && center_value > b1
                % M_cluster='Uncorrupted';
        else
            
            % Otherwise, a 3x3 window is imposed around the central pixels
            % and the steps from 2-6 are repeated
            imPatch_new = J1((i-1):(i+1), (j-1):(j+1));
            imVec_new = imPatch_new(:);
            V_0_new = sort(imVec_new);
            
            for k_new=1:(size(V_0_new,1)-1)
            D_v_new(k_new)=abs(V_0_new(k_new)-V_0_new(k_new+1));
            end

            first_interval_new=D_v_new(1:ceil(size(V_0_new,1)/2)-1);
            index1_new = find(first_interval_new == max(first_interval_new), 1);

            second_interval_new=D_v_new(ceil(size(V_0_new,1)/2):end);
            index2_new = find(second_interval_new == max(second_interval_new), 1);
            
            b1_new =V_0_new(index1_new);
            b2_new =V_0_new(index2_new-1+ceil(size(V_0_new,1)/2));
            
            % if the pixel belongs to the middle interval, it considers 
            % uncorrupted pixel and equal to 1 in the classified binary 
            % image, else it considers corrupted one and equal to zero 
            % in the classified image 
            if center_value <= b2_new && center_value > b1_new
                % M_cluster='Uncorrupted';
            else
                % M_cluster='corrupted';
            N(i,j)=0;
            end
        end
        
    end
end

end


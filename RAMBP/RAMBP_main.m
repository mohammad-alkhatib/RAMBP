% Author: Mohammad Alkhatib 
% email: mohammad.alkhatib@etu.univ-orleans.fr
% This function made for treating RAMBP on images folder

function RAMBP_main(dirname,infile, outfile)
 
% open the infile
infid = fopen(infile, 'r');
imgNumber=fscanf(infid,'%d',1);
nClass=fscanf(infid,'%d',1);

% create and open the outfile
[io name1]=fileparts(outfile);
outfile8L1       = sprintf('%s%s%d%s',name1,'.txt');
outfid8_L1        = fopen(outfile8L1, 'w');

% Give image directory and extension
imExt = 'png';

% get all files in the directory
filearray = dir([dirname filesep '*.' imExt]);

% get the number of images
NumImages = size(filearray,1);

% save each image RAMBP hist
image_RAMBP = {};

tic;
parfor(ii=1:NumImages)
    
    % read the images
    imgname1 = [dirname filesep filearray(ii).name];
    imgname = filearray(ii).name;
    grayImage = imread(imgname1);
    if size(grayImage,3) > 1
    	grayImage = rgb2gray(grayImage);
    else
        grayImage=grayImage;
    end
    % print the processed image number and name
    disp(sprintf('%d: %s',ii,imgname))
    
    % get RAMBP normalize hisrtogram
    h11 = RAMBP(grayImage,'nh')

    % save the results
    image_RAMBP{ii} = h11;
    
end
processed_time = toc;

% save to a file
for ii= 1:NumImages
    imgname = fscanf(infid,'%s',1);
    cl      = fscanf(infid,'%d',1);
    [pathstr, name] = fileparts(imgname) ;
    imgname = strcat(name,'.bmp');

    if ii == 1    
      fprintf(outfid8_L1,'%d\n%d\n%d 1', NumImages, nClass, 256);
    end
     
      
      fprintf(outfid8_L1,'\n%s', imgname); fprintf(outfid8_L1,' %d', cl); fprintf(outfid8_L1,' %f', image_RAMBP{ii});        
end

% close the files
fclose(infid);
fclose(outfid8_L1); 

% display the process time
disp(sprintf('Average time per image: %f sec',processed_time/NumImages))

end


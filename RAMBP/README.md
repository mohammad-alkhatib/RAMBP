# RAMBP code (MATLAB)

Matlab implementation of RAMBP.

# Usage

For using the RAMBP with image:<br/>
RAMBP_results = RAMBP(Image,MODE) <br/>
Where MODE is: 
* 0  to get RAMBP image
* 'h' or 'hist'  to get a histogram of RAMBP 
* 'nh'           to get a normalized histogram
       

For using the RAMBP with folder contains many classes of textures:<br/>
RAMBP_main(dirname,infile, outfile)<br/>
Where :
* dirname is the folder directory
* outfile to generate a txt file where are the results will be saved.
* infile is a txt file contains:
  * number of images
  * number of classes
  * first_image_name first_image_class
  * second_image_name second_image_class
  * .....        
  * last_image_name last_image_class
       

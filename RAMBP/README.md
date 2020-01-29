# RAMBP code (MATLAB)

Matlab implementation of RAMBP.

# Usage

For using the RAMBP with an image:
* RAMBP_results = RAMBP(Image,MODE)
* Where MODE is: 
  * 0  to get RAMBP image
  * 'h' or 'hist'  to get a histogram of RAMBP 
  * 'nh'           to get a normalized histogram
       
       
<br/>
<br/>
For using the RAMBP with a folder that contains many classes of textures:
* RAMBP_main(dirname,infile, outfile)<br/>
* Where :
  * dirname is the folder directory
  * outfile to generate a txt file where are the results will be saved.
  * infile is a txt file contains:
    * number of images
    * number of classes
    * first_image_name first_image_class
    * second_image_name second_image_class
    * .....        
    * last_image_name last_image_class
       

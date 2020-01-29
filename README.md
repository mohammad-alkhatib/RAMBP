# RAMBP
Matlab implementation of the Robust Adaptive Median Binary Pattern (RAMBP) texture descriptor

Texture is an important characteristic for different computer vision tasks and applications. Local binary pattern (LBP) is considered one of the most efficient texture descriptors yet. However, LBP has some notable limitations, in particular its sensitivity to noise. In this respiratory, we introduce a novel texture descriptor, robust adaptive median binary pattern (RAMBP). RAMBP is based on a process involving classification of noisy pixels, adaptive analysis window, scale analysis, and a comparison of image medians. TRAMBP handles images with highly noisy textures and increases the discriminative properties by capturing microstructure and macrostructure texture information.

# Usage
1- RAMBP code (MATLAB)<br/>
2- KNN code (C++) to evaluate the descriptor.<br/>


# Publication
All details about RAMBP descriptor are described in the reference paper:<br/>
https://ieeexplore.ieee.org/abstract/document/8718516<br/>

Please cite the above publication if you use the code or compare with the RAMBP descriptor in your work. Bibtex entry:<br/>
@article{alkhatib2019robust,<br/>
    title={Robust Adaptive Median Binary Pattern for noisy texture classification and retrieval},<br/>
    author={Alkhatib, Mohammad and Hafiane, Adel},<br/>
    journal={IEEE Transactions on Image Processing},<br/>
    volume={28},<br/>
    number={11},<br/>
    pages={5407--5418},<br/>
    year={2019},<br/>
    publisher={IEEE}<br/>
}

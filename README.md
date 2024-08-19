# About
This is a software renderer written in C, made with SDL2. 
It supports Z-buffering, backface culling, and frustum culling.
I will note the Z-buffering at this point in time is a tad wonky. Also there is no texture support yet. 
![image](https://github.com/user-attachments/assets/8a0fdc8f-9077-4c2e-808d-a1ea4e49439e)
There is some pseudo-lighting effects that I thought were pretty cool though! :D All I did though was just
make farther objects and objects which have normals that are rotated further away from the camera make their
colors darker. Nothing fancy. 

# Building
Only dependency other than standard libraries is SDL2. Once you have that installed, just run the build script in the source directory. 
Windows users, you are on your own for now.


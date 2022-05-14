# RayTracingPrac
This is a ray tracer program that I, Derek Chen, wrote. This program was rewritten in 2022 after I finished my first major project Unimap.

# Initial Release
This is the initial release and some features it had.
## Anti aliasing
This is the image rendered at 1080P of two sphere with 0 anti aliasing.
![twoSpheresNoAAShowNormalVec1080P](https://user-images.githubusercontent.com/80089456/168451084-16a09941-0245-45b5-a6a0-d8463b041ff9.png)

This is the image rendered at 1080P of two sphere with 100 ray anti-aliasing.
![twoSpheresAntialiasingShowNormalVec](https://user-images.githubusercontent.com/80089456/168451083-dfb72136-33cd-46f8-b670-0f27e8b68282.png)

Close up difference comparison: 

![image](https://user-images.githubusercontent.com/80089456/168451139-4c1abdeb-63b6-4c12-9544-874f06c57933.png) ![image](https://user-images.githubusercontent.com/80089456/168451140-abf7c070-52ab-40c5-82d4-0c73b661a718.png)

The anti aliasing is done by emitting multiple dispersed rays into different directions from the same origin and then summing them up. The performance liability was moderate: runtime 52s

# May 14 Update
This update added multi-threading support to renderer, restrctured code, and changed the image output logic. Now the same operation as before, which had a run time of 52 seconds, is not 5.42 seconds.

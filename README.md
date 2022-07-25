# 42-miniRT

<img width="1498" alt="42-logo" src="https://user-images.githubusercontent.com/56789534/173826141-045ce31b-b8be-4065-b711-4e385cb72ef6.png">

This 42 project is an introduction to the beautiful world of Raytracing. 
It is one of the group projects in the 42 core curriculum. <br>
Done by: [hepple42](https://github.com/hepple42) & [tjensen42](https://github.com/tjensen42) 

Working on this project, we have noticed more and more interesting optical effects in everyday life and were constantly thinking about possible implementation in our RayTracer. Once the basic principle was implemented, it was fun to add more and more objects and functionalities. We were especially excited about implementing relatively fundamental physical laws in code.

An excellent source on raytracing which helped us a lot is [Ray Tracing in One Weekend series of books](https://raytracing.github.io/) by Peter Shirley. It is a really detailed step-by-step guide for implementing a path-tracer in C++.

<br>

## How to use it

The only supported and tested operating systems are ```macOS``` and ```Ubuntu 20.04```.

For ```Ubuntu``` it is necessary to install the GLFW library first:
```
sudo apt-get update && \
sudo apt-get install libglfw3 && \
sudo apt-get install libglfw3-dev
```

<b>Compile and run miniRT in 3 simple steps:</b>
1. ```git clone https://github.com/tjensen42/42-miniRT miniRT```
2. ```cd miniRT && make```
3. ```./miniRT scenes/template.rt```

<br>

## Scenes

<b>Example: [Template](scenes/template.rt)</b>

| Identifier  | Description | Identifier    | Description
| :---         | :---         | :---         | :---         |
| ```R```  | Resolution | ```ls```  | Light sphere |
| ```S```  | Sampling specifications |```ld```  | Light disc |
| ```B```  | Background |```lr```  | Light rectangle |
| ```A```  | Ambient light |```tx```  | Texture |
| ```C```  | Camera |```pl```  | Plane |
|   |   | ```sp```  | Sphere |
|   |   | ```cy```  | Cylinder |
|   |   | ```tb```  | Tube |
|   |   | ```di```  | Disc |
|   |   | ```rt```  | Rectangle |
|   |   | ```cu```  | Cuboid |

## Samples
<img width="2672" alt="Screen Shot 2022-05-27 at 12 25 43 PM" src="https://user-images.githubusercontent.com/56789534/180815692-0fa071c2-1b2b-44e5-a3d9-6baf9aab7e5e.png">
<img width="2628" alt="777" src="https://user-images.githubusercontent.com/56789534/180815726-fefe9787-4059-431f-a05d-43e2bc5220fd.png">
<img width="2628" alt="135" src="https://user-images.githubusercontent.com/56789534/180815864-a63f059a-2897-4294-9042-de597fa87d11.png">
<img width="2560" alt="6000" src="https://user-images.githubusercontent.com/56789534/180815911-c11b4893-e891-4706-a0c9-bbb166b63625.png](https://user-images.githubusercontent.com/56789534/180816221-ed3e7391-d8e4-4e61-a4cb-fe73ed5923d1.png">
<img width="1068" alt="Screen Shot 2022-05-31 at 10 50 14 AM" src="https://user-images.githubusercontent.com/56789534/180815911-c11b4893-e891-4706-a0c9-bbb166b63625.png">
<img width="1068" alt="Screen Shot 2022-06-07 at 2 56 40 PM" src="https://user-images.githubusercontent.com/56789534/180815915-97fe7f6c-0978-4ed8-a975-8df527e2c391.png">
<img width="1568" alt="600" src="https://user-images.githubusercontent.com/56789534/180814525-86fafb66-9f24-4098-beb8-28eb454f0f78.png">
<img width="1068" alt="random-42-color" src="https://user-images.githubusercontent.com/56789534/180814553-7e658d79-da34-49af-8438-79086d8e3ac8.png">
<img width="1112" alt="rgb-color" src="https://user-images.githubusercontent.com/56789534/180814564-d6d0e465-bf73-41b9-bceb-6b9f1f507b79.png">


<br>
<hr>
<b>*This 42 project is written in C and in accordance to the 42 school norm.<br></b>
<br>

> #### Sample restrictions:
> - All variables have to be declared and aligned at the top of each function
> - Each function can not have more then 25 lines
> - Projects should be created with allowed std functions otherwise it is cheating

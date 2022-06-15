# 42-miniRT-new

<img width="1498" alt="42-logo" src="https://user-images.githubusercontent.com/56789534/173826141-045ce31b-b8be-4065-b711-4e385cb72ef6.png">

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
1. ```git clone [link](https://github.com/tjensen42/42-miniRT) miniRT```
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

<br>
<hr>
<b>*This 42 project is written in C and in accordance to the 42 school norm.<br></b>
<br>

> #### Sample restrictions:
> - All variables have to be declared and aligned at the top of each function
> - Each function can not have more then 25 lines
> - Projects should be created with allowed std functions otherwise it is cheating

# Sorting-Visualizer-Cpp
Visualize sorting algorithms -- in C++


# Description
This is a little program that can be used for visualization of major sorting algorithms. I've made another program like this in C# (available on my github),
but it didn't work well. I was single stepping through algorithms and displaying each state and it worked for some algorithms but others couldn't be
implemented like this (mainly recursive ones). The code was also really ugly. But now I use a different method. I first run the whole algorithm and store
each array state separately. Since the array isn't that big (<= 400 elements), it works quickly. And one advantage is you can go back in history for each
step! (This isn't implemented yet, but should be easy enough.)

# Demo
![Insertion Sort](https://i.ibb.co/2vD8Zkf/ezgif-com-gif-maker-1.gif)
Insertion Sort

![Merge Sort](https://i.ibb.co/Z6Pktg4/ezgif-com-gif-maker.gif)
Merge Sort
The yello bars are left and right indexes, the blue bar is the middle.

# To Run
If you're on Windows, download the Release folder and run the exe. For
other platforms, you have to compile yourself.

# Controls
* **Up/Down** to change array size
* **Left/Right** to change algorithm
* **S** to start
* **N** to generate new random data
* **X** to cancel running algorithm

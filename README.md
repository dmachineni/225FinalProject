# 225FinalProject

Organization:  
src: Code files (creating the graph, algorithm code), data files  
main.cpp: test cases  
data: outputted files  
results.md: written report   

Running the code:
1. Use ```` git clone ```` command to clone our repository into your environment. 
2. Use ```` cd ```` to change into your project directory.
3. Open a new terminal and run ```` make exec ````.
4. Then run ```` ./bin/exec ````.
Note: Please note that the running our code takes a while. With an M1 processor we found that it takes about 6 - 7 minutes. This is because to create and update the distance matrix, we have to run through the entire dataset (about 3000 airports) so populating the entire 2D matrix takes a while.

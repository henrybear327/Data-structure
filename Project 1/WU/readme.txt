403410050 ¸ê¤u¤G  §d©{¿²

Please use -std=c99 to compile, thanks!

project 1

stack---walking rats in a maze

Intro

I think this queastion is two floor,so i use three array to save the map.
Because the howework ask us use the stack concept,i use the two stacks(stackA for save
rata path,stackB for save ratb path)
So the dfs algorithm be use.


adverstiy

The project can operation on two rat the walking path.  
It can show 3 situations.
1. two rats meet on <floor,x,y>. 
2. a rat reach <1,99,99>.
3. b rat reach <0,1,1>.
and the code can show every step.  


bug
In begin,
1.I forget to differentiate the stair,so maybe the rat may can't walk to end.
2.I forget mark the path,so the rat shake to and fro. 

implementation

1.You should open a maze.txt
2.write '0' 
3.write 'X'(wall)or '.'(can walk the path)or 'o'(the stair,only one )
4.write '1'
5.write 'X'(wall)or '.'(can walk the path)or 'o'(the stair,only one )
6. execute
7.output in the result.txe

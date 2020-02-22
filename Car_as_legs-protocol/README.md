# car_as_legs-protocol
## This code is for arduino based car which act as Legs of a robot.
----
This code is still under developoment and not recomended for comercial use without understanding the details of the code required for manipulation.

commands input follow these protocols
direction (w,a,s,d,r) & duration || staring with ':' || seperated by ','duration can be -ve(infite) or 0(default) or nothing(default) or +ve number(set time) || ending with '.'
eg-
> :w,500. <br>
> :w.

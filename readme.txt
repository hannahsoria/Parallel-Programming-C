CS333 - Project #7 - README
Hannah Soria
5/2/24

Directory Layout:
Project5_hmsori25/
|
|__/benford_sequential.c
|__/benford_par1.c
|__/benford_par2.c
|__/benford_par3.c
|__/benford_par4.c
|__/benford_par5.c
|__/benford_par6.c
|__/colorize.c
|__/colorize_par.c
|__/pyppmIO.py
|__/my_timimg.c
|__/my_timimg.h
|__/ppmIO.c
|__/ppmIO.h
|__/IMG_4203.ppm
|__/mod.ppm
|__/medium.bin
|__/longer.bin
|__/super_short.bin


the following don't compile and run alone
|__/my_timimg.c
|__/my_timimg.h
|__/ppmIO.c
|__/ppmIO.h
|__/IMG_4203.ppm
|__/mod.ppm
|__/medium.bin
|__/longer.bin
|__/super_short.bin

benford_sequential.c
 Compile:
	gcc -o benford_sequential my_timing.c benford_sequential.c -lm
 Run:
	./benford_sequential
 Output:
  There are 3217 1's
  There are 1779 2's
  There are 1121 3's
  There are 907 4's
  There are 745 5's
  There are 668 6's
  There are 591 7's
  There are 495 8's
  There are 477 9's
  It took 0.000722 seconds for the whole thing to run

benford_par1.c
 Compile:
	gcc -o benford_par1 my_timing.c benford_par1.c -lm
 Run:
	./benford_par1
 Output:
  There are 3217 1's
  There are 1779 2's
  There are 1121 3's
  There are 907 4's
  There are 745 5's
  There are 668 6's
  There are 591 7's
  There are 495 8's
  There are 477 9's
  It took 0.001836 seconds for the whole thing to run
  ** time will vary
  
benford_par2.c
 Compile:
	gcc -o benford_par2 my_timing.c benford_par2.c -lm
 Run:
	./benford_par2
 Output:
  There are 2945 1's
  There are 1682 2's
  There are 1089 3's
  There are 889 4's
  There are 725 5's
  There are 652 6's
  There are 576 7's
  There are 487 8's
  There are 472 9's
  It took 0.000734 seconds for the whole thing to run
  ** time will vary
  
benford_par3.c
 Compile:
	gcc -o benford_par3 my_timing.c benford_par3.c -lm
 Run:
	./benford_par3
 Output:
  There are 3217 1's
  There are 1779 2's
  There are 1121 3's
  There are 907 4's
  There are 745 5's
  There are 668 6's
  There are 591 7's
  There are 495 8's
  There are 477 9's
  It took 0.000625 seconds for the whole thing to run
  ** time will vary
  
benford_par4.c
 Compile:
	gcc -o benford_par4 my_timing.c benford_par4.c -lm
 Run:
	./benford_par4
 Output:
  There are 3217 1's
  There are 1779 2's
  There are 1121 3's
  There are 907 4's
  There are 745 5's
  There are 668 6's
  There are 591 7's
  There are 495 8's
  There are 477 9's
  It took 0.000516 seconds for the whole thing to run
  ** time will vary
  
benford_par5.c
 Compile:
	gcc -o benford_par5 my_timing.c benford_par5.c -lm
 Run:
	./benford_par5
 Output:
  There are 3217 1's
  There are 1779 2's
  There are 1121 3's
  There are 907 4's
  There are 745 5's
  There are 668 6's
  There are 591 7's
  There are 495 8's
  There are 477 9's
  It took 0.000791 seconds for the whole thing to run
  ** time will vary
  
benford_par6.c
 Compile:
	gcc -o benford_par6 my_timing.c benford_par6.c -lm
 Run:
	./benford_par6
 Output:
  There are 3217 1's
  There are 1779 2's
  There are 1121 3's
  There are 907 4's
  There are 745 5's
  There are 668 6's
  There are 591 7's
  There are 495 8's
  There are 477 9's
  It took 0.000604 seconds for the whole thing to run
  ** time will vary
  
colorize.c
 Compile:
	gcc -o colorize -I. my_timing.c colorize.c ppmIO.c -lm
 Run:
	./colorize IMG_4203.ppm
 Output:
  It took 0.021929 seconds for the whole thing to run
  ** time may vary

colorize_par.c
 Compile:
	gcc -o colorize_par -I. my_timing.c colorize_par.c ppmIO.c -lm
 Run:
	./colorize_par IMG_4203.ppm
 Output:
  It took 0.015983 seconds for the whole thing to run
  ** time may vary

pyppmIO.py
 Run:
	pyppmIO.py IMG_4203.ppm
 Output:
 it took  0.0020987987518310547  seconds for the whole thing to run
 Writing mod.ppm
 Terminating

haiku.c
 Compile:
  gcc -o haiku haiku.c
 Run:
  ./haiku
 Output:
  This poem needs one
  What is this magical thing
  A mutex of course!

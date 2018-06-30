Important notice: if you're ever planning on using this. Make shure that the 2 shift registers are connected to eachother(the shiftout of the left register is connected to the the input of the right one). 
This thing shifts everything from the left register to right.


Also make sure that you keep writing to the register in the loop. Otherwise it won't show the image properly on the matrix. Also don't use println a lot, this slows down the program and it won't allow it to update quick enough in some cases
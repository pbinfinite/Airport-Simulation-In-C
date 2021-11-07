a.out:file1_pb.o file2_pb.o 
	gcc file1_pb.o file2_pb.o -lm
file1_pb.o:server.h file1_pb.c 
	gcc -c file1_pb.c 
file2_pb.o:server.h file2_pb.c
	gcc -c file2_pb.c


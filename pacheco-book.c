/* C11 Personal reference for parallel code from the book 
 * Introduction to parallel programming by 
 * Peter S. Pacheco 
 */
 
/*--------------------------- INTRODUCTION ---------------------------*/
 
// Calculating speedup: S = Time(serial) / Time(parallel)
// Calculating efficiency: E = S/p = Time(serial)/(p * Time(Parallel))

/* Foster method for designing and building parallel programs:
 * 1) Partitioning: we split the calculations and data on which the 
 *    operations will be done into small tasks. Our focus should be 
 *    on recognising tasks that can be done in parallel.
 * 2) Communication: we define the necessary communications between 
 *    the tasks that we defined on step 1.
 * 3) Agglomeration/Aggregation: we combine the tasks and communications
 *    we recognised beforehand into bigger tasks; e.g. if task A 
 *    must execute first so task B can execute, it might make sense to 
 *    combine them into one big task.
 * 4) Mapping: we assign the tasks we defined earlier 
 *    into threads/processes. This should be done so the communications
 *    are minimized and every thread/process has the same load as others.
 * */
 
/* Current trivial/basic assertions to counter common IO problems:
 * In distributed memory programs, only process 0 will access stdin.
 * In shared memory programs, only main thread, or thread 0 will access stdin.
 * 
 * In parallel programs (either distributed or shared), all 
 * threads will be able to access stdout and stderr.
 * 
 * Because of the non-deterministic output on stdout, on most cases 
 * only one process/thread will be used to dump output to stdout.
 * One exception we'll make is when debugging our program, we'll let
 * multiple processes/threads output to stdout.
 * 
 * Only one process/thread will attempt to access a certain file 
 * except stdin, stdout or stderr. Two processes/threads must never
 * read/write the same file.
 * 
 * The debug data must always have the process/thread number or id
 * that submitted it.
 * */


//hello_mpi_world.c
// execute with mpirun or mpiexec -np <number of processes> <executable>
// SPMD Program: single program multiple data
#include <stdio.h>
#include <stdlib.h>
#include <string.h> //for strlen
#include "mpi.h" //for mpi programs

const int MAX_STRING = 100;

//int main(int argc, char **argv)
int main() {
    char greeting[MAX_STRING];
    int comm_size; //number of processes
    int my_rank;   //number of running process
    
    //MPI_Init must be called first, before any other function.
    //Another syntax is this: MPI_Init(*argc, ***argv)
    MPI_Init(NULL, NULL);
    //https://www.mpich.org/static/docs/v3.3/www3/MPI_Comm_size.html
    //int MPI_Comm_size(MPI_Comm comm, int *size)
    MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
    //https://www.mpich.org/static/docs/v3.3/www3/MPI_Comm_rank.html
    //int MPI_Comm_rank(MPI_Comm comm, int *rank)
    // takes a communicator, returns the rank
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    
    if (!my_rank != 0) {
        //puts the formatted text into greeting string
        sprintf(greeting, "Greetings from process %d out of %d!", my_rank, comm_size);
        //strlen(greeting)+1 for including the \0 at the end
        //https://www.mpich.org/static/docs/v3.3/www3/MPI_Send.html
        //Performs a blocking send 
        /* Input:
        buf
            initial address of send buffer (choice) 
        count
            number of elements in send buffer (nonnegative integer) 
        datatype
            datatype of each send buffer element (handle) 
        dest
            rank of destination (integer) 
        tag
            message tag (integer) 
        comm
            communicator (handle) 
        */
        //int MPI_Send(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm)
        MPI_Send(greeting, strlen(greeting)+1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
    } else {
        printf("Greetings from process %d out of %d!\n", my_rank, comm_size);
        for(int p = 1; p < comm_size; p++) {
            //https://www.mpich.org/static/docs/v3.3/www3/MPI_Recv.html
            //Blocking receive for a message 
            /*
            Output Parameters
                buf
                    initial address of receive buffer (choice) 
                status
                    status object (Status) 

            Input Parameters
                count
                    maximum number of elements in receive buffer (integer) 
                datatype
                    datatype of each receive buffer element (handle) 
                source
                    rank of source (integer) 
                tag
                    message tag (integer) 
                comm
                    communicator (handle) 
            */
            //int MPI_Recv(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Status * status)
            MPI_Recv(greeting, MAX_STRING, MPI_CHAR, p, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("%s\n", greeting);
            //Alternatively, we could use this:
            //MPI_Recv(greeting, MAX_STRING, MPI_CHAR, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            //this way we'll receive the strings as the processes finish, rather waiting for a CERTAIN process to finish
            //however, by using the wildcard, there's a possibility we do not know who sent the message, neither the tag of the message.
            // one way to resolve this is by using status:
            //  MPI_Status status;
            //  if we pass 
            //  MPI_Recv(greeting, MAX_STRING, MPI_CHAR, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
            //  we can access status.MPI_SOURCE and status.MPI_TAG
            // in order to get the amount of data we received, we must do:
            // MPI_Get_count(&status, recv_type, &count);
            // which returns (in the count variable) the amount of elements we got
            // https://www.mpich.org/static/docs/v3.3/www3/MPI_Get_count.html
            /*
                Input Parameters
                status
                    return status of receive operation (Status) 
                datatype
                    datatype of each receive buffer element (handle) 

                Output Parameters
                count
                    number of received elements (integer) Notes: If the size of the datatype is zero, 
                    this routine will return a count of zero. If the amount of data in status is 
                    not an exact multiple of the size of datatype (so that count would not be integral),
                    a count of MPI_UNDEFINED is returned instead. 
            */
            // int MPI_Get_count(const MPI_Status * status, MPI_Datatype datatype, int *count)
        }
    }
    
    //Last MPI function to be called. Frees system resources from MPI.
    MPI_Finalize();
    
    return 0;
}

//Notes:
//  MPI_COMM_WORLD is a macro, and so is MPI_CHAR, e.g.
//  All mpi functions start with MPI_ and a capitalized letter.
//  MPI_Init and MPI_Finalize don't have to be called only in main().
/*  
 *  MPI DATATYPES MPI_Datatype
 *  
 *  MPI_CHAR    MPI_SIGNED_CHAR    MPI_UNSIGNED_CHAR    MPI_BYTE
 *  - char      signed char        unsigned char        See standard; like unsigned char 
 *  
 *  MPI_WCHAR                   MPI_SHORT       MPI_UNSIGNED_SHORT      MPI_INT
 *  wide character (wchar_t)    short           unsigned short          int
 *
 *  MPI_UNSIGNED    MPI_LONG    MPI_UNSIGNED_LONG   MPI_LONG_LONG_INT
 *  unsigned int    long        unsigned long       long long
 *
 *  MPI_LONG_LONG                   MPI_UNSIGNED_LONG_LONG
 *  synonyn for MPI_LONG_LONG_INT   unsigned long long
 *
 *  MPI_FLOAT   MPI_DOUBLE  MPI_LONG_DOUBLE
 *  float       double      long double (some systems may not implement this)
 *
 *  MPI_INT8_T  MPI_INT16_T MPI_INT32_T MPI_INT64_T MPI_UINT8_T MPI_UINT16_T
 *  int8_t      int16_t     int32_t     int64_t     uint8_t     uint16_t
 *
 *  MPI_UINT32_T    MPI_UINT64_T    MPI_C_BOOL
 *  uint32_t        uint64_t        _Bool
 *
 *  MPI_C_FLOAT_COMPLEX MPI_C_COMPLEX   MPI_C_DOUBLE_COMPLEX    MPI_C_LONG_DOUBLE_COMPLEX
 *  float _Complex      float _Complex  double _Complex         long double _Complex
 *  */
/*----------------------------------------------------------------------*/
/*--------------------------- OTHER FUNCTIONS ---------------------------*/
//https://www.mpich.org/static/docs/v3.3/www3/MPI_Ssend.html
//MPI_Ssend (Blocking synchronous send; doesn't rely on buffers) and can be used to confirm if a MPI_Send is safe (and will never hang)
//int MPI_Ssend(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm)

//https://www.mpich.org/static/docs/v3.3/www3/MPI_Bcast.html
//MPI_Bcast Broadcasts a message from the process with rank "root" to all other processes of the communicator 
//int MPI_Bcast(void *buffer, int count, MPI_Datatype datatype, int root, MPI_Comm comm)

//https://www.mpich.org/static/docs/v3.3/www3/MPI_Allreduce.html
//MPI_Allreduce Combines values from all processes and distributes the result back to all processes 
//int MPI_Allreduce(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm)

//https://www.mpich.org/static/docs/v3.3/www3/MPI_Gather.html
//MPI_Gather Gathers together values from a group of processes 
//int MPI_Gather(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm)

//https://www.mpich.org/static/docs/v3.3/www3/MPI_Allgather.html
//MPI_Allgather Gathers data from all tasks and distribute the combined data to all tasks 
//int MPI_Allgather(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm)

//MPI_Type_create_struct way to create pseudo-structs and pass more than 1 thing at the same time (e.g. 2 doubles and 1 int at once)
//MPI_Get_address ^
/*----------------------------------------------------------------------*/
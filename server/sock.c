#include <unistd.h>
#include <stddef.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/time.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>

#include "../shared/sockets.h"
#include "sock.h"
#include "clients.h"
#include "../shared/debug.h"


/**************************************************
  LCDproc sockets code...

  This is messy, and needs to be finished.
**************************************************/

fd_set active_fd_set, read_fd_set;
int orig_sock;

// Length of longest transmission allowed at once...
#define MAXMSG 8192


int read_from_client (int filedes);


// Creates a socket in internet space
int sock_create_inet_socket(unsigned short int port)
{
  struct sockaddr_in name;
  int sock;

  debug("sock_create_inet_socket(%i)\n", port);
  
  /* Create the socket. */
  //debug("Creating Inet Socket\n");
  sock = socket (PF_INET, SOCK_STREAM, 0);
  if (sock < 0)
  {
     perror("Error creating socket");
     return -1;
  }
     
  /* Give the socket a name. */
  //debug("Binding Inet Socket\n");
  name.sin_family = AF_INET;
  name.sin_port = htons (port);
  name.sin_addr.s_addr = htonl (INADDR_ANY);
  if (bind (sock, (struct sockaddr *) &name, sizeof (name)) < 0)
  {
     perror("Error binding socket");
     return -1;
  }
     
  return sock;
 
}

//int StartSocketServer()
int sock_create_server()
{
   int sock;
     
  debug("sock_create_server()\n");
  
  /* Create the socket and set it up to accept connections. */
  sock = sock_create_inet_socket(LCDPORT);
  if(sock < 0)
    {
      perror("sock_create_server: Error creating socket");
      return -1;
    }
  
  
  if (listen (sock, 1) < 0)
    {
      perror("sock_create_server: Listen error");
      return -1;
    }
  
  /* Initialize the set of active sockets. */
  FD_ZERO (&active_fd_set);
  FD_SET (sock, &active_fd_set);

  orig_sock = sock;
  
/*
  {
     int val, len, sock;
     sock = new;
     
     len = sizeof(int);
     getsockopt(sock, SOL_SOCKET, SO_SNDBUF, &val, &len);
     printf("SEND buffer: %i bytes\n", val);

     len = sizeof(int);
     getsockopt(sock, SOL_SOCKET, SO_RCVBUF, &val, &len);
     printf("RECV buffer: %i bytes\n", val);
  }
*/

  return sock;
}


int sock_poll_clients()
{
   int i;
   int err;
   struct sockaddr_in clientname;
   size_t size;
   struct timeval t;
   client *c;
   
   //debug("sock_poll_clients()\n");
   
   t.tv_sec = 0;
   t.tv_usec = 0;

   /* Block until input arrives on one or more active sockets. */
   read_fd_set = active_fd_set;
   
   if (select (FD_SETSIZE, &read_fd_set, NULL, NULL, &t) < 0)
   {
      perror("sock_poll_clients: Select error");
      return -1;
   }

   /* Service all the sockets with input pending. */
   for (i = 0; i < FD_SETSIZE; ++i)
   {
      if (FD_ISSET (i, &read_fd_set))
      {
	 if (i == orig_sock)
	 {
	    /* Connection request on original socket. */
	    int new;
	    size = sizeof (clientname);
	    new = accept (orig_sock,
			  (struct sockaddr *) &clientname,
			  &size);
	    if (new < 0)
	    {
	       perror("sock_poll_clients: Accept error");
	       return -1;
	    }
	    debug("sock_poll_clients: connect from host %s, port %hd.\n",
		     inet_ntoa (clientname.sin_addr),
		     ntohs (clientname.sin_port));
	    FD_SET (new, &active_fd_set);

	    fcntl(new, F_SETFL, O_NONBLOCK);
	    

            // TODO:  Create new "client" here...  (done?)
	    if ( client_create(new) == NULL)
	    {
	       fprintf(stderr,
		       "sock_poll_clients: error creating client %i\n",
		       i);
	       return -1;
	    }
	 }
	 else
	 {
	    /* Data arriving on an already-connected socket. */
	    err = 0;
	    do {
	       debug("sock_poll_clients: reading...\n");
	       err = read_from_client(i);
	       debug("sock_poll_clients: ...done\n");
	       if (err < 0)
	       {
		  // TODO:  Destroy a "client" here... (done?)
		  c = client_find_sock(i);
		  if(c)
		  {
		     //sock_send_string(i, "bye\n");
		     client_destroy(c);
		     close (i);
		     FD_CLR (i, &active_fd_set);
		     debug("sock_poll_clients: Closed connection %i\n", i);
		  }
		  else fprintf(stderr,
			       "sock_poll_clients: Can't find client %i\n",
			       i);
	       }
	    } while (err > 0);
	    
	 }
      }
   }
   return 0;
}


int read_from_client (int filedes)
{
   char buffer[MAXMSG];
   int nbytes, i;
   client *c;
   
//   nbytes = read (filedes, buffer, MAXMSG);
   //debug("read_from_client(%i): reading...\n", filedes);
   nbytes = sock_recv (filedes, buffer, MAXMSG);
   //debug("read_from_client(%i): ...done\n", filedes);
   debug("read_from_client(%i): %i bytes\n", filedes, nbytes);
   
  
   if (nbytes < 0)  // Read error?  No data available?
   {
      // TODO:  check errno here!
      //fprintf (stderr,"read_from_client: Read error\n");
      return 0;
   }
   else if (nbytes == 0)  // EOF
      return -1;
   else if (nbytes > (MAXMSG - (MAXMSG / 8)))  // Very noisy client...
   {
      sock_send_string(filedes, "huh? Shut up!\n");
      return -1;
   }
   else         // Data Read
   {
      buffer[nbytes] = 0;
      // Now, replace zeros with linefeeds...
      for(i=0; i<nbytes; i++)
	 if(buffer[i] == 0) buffer[i] = '\n';
      // Enqueue a "client message" here...
      c = client_find_sock(filedes);
      if(c)
      {
	 client_add_message(c, buffer);
      }
      else fprintf(stderr, "read_from_client:  Can't find client %i\n",
		   filedes);
      
      debug("read_from_client: got message: `%s'\n", buffer);
      return nbytes;
   }
   return nbytes;
}

// FIXME: This talks to all open files, including
// stdin, stdout, stderr, the LCD, etc...
// BUT it should only talk to sockets!
int sock_close_all()
{
   int i;

   debug("sock_close_all()\n");
   
   for (i = 0; i < FD_SETSIZE; i++)
   {
      // TODO:  Destroy a "client" here...?  Nope.
      sock_send_string(i, "bye\n");
      close (i);
      FD_CLR (i, &active_fd_set);
      debug("sock_close_all: Closed connection %i\n", i);
   }

   return 0;
  
}